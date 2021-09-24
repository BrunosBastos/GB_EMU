#include "cpu.h"
#include "opcodes.h"

Cpu::Cpu(Mmu* mmu) {
    this->mmu = mmu;
    pc = 0x100;
    sp = 0xFFFE;

    interrupt_master = true;
    pending_interrupt_disabled = false;
    pending_interrupt_enabled = false;
    
    reg_A = 0x01;
    reg_F = 0xB0;
    reg_C = 0x13;
    reg_E = 0xD8;
    reg_H = 0x01;
    reg_L = 0x4D;
};

void Cpu::emulate_cycle() {
    // get opcode
    opcode = mmu->read_memory(pc);
    last_clock = cycle_table[opcode];

    // decode and execute op
    execute_opcode();
    total_clock += last_clock;      // ig total_clock is not used but...

    pc++;

    if (pending_interrupt_disabled) {
        if (mmu->read_memory(pc - 1) != 0xF3) {
            interrupt_master = false;
            pending_interrupt_disabled = false;
        }
    }
    if (pending_interrupt_enabled) {
        if (mmu->read_memory(pc - 1) != 0xFB) {
            interrupt_master = true;
            pending_interrupt_enabled = false;
        }
    }
};

void Cpu::execute_opcode() {
    debug();

    (*optable[opcode])(mmu, this);
};

void Cpu::debug() {
    printf("pc: %04x  opcode: %02x  sp: %04x\n", pc, opcode, sp);
    printf("last_clock: %02i\n", last_clock);
    printf("a: %02x  f: %02x\n", reg_A, reg_F);
    printf("b: %02x  c: %02x\n", reg_B, reg_C);
    printf("d: %02x  e: %02x\n", reg_D, reg_E);
    printf("h: %02x  l: %02x\n", reg_H, reg_L);
    printf("LY: %02i\n", mmu->LY.get());
    printf("LCDC: %02x\n", mmu->LCDC.get());
    printf("\n");
};

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


void Cpu::inc16(PairRegister *reg_16) {
    (*reg_16)++;
};

void Cpu::dec16(PairRegister *reg_16) {
    (*reg_16)--;
};

void Cpu::swap8(byte *reg_8) {
    *reg_8 = (*reg_8 << 4) | (*reg_8 >> 4);

    set_z_flag(*reg_8 == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);
};

void Cpu::swap16(PairRegister *reg_16) {
    byte temp = reg_16->low();

    reg_16->low(reg_16->high());
    reg_16->high(temp);

    set_z_flag(reg_16->get() == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);
};

// for rl vs rlc : http://jgmalcolm.com/z80/advanced/shif

void Cpu::rlc8(byte *reg_8) {
    // rotates reg_8 to the left with bit 7 being moved to bit 0 and
    // also stored in the carry

    byte carry = (*reg_8 & (1 << 7)) >> 7;
    *reg_8 = (*reg_8 << 1) | carry;

    set_z_flag(*reg_8 == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(carry);
};

void Cpu::rl8(byte *reg_8) {
    // rotates reg_8 to the left with the carry's value put into bit
    // 0 and bit 7 is put into the carry

    byte carry = get_c_flag();

    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(*reg_8 & (1 << 7));

    *reg_8 = (*reg_8 << 1) | carry;

    set_z_flag(*reg_8 == 0);
};

void Cpu::rrc8(byte *reg_8) {
    set_h_flag(0);
    set_n_flag(0);
    set_c_flag(*reg_8 & 0x01);

    byte carry = get_c_flag();
    *reg_8 = (*reg_8 >> 1) | (carry << 7);

    set_z_flag(*reg_8 == 0);
};

void Cpu::rr8(byte *reg_8) {
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(*reg_8 & 0x01);

    byte carry = get_c_flag();
    *reg_8 = (*reg_8 >> 1) | (carry << 7);

    set_z_flag(*reg_8 == 0);
};

void Cpu::sla8(byte *reg_8) {
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag((*reg_8 & 0x80) >> 7);

    *reg_8 <<= 1;

    set_z_flag(*reg_8 == 0);
};

void Cpu::sra8(byte *reg_8) {
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(*reg_8 & 0x01);

    byte last_bit = *reg_8 & 0x80;
    *reg_8 >>= 1;
    *reg_8 |= last_bit;

    set_z_flag(*reg_8 == 0);
};

void Cpu::srl8(byte *reg_8) {
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(*reg_8 & 0x01);

    *reg_8 >>= 1;

    set_z_flag(*reg_8 == 0);
};

void Cpu::bit(byte *reg_8, byte bit) {
    
    set_z_flag(!(*reg_8 & (1 << bit)));
    set_n_flag(0);
    set_h_flag(1);
};

void Cpu::bit(PairRegister *reg_16, byte bit) {

    last_clock = 16;        // the clock for this operation is different
    set_z_flag(!(mmu->read_memory(reg_16->get()) & (1 << bit)));
    set_n_flag(0);
    set_h_flag(1);
};

void Cpu::set(byte *reg_8, byte bit) {
    *reg_8 |= (1 << bit);
};

void Cpu::set(PairRegister *reg_16, byte bit) {
    last_clock = 16;
    mmu->write_memory(reg_16->get(), mmu->read_memory(reg_16->get()) | (1 << bit));
};

void Cpu::res(byte *reg_8, byte bit) {
    *reg_8 &= ~(1 << bit);
};

void Cpu::res(PairRegister *reg_16, byte bit) {
    last_clock = 16;
    mmu->write_memory(reg_16->get(), mmu->read_memory(reg_16->get()) & ~(1 << bit));
};

void Cpu::add8(byte *op1, byte op2) {
    byte res = *op1 + op2;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag((*op1 & 0x0F) + (op2 & 0x0F) > 0x0F);
    set_c_flag((*op1 + op2) > 0xFF);

    *op1 = res;
};

void Cpu::sub8(byte *op1, byte op2) {
    byte res = *op1 - op2;

    set_z_flag(res == 0);
    set_n_flag(1);
    set_h_flag((*op1 & 0x0F) < (op2 & 0x0F));
    set_c_flag(*op1 < op2);

    *op1 = res;
};

void Cpu::and8(byte *op1, byte op2) {
    byte res = *op1 & op2;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag(1);
    set_c_flag(0);

    *op1 = res;
};

void Cpu::or8(byte *op1, byte op2) {
    byte res = *op1 | op2;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);

    *op1 = res;
};

