
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "opcodes.h"

Cpu::Cpu(Mmu* mmu) {
    memory = mmu;
    pc = 0x100;
    sp = 0xFFFE;

    time_counter = 0;
    divider_counter = 0;
    current_clock_speed = 1024;

    interrupt_master = true;
    pending_interrupt_disabled = false;
    pending_interrupt_enabled = false;
    joypad_state = 0xFF;

    current_ram_bank = 0;
    current_rom_bank = 1;

    mbc1 = false;
    mbc2 = false;
    using16_8_model = false;

    
    registers[A] = 0x01;
    registers[F] = 0xB0;
    registers[C] = 0x13;
    registers[E] = 0xD8;
    registers[H] = 0x01;
    registers[L] = 0x4D;   
    memory->address[0xFF05] = 0x00;  // TIMA
    memory->address[0xFF06] = 0x00;  // TMA
    memory->address[0xFF07] = 0x00;  // TAC
    memory->address[0xFF0F] = 0xE1;  // FIXME: IF
    memory->address[0xFF10] = 0x80;  // NR10
    memory->address[0xFF11] = 0xBF;  // NR11
    memory->address[0xFF12] = 0xF3;  // NR12
    memory->address[0xFF14] = 0xBF;  // NR14
    memory->address[0xFF16] = 0x3F;  // NR21
    memory->address[0xFF17] = 0x00;  // NR22
    memory->address[0xFF19] = 0xBF;  // NR24
    memory->address[0xFF1A] = 0x7F;  // NR30
    memory->address[0xFF1B] = 0xFF;  // NR31
    memory->address[0xFF1C] = 0x9F;  // NR32
    memory->address[0xFF1E] = 0xBF;  // NR33
    memory->address[0xFF20] = 0xFF;  // NR41
    memory->address[0xFF21] = 0x00;  // NR42
    memory->address[0xFF22] = 0x00;  // NR43
    memory->address[0xFF23] = 0xBF;  // NR30
    memory->address[0xFF24] = 0x77;  // NR50
    memory->address[0xFF25] = 0xF3;  // NR51
    memory->address[0xFF26] = 0xF1;  // GB
    memory->address[0xFF40] = 0x91;  // LCDC
    memory->address[0xFF42] = 0x00;  // SCY
    memory->address[0xFF43] = 0x00;  // SCX
    memory->address[0xFF45] = 0x00;  // LYC
    memory->address[0xFF47] = 0xFC;  // BGP
    memory->address[0xFF48] = 0xFF;  // OBP0
    memory->address[0xFF49] = 0xFF;  // OBP1
    memory->address[0xFF4A] = 0x00;  // WY
    memory->address[0xFF4B] = 0x00;  // WX
    memory->address[0xFFFF] = 0x00;  // IE

    switch (read_memory(0x147)) {
        case 0:
            mbc1 = false;
            break;
        case 1:
        case 2:
        case 3:
            mbc1 = true;
            break;
        case 5:
            mbc2 = true;
            break;
        case 6:
            mbc2 = true;
            break;
    }

    int n_ram_banks = 0;
    switch (read_memory(0x149)) {
        case 0:
            n_ram_banks = 0;
            break;
        case 1:
            n_ram_banks = 1;
            break;
        case 2:
            n_ram_banks = 1;
            break;
        case 3:
            n_ram_banks = 4;
            break;
        case 4:
            n_ram_banks = 16;
            break;
    }

    for (int i = 0; i < n_ram_banks; i++) {
        byte* ram = new byte[0x2000];
        memset(ram, 0, sizeof(ram));
        memory->ram_banks.push_back(ram);
    }

    if (n_ram_banks > 0) {
        for (int i = 0; i < 0x2000; i++) {
            memory->ram_banks[0][i] = memory->address[0xA000 + i];
        }
    }
};

void Cpu::emulate_cycle() {
    // get opcode
    opcode = read_memory(pc);
    last_clock = cycle_table[opcode];

    // decode and execute op
    execute_opcode();

    pc++;

    if (pending_interrupt_disabled) {
        if (read_memory(pc - 1) != 0xF3) {
            interrupt_master = false;
            pending_interrupt_disabled = false;
        }
    }
    if (pending_interrupt_enabled) {
        if (read_memory(pc - 1) != 0xFB) {
            interrupt_master = true;
            pending_interrupt_enabled = false;
        }
    }
};

void Cpu::execute_opcode() {
    debug();

    (*optable[opcode])(memory, this);
};

