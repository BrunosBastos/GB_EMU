
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "opcodes.h"

void cpu::initialize(mmu* mmu) {
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

void cpu::emulate_cycle() {
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

byte cpu::read_memory(word addr) {
    // reading from rom bank
    if (addr >= 0x4000 && addr <= 0x7FFF) {
        unsigned int new_Address = addr;
        new_Address += ((current_rom_bank - 1) * 0x4000);
        return memory->cart->rom[new_Address];
    }
    // reading from RAM Bank
    else if (addr >= 0xA000 && addr <= 0xBFFF) {
        // WORD new_Address = addr - 0xA000;
        // return m_RamBank.at(current_ram_bank)[new_Address];
        assert(false);
    }
    // trying to read joypad state
    else if (addr == 0xFF00)
        return get_joypad_state();

    return memory->address[addr];
};

void cpu::write_memory(word addr, byte data) {
    // writing to memory addr 0x0 to 0x1FFF this disables writing to the ram
    // bank. 0 disables, 0xA enables
    if (addr <= 0x1FFF) {
        if (mbc1) {
            if ((data & 0xF) == 0xA)
                enable_ram_bank = true;
            else if (data == 0x0)
                enable_ram_bank = false;
        } else if (mbc2) {
            // bit 0 of upper byte must be 0
            if (!(addr & 0x10)) {
                if ((data & 0xF) == 0xA)
                    enable_ram_bank = true;
                else if (data == 0x0)
                    enable_ram_bank = false;
            }
        }
    }

    // if writing to a memory addr between 2000 and 3FFF then we need to
    // change rom bank
    else if ((addr >= 0x2000) && (addr <= 0x3FFF)) {
        if (mbc1) {
            if (data == 0x00) data++;

            data &= 31;

            // Turn off the lower 5-bits.
            current_rom_bank &= 224;

            // Combine the written data with the register.
            current_rom_bank |= data;

            printf("Changing Rom Bank to %d", current_rom_bank);
        } else if (mbc2) {
            data &= 0xF;
            current_rom_bank = data;
        }
    }

    // writing to addr 0x4000 to 0x5FFF switches ram banks (if enabled of
    // course)
    else if ((addr >= 0x4000) && (addr <= 0x5FFF)) {
        if (mbc1) {
            // are we using memory model 16/8
            if (using16_8_model) {
                // in this mode we can only use Ram Bank 0
                current_ram_bank = 0;

                data &= 3;
                data <<= 5;

                if ((current_rom_bank & 31) == 0) {
                    data++;
                }

                // Turn off bits 5 and 6, and 7 if it somehow got turned on.
                current_rom_bank &= 31;

                // Combine the written data with the register.
                current_rom_bank |= data;

                printf("Changing Rom Bank to %d", current_rom_bank);
            } else {
                current_ram_bank = data & 0x3;
                printf("=====Changing Ram Bank to %d=====", current_ram_bank);
            }
        }
    }

    // writing to addr 0x6000 to 0x7FFF switches memory model
    else if ((addr >= 0x6000) && (addr <= 0x7FFF)) {
        if (mbc1) {
            // we're only interested in the first bit
            data &= 1;
            if (data == 1) {
                current_ram_bank = 0;
                using16_8_model = false;
            } else
                using16_8_model = true;
        }
    }

    // from now on we're writing to RAM

    else if ((addr >= 0xA000) && (addr <= 0xBFFF)) {
        if (enable_ram_bank) {
            if (mbc1) {
                word new_addr = addr - 0xA000;
                memory->ram_banks.at(current_ram_bank)[new_addr] = data;
            }
        } else if (mbc2 && (addr < 0xA200)) {
            word new_addr = addr - 0xA000;
            memory->ram_banks.at(current_ram_bank)[new_addr] = data;
        }

    }

    // we're right to internal RAM, remember that it needs to echo it
    else if ((addr >= 0xC000) && (addr <= 0xDFFF)) {
        memory->address[addr] = data;
    }

    // echo memory. Writes here and into the internal ram. Same as above
    else if ((addr >= 0xE000) && (addr <= 0xFDFF)) {
        memory->address[addr] = data;
        memory->address[addr - 0x2000] = data;  // echo data into ram addr
    }

    // This area is restricted.
    else if ((addr >= 0xFEA0) && (addr <= 0xFEFF)) {
    }

    // reset the divider register
    else if (addr == 0xFF04) {
        memory->address[0xFF04] = 0;
        divider_counter = 0;
    }

    // not sure if this is correct
    else if (addr == 0xFF07) {
        memory->address[addr] = data;

        int timerVal = data & 0x03;

        int clockSpeed = 0;

        switch (timerVal) {
            case 0:
                clockSpeed = 1024;
                break;
            case 1:
                clockSpeed = 16;
                break;
            case 2:
                clockSpeed = 64;
                break;
            case 3:
                clockSpeed = 256;
                break;  // 256
            default:
                assert(false);
                break;  // weird timer val
        }

        if (clockSpeed != current_clock_speed) {
            time_counter = 0;
            current_clock_speed = clockSpeed;
        }
    }

    // FF44 shows which horizontal scanline is currently being draw. Writing
    // here resets it
    else if (addr == 0xFF44) {
        memory->address[0xFF44] = 0;
    }

    else if (addr == 0xFF45) {
        memory->address[addr] = data;
    }
    // DMA transfer
    else if (addr == 0xFF46) {
        word new_addr = (data << 8);
        for (int i = 0; i < 0xA0; i++) {
            memory->address[0xFE00 + i] = read_memory(new_addr + i);
        }
    }

    // This area is restricted.
    else if ((addr >= 0xFF4C) && (addr <= 0xFF7F)) {
    }

    else {
        memory->address[addr] = data;
    }
};

void cpu::key_pressed(int key) {
    bool previously_unset = false;

    if (!(joypad_state & (1 << key))) {
        previously_unset = true;
    }

    joypad_state &= ~(1 << key);

    byte res = read_memory(0xFF00);
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
        request_interrupt(INTERRUPT_JOYPAD);
    }
};

void cpu::key_released(int key) {
    joypad_state |= (1 << key);
};

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

void cpu::request_interrupt(int id) {
    write_memory(0xFF0F, read_memory(0xFF0F) | (1 << id));
};

void cpu::execute_interrupts() {
    if (interrupt_master) {
        byte req = read_memory(0xFF0F);
        byte enabled = read_memory(0xFFFF);

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
    write_memory(0xFF0F, read_memory(0xFF0F) & ~(1 << id));

    store_pc_stack();

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
};

void cpu::update_timers() {
    divider_counter += last_clock;
    if (divider_counter >= 255) {
        divider_counter = 0;
        write_memory(0xFF04, read_memory(0xFF04) + 1);
    }

    // check if clock enabled
    if (read_memory(0xFF07) & (1 << 2)) {
        time_counter -= last_clock;

        // enough cpu clock cycles have happened to update the timer
        if (time_counter <= 0) {
            switch (read_memory(0xFF07) & 0x3) {
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

            write_memory(0xFF05, read_memory(0xFF05) + 1);

            // overflow
            if (read_memory(0xFF05) == 0) {
                write_memory(0xFF05, read_memory(0xFF06));
                request_interrupt(INTERRUPT_TIMER);
            }
        }
    }
};

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void cpu::subc_a_pc() {
    // TODO:: this is not used??
    registers[A] = sub8(registers[A], memory->address[pc] + get_c_flag());
};

void cpu::add_hl_r16(byte r16) {
    word res = add16((registers[H] << 8) | registers[L],
                     (registers[r16] << 8) | registers[r16 + 1]);

    registers[H] = res & 0xFF;
    registers[L] = (res & 0xFF00) >> 8;
};

void cpu::add_hl_sp() {
    word res = add16((registers[H] << 8) | registers[L], sp);

    registers[H] = res & 0xFF;
    registers[L] = (res & 0xFF00) >> 8;
};

void cpu::inc_r16(byte r16) {
    word res = ((registers[r16] << 8) | registers[r16 + 1]) + 1;
    registers[r16] = res & 0xFF;
    registers[r16 + 1] = (res & 0xFF00) >> 8;
};

void cpu::dec_r16(byte r16) {
    word res = ((registers[r16] << 8) | registers[r16 + 1]) - 1;
    registers[r16] = res & 0xFF;
    registers[r16 + 1] = (res & 0xFF00) >> 8;
};

void cpu::swap_r1(byte r1) {
    registers[r1] = (registers[r1] << 4) | (registers[r1] >> 4);

    set_z_flag(registers[r1] == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);
};

void cpu::swap_r16(byte r16) {
    byte temp = registers[r16];

    registers[r16] = registers[r16 + 1];
    registers[r16 + 1] = temp;

    set_z_flag(registers[r16] == 0 && registers[r16 + 1] == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);
};

// for rl vs rlc : http://jgmalcolm.com/z80/advanced/shif

void cpu::rlc_r1(byte r1) {
    // rotates r1 to the left with bit 7 being moved to bit 0 and
    // also stored in the carry

    byte carry = (registers[r1] & (1 << 7)) >> 7;
    registers[r1] = (registers[r1] << 1) | carry;

    set_z_flag(registers[r1] == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(carry);
};

void cpu::rl_r1(byte r1) {
    // rotates r1 to the left with the carry's value put into bit
    // 0 and bit 7 is put into the carry

    byte carry = get_c_flag();

    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(registers[r1] & (1 << 7));

    registers[r1] = (registers[r1] << 1) | carry;

    set_z_flag(registers[r1] == 0);
};

void cpu::rrc_r1(byte r1) {
    set_h_flag(0);
    set_n_flag(0);
    set_c_flag(registers[r1] & 0x01);

    byte carry = get_c_flag();
    registers[r1] = (registers[r1] >> 1) | (carry << 7);

    set_z_flag(registers[r1] == 0);
};

void cpu::rr_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(registers[r1] & 0x01);

    byte carry = get_c_flag();
    registers[r1] = (registers[r1] >> 1) | (carry << 7);

    set_z_flag(registers[r1] == 0);
};

void cpu::sla_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag((registers[r1] & 0x80) >> 7);

    registers[r1] <<= 1;

    set_z_flag(registers[r1] == 0);
};

void cpu::sra_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(registers[r1] & 0x01);

    byte last_bit = registers[r1] & 0x80;
    registers[r1] >>= 1;
    registers[r1] |= last_bit;

    set_z_flag(registers[r1] == 0);
};

void cpu::srl_r1(byte r1) {
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(registers[r1] & 0x01);

    registers[r1] >>= 1;

    set_z_flag(registers[r1] == 0);
};

void cpu::bit_r1(byte r1, byte bit) {
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

void cpu::set_r1(byte r1, byte bit) {
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

void cpu::res_r1(byte r1, byte bit) {
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

void cpu::call_cc_nn(byte cc) {
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

void cpu::ret_cc(byte cc) {
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

byte cpu::add8(byte op1, byte op2) {
    byte res = op1 + op2;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag((op1 & 0x0F) + (op2 & 0x0F) > 0x0F);
    set_c_flag((op1 + op2) > 0xFF);

    return res;
};

byte cpu::sub8(byte op1, byte op2) {
    byte res = op1 - op2;

    set_z_flag(res == 0);
    set_n_flag(1);
    set_h_flag((op1 & 0x0F) < (op2 & 0x0F));
    set_c_flag(op1 < op2);

    return res;
};

byte cpu::and8(byte op1, byte op2) {
    byte res = op1 & op2;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag(1);
    set_c_flag(0);

    return res;
};

byte cpu::or8(byte op1, byte op2) {
    byte res = op1 | op2;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);

    return res;
};

byte cpu::xor8(byte op1, byte op2) {
    byte res = op1 ^ op2;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);

    return res;
};

void cpu::cp(byte op1, byte op2) {
    set_z_flag(op1 == op2);
    set_n_flag(1);
    set_h_flag((op1 & 0xF) < (op2 & 0xF));
    set_c_flag(op1 < op2);
};

void cpu::inc8(byte op1) {
    byte res = registers[op1] + 1;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag((registers[op1] & 0x0F) == 0x0F);

    registers[op1] = res;
};

void cpu::dec8(byte op1) {
    byte res = registers[op1] - 1;

    set_z_flag(res == 0);
    set_n_flag(1);
    set_h_flag((res & 0x0F) == 0x0F);

    registers[op1] = res;
};

word cpu::add16(word op1, word op2) {
    set_n_flag(0);
    set_h_flag((0x0FFF & op1) + (0X0FFF & op2) > 0x0FFF);
    set_c_flag((0xFFFF - op1) < op2);

    return op1 + op2;
};

void cpu::ret() {
    pc = (read_memory(sp++) | (read_memory(sp++) << 8)) - 1;
};

void cpu::store_pc_stack() {
    write_memory(--sp, ((pc + 1) & 0xFF00) >> 8);
    write_memory(--sp, ((pc + 1) & 0xFF));
};

void cpu::push16(byte r1) {
    write_memory(--sp, registers[r1]);
    write_memory(--sp, registers[r1 + 1]);
};

void cpu::pop16(byte r1) {
    registers[r1 + 1] = read_memory(sp++);
    registers[r1] = read_memory(sp++);
};

void cpu::set_z_flag(bool value) {
    registers[F] = (registers[F] & ~(1 << 7)) | (value << 7);
};

void cpu::set_n_flag(bool value) {
    registers[F] = (registers[F] & ~(1 << 6)) | (value << 6);
};

void cpu::set_h_flag(bool value) {
    registers[F] = (registers[F] & ~(1 << 5)) | (value << 5);
};

void cpu::set_c_flag(bool value) {
    registers[F] = (registers[F] & ~(1 << 4)) | (value << 4);
};

bool cpu::get_z_flag() { return registers[F] & 0x80; };

bool cpu::get_n_flag() { return registers[F] & 0x40; };

bool cpu::get_h_flag() { return registers[F] & 0x20; };

bool cpu::get_c_flag() { return registers[F] & 0x10; };