void Cpu::xor8(byte *op1, byte op2) {
    byte res = *op1 ^ op2;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);

    *op1 = res;
};

void Cpu::cp8(byte *op1, byte op2) {
    printf("cp :: %i %i\n", *op1, op2);
    set_z_flag(*op1 == op2);
    set_n_flag(1);
    set_h_flag((*op1 & 0xF) < (op2 & 0xF));
    set_c_flag(*op1 < op2);
};

void Cpu::inc8(byte *op1) {
    byte res = *op1 + 1;

    set_z_flag(res == 0);
    set_n_flag(0);
    set_h_flag((*op1 & 0x0F) == 0x0F);

    *op1 = res;
};

void Cpu::dec8(byte *op1) {
    byte res = *op1 - 1;

    set_z_flag(res == 0);
    set_n_flag(1);
    set_h_flag((res & 0x0F) == 0x0F);

    *op1 = res;
};

void Cpu::add16(PairRegister *op1, word op2) {
    set_n_flag(0);
    set_h_flag((0x0FFF & op1->get()) + (0X0FFF & op2) > 0x0FFF);
    set_c_flag((0xFFFF - op1->get()) < op2);

    op1->set(op1->get() + op2);
};


void Cpu::rl16(PairRegister *reg_16) {
    byte carry = get_c_flag();
    byte value = mmu->read_memory(reg_16->get());

    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(value & (1 << 7));

    value = (value << 1) | carry;

    set_z_flag(value == 0);

    mmu->write_memory(reg_16->get(), value);
};

void Cpu::rlc16(PairRegister *reg_16) {
    // rotates reg_8 to the left with bit 7 being moved to bit 0 and
    // also stored in the carry
    byte value = mmu->read_memory(reg_16->get());

    byte carry = (value & (1 << 7)) >> 7;
    value = (value << 1) | carry;

    set_z_flag(value == 0);
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(carry);

    mmu->write_memory(reg_16->get(), value);
};

void Cpu::rrc16(PairRegister *reg_16) {
    byte value = mmu->read_memory(reg_16->get());

    set_h_flag(0);
    set_n_flag(0);
    set_c_flag(value & 0x01);

    byte carry = get_c_flag();
    value = (value >> 1) | (carry << 7);

    set_z_flag(value == 0);
    
    mmu->write_memory(reg_16->get(), value);
};

void Cpu::rr16(PairRegister *reg_16) {
    byte value = mmu->read_memory(reg_16->get());

    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(value & 0x01);

    byte carry = get_c_flag();
    value = (value >> 1) | (carry << 7);

    set_z_flag(value == 0);

    mmu->write_memory(reg_16->get(), value);
};

void Cpu::sla16(PairRegister *reg_16) {
    byte value = mmu->read_memory(reg_16->get());

    set_n_flag(0);
    set_h_flag(0);
    set_c_flag((value & 0x80) >> 7);

    value <<= 1;

    set_z_flag(value == 0);
    
    mmu->write_memory(reg_16->get(), value);
};

void Cpu::sra16(PairRegister *reg_16) {
    byte value = mmu->read_memory(reg_16->get());
    
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(value & 0x01);

    byte last_bit = value & 0x80;
    value >>= 1;
    value |= last_bit;
    
    set_z_flag(value == 0);

    mmu->write_memory(reg_16->get(), value);
};

void Cpu::srl16(PairRegister *reg_16) {
    byte value = mmu->read_memory(reg_16->get());
    
    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(value & 0x01);

    value >>= 1;

    set_z_flag(value == 0);

    mmu->write_memory(reg_16->get(), value);
};

void Cpu::ret() {
    pc = (mmu->read_memory(sp++) | (mmu->read_memory(sp++) << 8)) - 1;
};

void Cpu::store_pc_stack() {
    mmu->write_memory(--sp, ((pc + 1) & 0xFF00) >> 8);
    mmu->write_memory(--sp, ((pc + 1) & 0xFF));
};

void Cpu::push16(PairRegister *reg_16) {
    mmu->write_memory(--sp, reg_16->high());
    mmu->write_memory(--sp, reg_16->low());
};

void Cpu::pop16(PairRegister *reg_16) {
    reg_16->low(mmu->read_memory(sp++));
    reg_16->high(mmu->read_memory(sp++));
};

void Cpu::set_z_flag(bool value) {
    reg_F = (reg_F & ~(1 << 7)) | (value << 7);
};

void Cpu::set_n_flag(bool value) {
    reg_F = (reg_F & ~(1 << 6)) | (value << 6);
};

void Cpu::set_h_flag(bool value) {
    reg_F = (reg_F & ~(1 << 5)) | (value << 5);
};

void Cpu::set_c_flag(bool value) {
    reg_F = (reg_F & ~(1 << 4)) | (value << 4);
};

bool Cpu::get_z_flag() { return reg_F & 0x80; };

bool Cpu::get_n_flag() { return reg_F & 0x40; };

bool Cpu::get_h_flag() { return reg_F & 0x20; };

bool Cpu::get_c_flag() { return reg_F & 0x10; };