void Cpu::debug() {
    printf("pc: %04x  opcode: %02x  sp: %04x\n", pc, opcode, sp);
    printf("a: %02x  f: %02x\n", registers[A], registers[F]);
    printf("b: %02x  c: %02x\n", registers[B], registers[C]);
    printf("d: %02x  e: %02x\n", registers[D], registers[E]);
    printf("h: %02x  l: %02x\n", registers[H], registers[L]);
    printf("\n");
};

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void Cpu::subc_a_pc() {
    // TODO:: this is not used??
    registers[A] = sub8(registers[A], memory->address[pc] + get_c_flag());
};

void Cpu::add_hl_r16(byte r16) {
    word res = add16((registers[H] << 8) | registers[L],
                     (registers[r16] << 8) | registers[r16 + 1]);

    registers[H] = res & 0xFF;
    registers[L] = (res & 0xFF00) >> 8;
};

void Cpu::add_hl_sp() {
    word res = add16((registers[H] << 8) | registers[L], sp);

    registers[H] = res & 0xFF;
    registers[L] = (res & 0xFF00) >> 8;
};

void Cpu::inc_r16(byte r16) {
    word res = ((registers[r16] << 8) | registers[r16 + 1]) + 1;
    registers[r16] = res & 0xFF;
    registers[r16 + 1] = (res & 0xFF00) >> 8;
};

void Cpu::dec_r16(byte r16) {
    word res = ((registers[r16] << 8) | registers[r16 + 1]) - 1;
    registers[r16] = res & 0xFF;
    registers[r16 + 1] = (res & 0xFF00) >> 8;
};

void Cpu::swap_r1(byte r1) {
    registers[r1] = (registers[r1] << 4) | (registers[r1] >> 4);

    set_z_flag(registers[r1] == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);
};

void Cpu::swap_r16(byte r16) {
    byte temp = registers[r16];

    registers[r16] = registers[r16 + 1];
    registers[r16 + 1] = temp;

    set_z_flag(registers[r16] == 0 && registers[r16 + 1] == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);
};

// for rl vs rlc : http://jgmalcolm.com/z80/advanced/shif

void Cpu::rlc_r1(byte r1) {
    // rotates r1 to the left with bit 7 being moved to bit 0 and
    // also stored in the carry

    byte carry = (registers[r1] & (1 << 7)) >> 7;
    registers[r1] = (registers[r1] << 1) | carry;

    set_z_flag(registers[r1] == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(carry);
};

void Cpu::rl_r1(byte r1) {
    // rotates r1 to the left with the carry's value put into bit
    // 0 and bit 7 is put into the carry

    byte carry = get_c_flag();

    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(registers[r1] & (1 << 7));

    registers[r1] = (registers[r1] << 1) | carry;

    set_z_flag(registers[r1] == 0);
};

void Cpu::rrc_r1(byte r1) {
    set_h_flag(0);
    set_n_flag(0);
    set_c_flag(registers[r1] & 0x01);

    byte carry = get_c_flag();
    registers[r1] = (registers[r1] >> 1) | (carry << 7);

    set_z_flag(registers[r1] == 0);
};

void Cpu::rr_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(registers[r1] & 0x01);

    byte carry = get_c_flag();
    registers[r1] = (registers[r1] >> 1) | (carry << 7);

    set_z_flag(registers[r1] == 0);
};

void Cpu::sla_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag((registers[r1] & 0x80) >> 7);

    registers[r1] <<= 1;

    set_z_flag(registers[r1] == 0);
};

void Cpu::sra_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(registers[r1] & 0x01);

    byte last_bit = registers[r1] & 0x80;
    registers[r1] >>= 1;
    registers[r1] |= last_bit;

    set_z_flag(registers[r1] == 0);
};

void Cpu::srl_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(registers[r1] & 0x01);

    registers[r1] >>= 1;

    set_z_flag(registers[r1] == 0);
};

void Cpu::bit_r1(byte r1, byte bit) {
    bool n = true;
    if (r1 == 6) {
        last_clock = 16;
        n = (read_memory((registers[H] << 8) | registers[L])) & (1 << bit);
    } else if (r1 == 7) {
        n = registers[A] & (1 << bit);
    } else {
        n = registers[r1 + 2] & (1 << bit);
    }

    set_z_flag(!n);
    set_n_flag(0);
    set_h_flag(1);
};

void Cpu::set_r1(byte r1, byte bit) {
    if (r1 == 6) {
        last_clock = 16;
        word hl = (registers[H] << 8) | registers[L];
        write_memory(hl, read_memory(hl) | (1 << bit));
    } else if (r1 == 7) {
        registers[A] |= (1 << bit);
    } else {
        registers[r1 + 2] |= (1 << bit);
    }
};

