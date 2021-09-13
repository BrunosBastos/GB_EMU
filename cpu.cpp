
#include <stdio.h>

#include "opcodes.h"

void cpu::initialize(mmu* mmu) {
    pc = 0x100;
    memory = mmu;
    time_counter = 0;
    divider_counter = 0;
    sp = 0xFFFE;
    interrupt_master = true;
    pending_interrupt_disabled = false;
    pending_interrupt_enabled = false;
    joypad_state = 0xFF;
}

void cpu::emulate_cycle() {
    // get opcode
    opcode = memory->address[pc];
    last_clock = cycle_table[opcode];

    // decode and execute op
    execute_opcode();

    pc += 1;

    if (pending_interrupt_disabled) {
        if (memory->address[pc - 1] != 0xF3) {
            interrupt_master = false;
            pending_interrupt_disabled = false;
        }
    }
    if (pending_interrupt_enabled) {
        if (memory->address[pc - 1] != 0xFB) {
            interrupt_master = true;
            pending_interrupt_enabled = false;
        }
    }
};

void cpu::key_pressed(int key) {
    bool previously_unset = false;

    if (!(joypad_state & (1 << key))) {
        previously_unset = true;
    }

    joypad_state &= ~(1 << key);

    byte res = memory->address[0xFF00];
    bool req_interrupt = false;

    // standard buttons
    if (key > 3 && !(res & (1 << 5))) {
        req_interrupt = true;
    }
    // directional buttons
    else if (key <= 3 && !(res & (1 << 4))) {
        req_interrupt = true;
    }

    if (req_interrupt && !previously_unset) {
        request_interrupt(4);
    }
}

void cpu::key_released(int key) { joypad_state |= (1 << key); };

byte cpu::get_joypad_state() {
    byte res = memory->address[0xFF00] ^ 0xFF;

    // standard buttons
    if (!(res & (1 << 4))) {
        res &= ((joypad_state >> 4) | 0xF0);
    }
    // directional buttons
    else if (!(res & (1 << 5))) {
        res &= ((joypad_state & 0xF) | 0xF0);
    }
    return res;
};

void cpu::execute_opcode() {
    debug();

    (*optable[opcode])(memory, this);
};

void cpu::debug() {
    printf("pc: %04x  opcode: %02x  sp: %04x\n", pc, opcode, sp);
    printf("a: %02x  f: %02x\n", registers[A], registers[F]);
    printf("b: %02x  c: %02x\n", registers[B], registers[C]);
    printf("d: %02x  e: %02x\n", registers[D], registers[E]);
    printf("h: %02x  l: %02x\n", registers[H], registers[L]);
    printf("\n");
};

void cpu::request_interrupt(int id) { memory->address[0xFF0F] |= (1 << id); };

void cpu::execute_interrupts() {
    if (interrupt_master) {
        byte req = memory->address[0xFF0F];
        byte enabled = memory->address[memory->ief];

        if (req & 0xFF) {
            // check if any of the bits is 1
            for (int i = 0; i <= 4; i++) {
                // check if the bit is set and if so check if it is
                // enabled in the other flag
                if ((req & (1 << i)) && (enabled & (1 << i))) {
                    // FIXME: does this need a break?
                    service_interrupt(i);
                }
            }
        }
    }
};

void cpu::service_interrupt(int id) {
    // master interrupt and the bit of the current interrupt are reset
    interrupt_master = false;
    memory->address[0xFF0F] &= ~(1 << id);

    stack[--sp] = pc;  // FIXME:

    switch (id) {
        case 0:
            pc = 0x40;
            break;
        case 1:
            pc = 0x48;
            break;
        case 2:
            pc = 0x50;
            break;
        case 4:
            pc = 0x60;
            break;
    }
}