void Cpu::res_r1(byte r1, byte bit) {
    if (r1 == 6) {
        last_clock = 16;
        word hl = (registers[H] << 8) | registers[L];
        write_memory(hl, read_memory(hl) & ~(1 << bit));
    } else if (r1 == 7) {
        registers[A] &= ~(1 << bit);
    } else {
        registers[r1 + 2] &= ~(1 << bit);
    }
};

void Cpu::call_cc_nn(byte cc) {
    word nn = read_memory(++pc) | (read_memory(++pc) << 8);

    if (cc == 0 && !get_z_flag()) {
        store_pc_stack();
        pc = nn;
    } else if (cc == 1 && get_z_flag()) {
        store_pc_stack();
        pc = nn;
    } else if (cc == 2 && !get_c_flag()) {
        store_pc_stack();
        pc = nn;
    } else if (cc == 3 && get_c_flag()) {
        store_pc_stack();
        pc = nn;
    }
};

void Cpu::ret_cc(byte cc) {
    if (cc == 0 && !get_z_flag()) {
        ret();
    } else if (cc == 1 && get_z_flag()) {
        ret();
    } else if (cc == 2 && !get_c_flag()) {
        ret();
    } else if (cc == 3 && get_c_flag()) {
        ret();
    }
};

byte Cpu::add8(byte op1, byte op2) {
    byte res = op1 + op2;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag((op1 & 0x0F) + (op2 & 0x0F) > 0x0F);
    set_c_flag((op1 + op2) > 0xFF);

    return res;
};

byte Cpu::sub8(byte op1, byte op2) {
    byte res = op1 - op2;

    set_z_flag(res == 0);
    set_n_flag(1);
    set_h_flag((op1 & 0x0F) < (op2 & 0x0F));
    set_c_flag(op1 < op2);

    return res;
};

byte Cpu::and8(byte op1, byte op2) {
    byte res = op1 & op2;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag(1);
    set_c_flag(0);

    return res;
};

byte Cpu::or8(byte op1, byte op2) {
    byte res = op1 | op2;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);

    return res;
};

byte Cpu::xor8(byte op1, byte op2) {
    byte res = op1 ^ op2;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);

    return res;
};

void Cpu::cp(byte op1, byte op2) {
    set_z_flag(op1 == op2);
    set_n_flag(1);
    set_h_flag((op1 & 0xF) < (op2 & 0xF));
    set_c_flag(op1 < op2);
};

void Cpu::inc8(byte op1) {
    byte res = registers[op1] + 1;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag((registers[op1] & 0x0F) == 0x0F);

    registers[op1] = res;
};

void Cpu::dec8(byte op1) {
    byte res = registers[op1] - 1;

    set_z_flag(res == 0);
    set_n_flag(1);
    set_h_flag((res & 0x0F) == 0x0F);

    registers[op1] = res;
};

word Cpu::add16(word op1, word op2) {
    set_n_flag(0);
    set_h_flag((0x0FFF & op1) + (0X0FFF & op2) > 0x0FFF);
    set_c_flag((0xFFFF - op1) < op2);

    return op1 + op2;
};

void Cpu::ret() {
    pc = (read_memory(sp++) | (read_memory(sp++) << 8)) - 1;
};

void Cpu::store_pc_stack() {
    write_memory(--sp, ((pc + 1) & 0xFF00) >> 8);
    write_memory(--sp, ((pc + 1) & 0xFF));
};

void Cpu::push16(byte r1) {
    write_memory(--sp, registers[r1]);
    write_memory(--sp, registers[r1 + 1]);
};

void Cpu::pop16(byte r1) {
    registers[r1 + 1] = read_memory(sp++);
    registers[r1] = read_memory(sp++);
};

void Cpu::set_z_flag(bool value) {
    registers[F] = (registers[F] & ~(1 << 7)) | (value << 7);
};

void Cpu::set_n_flag(bool value) {
    registers[F] = (registers[F] & ~(1 << 6)) | (value << 6);
};

void Cpu::set_h_flag(bool value) {
    registers[F] = (registers[F] & ~(1 << 5)) | (value << 5);
};

void Cpu::set_c_flag(bool value) {
    registers[F] = (registers[F] & ~(1 << 4)) | (value << 4);
};

bool Cpu::get_z_flag() { return registers[F] & 0x80; };

bool Cpu::get_n_flag() { return registers[F] & 0x40; };

bool Cpu::get_h_flag() { return registers[F] & 0x20; };

bool Cpu::get_c_flag() { return registers[F] & 0x10; };