void cpu::update_timers() {
    divider_counter += last_clock;
    if (divider_counter >= 255) {
        divider_counter = 0;
        memory->address[0xFF04]++;
    }

    // check if clock enabled
    if (memory->address[0xFF07] & (1 << 2)) {
        time_counter -= last_clock;

        // enough cpu clock cycles have happened to update the timer
        if (time_counter <= 0) {
            switch (memory->address[0xFF07] & 0x3) {
                case 0:
                    time_counter = 1024;
                    break;  // freq 4096
                case 1:
                    time_counter = 16;
                    break;  // freq 262144
                case 2:
                    time_counter = 64;
                    break;  // freq 65536
                case 3:
                    time_counter = 256;
                    break;  // freq 16382
            }

            memory->address[0xFF05]++;

            // overflow
            if (memory->address[0xFF05] == 0) {
                memory->address[0xFF05] = memory->address[0xFF06];
                request_interrupt(2);
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void cpu::subc_a_pc() {
    // TODO:: this is not used??
    registers[A] = sub8(registers[A], memory->address[pc] + get_c_flag());
};

void cpu::add_hl_r16(byte r16) {
    // FIXME:
    word res = add16(registers[H] | (registers[L] << 8),
                     registers[r16] | (registers[r16 + 1] << 8));

    registers[H] = res & 0xFF;
    registers[L] = (res & 0xFF00) >> 8;
};

void cpu::add_hl_sp() {
    word res = add16(registers[H] | (registers[L] << 8), sp);

    registers[H] = res & 0xFF;
    registers[L] = (res & 0xFF00) >> 8;
};

void cpu::add_sp_pc() {
    char n = memory->address[++pc];

    set_z_flag(0);
    set_n_flag(0);
    if (n < 0) {
        set_c_flag(0);  // FIXME:_ foi feito a sorte
        set_h_flag(0);
    } else {
        set_c_flag(1);
        set_h_flag(1);
    }
    sp += n;
};

void cpu::inc_r16(byte r16) {
    word res = inc16(registers[r16] | (registers[r16 + 1] << 8));
    registers[r16] = res & 0xFF;
    registers[r16 + 1] = (res & 0xFF00) >> 8;
};

void cpu::dec_r16(byte r16) {
    word res = dec16(registers[r16] | (registers[r16 + 1] << 8));
    registers[r16] = res & 0xFF;
    registers[r16 + 1] = (res & 0xFF00) >> 8;
};

void cpu::swap_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);

    registers[r1] = (registers[r1] << 4) | (registers[r1] >> 4);
    if (registers[r1] == 0) set_z_flag(1);
};

void cpu::swap_r16(byte r16) {
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);

    byte temp = registers[r16];

    registers[r16] = registers[r16 + 1];
    registers[r16 + 1] = temp;
    if (registers[r16] == 0 && registers[r16 + 1] == 0) set_z_flag(1);
};

// for rl vs rlc : http://jgmalcolm.com/z80/advanced/shif

void cpu::rlc_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);

    if (registers[r1] == 0x80) {
        set_z_flag(1);
        set_c_flag(1);
    } else if (registers[r1] & 0x80) {
        set_c_flag(1);
    } else {
        set_c_flag(0);
    }

    byte carry = get_c_flag() >> 6;
    registers[r1] = (registers[r1] << 1) | carry;
};

void cpu::rl_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);
    byte carry = get_c_flag() >> 6;

    if (registers[r1] == 0x80) {
        set_z_flag(1);
    }

    if (registers[r1] & 0x80) {
        set_c_flag(1);
    } else {
        set_c_flag(0);
    }

    registers[r1] = (registers[r1] << 1) | carry;
};

void cpu::rrc_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);

    if (registers[r1] == 0x01) set_z_flag(1);

    if (registers[r1] & 0x01)
        set_c_flag(1);
    else
        set_c_flag(0);

    byte carry = registers[r1] & 0x01;
    registers[r1] = (registers[r1] >> 1) | (carry << 7);
};

void cpu::rr_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);
    byte carry = get_c_flag() >> 6;

    if (registers[r1] == 0x01) set_z_flag(1);

    if (registers[r1] & 0x01)
        set_c_flag(1);
    else
        set_c_flag(0);

    registers[r1] = (registers[r1] >> 1) | (carry << 7);
};

void cpu::sla_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);

    if (registers[r1] & 0x80)
        set_c_flag(1);
    else
        set_c_flag(0);

    registers[r1] <<= 1;
    if (registers[r1] == 0) set_z_flag(1);
};

void cpu::sra_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);

    if (registers[r1] & 0x01)
        set_c_flag(1);
    else
        set_c_flag(0);

    byte last_bit = registers[r1] & 0x80;
    registers[r1] >>= 1;
    registers[r1] |= last_bit;

    if (registers[r1] == 0) set_z_flag(1);
};

void cpu::srl_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);
    if (registers[r1] & 0x01)
        set_c_flag(1);
    else
        set_c_flag(0);

    registers[r1] >>= 1;

    if (registers[r1] == 0) set_z_flag(1);
};

void cpu::bit_r1(byte r1, byte bit) {
    set_n_flag(0);
    set_h_flag(1);

    bool n = true;
    if (r1 == 6) {
        // FIXME: not sure if the its the addr or the values of reg
        last_clock = 16;
        n = (memory->address[registers[H] | (registers[L] << 8)]) & (1 << bit);
    } else if (r1 == 7) {
        n = registers[A] & (1 << bit);
    } else {
        n = registers[r1 + 2] & (1 << bit);
    }

    if (!n) set_z_flag(1);
};

void cpu::set_r1(byte r1, byte bit) {
    if (r1 == 6) {
        // FIXME: not sure if the its the addr or the values of reg
        last_clock = 16;
        memory->address[registers[H] | (registers[L] << 8)] |= (1 << bit);
    } else if (r1 == 7) {
        registers[A] |= (1 << bit);
    } else {
        registers[r1 + 2] |= (1 << bit);
    }
};

void cpu::res_r1(byte r1, byte bit) {
    if (r1 == 6) {
        // FIXME: not sure if the its the addr or the values of reg
        last_clock = 16;
        memory->address[registers[H] | (registers[L] << 8)] &= ~(1 << bit);
    } else if (r1 == 7) {
        registers[A] &= ~(1 << bit);
    } else {
        registers[r1 + 2] &= ~(1 << bit);
    }
};

void cpu::call_cc_nn(byte cc) {
    word nn =
        memory->address[memory->address[++pc] | (memory->address[++pc] << 8)];

    if (cc == 0 && !get_z_flag()) {
        stack[--sp] = pc;
        pc = nn;
    } else if (cc == 1 && get_z_flag()) {
        stack[--sp] = pc;
        pc = nn;
    } else if (cc == 2 && !get_c_flag()) {
        stack[--sp] = pc;
        pc = nn;
    } else if (cc == 3 && get_c_flag()) {
        stack[--sp] = pc;
        pc = nn;
    }
};

void cpu::ret_cc(byte cc) {
    if (cc == 0 && !get_z_flag()) {
        pc = stack[sp++];
    } else if (cc == 1 && get_z_flag()) {
        pc = stack[sp++];
    } else if (cc == 2 && !get_c_flag()) {
        pc = stack[sp++];
    } else if (cc == 3 && get_c_flag()) {
        pc = stack[sp++];
    }
};

byte cpu::add8(byte op1, byte op2) {
    set_n_flag(0);

    byte res = op1 + op2;

    if (res == 0) {
        set_z_flag(1);
    }

    if ((op1 + op2) > 0xFF) {
        set_c_flag(1);
    }

    if ((op1 & 0x0F) + (op2 & 0x0F) > 0x0F) {
        set_h_flag(1);
    }

    return res;
};

byte cpu::sub8(byte op1, byte op2) {
    set_n_flag(1);

    byte res = op1 - op2;

    if (res == 0) {
        set_z_flag(1);
    }

    if (op2 < op1) {
        set_c_flag(1);
    }

    if ((op2 & 0x0F) < (op1 & 0x0F)) {
        set_h_flag(1);
    }
    return res;
};

byte cpu::and8(byte op1, byte op2) {
    set_c_flag(0);
    set_h_flag(1);
    set_n_flag(0);

    byte res = op1 & op2;

    if (res == 0) set_z_flag(1);

    return res;
};

byte cpu::or8(byte op1, byte op2) {
    set_c_flag(0);
    set_h_flag(0);
    set_n_flag(0);

    byte res = op1 | op2;

    if (res == 0) set_z_flag(1);

    return res;
};

byte cpu::xor8(byte op1, byte op2) {
    set_c_flag(0);
    set_h_flag(0);
    set_n_flag(0);

    byte res = op1 ^ op2;

    if (res == 0) set_z_flag(1);

    return res;
};

void cpu::cp(byte op1, byte op2) {
    set_n_flag(1);

    if (op1 == op2) set_z_flag(1);

    if (op1 < op2) set_c_flag(1);

    if ((op1 & 0xF) < (op2 & 0xF)) set_h_flag(1);
};

byte cpu::inc8(byte op1) {
    set_n_flag(0);

    byte res = op1 + 1;

    if (res == 0) set_z_flag(1);

    if ((op1 & 0x0F) == 0x0F) set_h_flag(1);

    return res;
};

byte cpu::dec8(byte op1) {
    set_n_flag(1);

    byte res = op1 - 1;

    if (res == 0) set_z_flag(1);

    if ((res & 0x0F) == 0x0F) set_h_flag(1);

    return res;
};

word cpu::add16(word op1, word op2) {
    // this operation uses the values of the registers and not the addresses

    set_n_flag(0);

    if ((0xFFFF - op1) < op2) set_c_flag(1);

    if ((0x0FFF & op1) + (0X0FFF & op2) > 0x0FFF) set_h_flag(1);  // not sure

    return op1 + op2;
};

word cpu::inc16(word op1) {
    // no flags are affected making this function kinda useless
    return op1 + 1;
};

word cpu::dec16(word op1) {
    // no flags are affected making this function kinda useless
    return op1 - 1;
};

void cpu::set_z_flag(byte value) {
    registers[F] = (registers[F] & ~(1 << 7)) | (value << 7);
};

void cpu::set_n_flag(byte value) {
    registers[F] = (registers[F] & ~(1 << 6)) | (value << 6);
};

void cpu::set_h_flag(byte value) {
    registers[F] = (registers[F] & ~(1 << 5)) | (value << 5);
};

void cpu::set_c_flag(byte value) {
    registers[F] = (registers[F] & ~(1 << 4)) | (value << 4);
};

bool cpu::get_z_flag() { return registers[F] & 0x80; };

bool cpu::get_n_flag() { return registers[F] & 0x40; };

bool cpu::get_h_flag() { return registers[F] & 0x20; };

bool cpu::get_c_flag() { return registers[F] & 0x10; };
