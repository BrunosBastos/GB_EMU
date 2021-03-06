#include "cpu.h"
#include "opcodes.h"
#include <set>
#include <string>

std::set<int> ops;
std::set<int> ops_cb;

Cpu::Cpu(Mmu* mmu) {
    this->mmu = mmu;
    pc = 0x100;
    sp = 0xFFFE;

    interrupt_master = true;
    pending_interrupt_disabled = false;
    pending_interrupt_enabled = false;
    
    reg_A = 0x01;
    reg_F = 0xB0;
    reg_B = 0x00;
    reg_C = 0x13;
    reg_D = 0x00;
    reg_E = 0xD8;
    reg_H = 0x01;
    reg_L = 0x4D;
};

void Cpu::emulate_cycle() {

    if(halted) {
        last_clock = cycle_table[0x76].cycles;
        return;
    }
    // get opcode
    opcode = mmu->read_memory(pc);
    last_clock = cycle_table[opcode].cycles;
    
    // decode and execute op
    execute_opcode();
    total_clock += last_clock;      // ig total_clock is not used but...

    pc++;

    // debug();

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
    /*
    if(mmu->read_memory(0xff02) == 0x81) {
        printf("%c ", mmu->read_memory(0xff01));
        mmu->address[0xff02] = 0;
    }
    if(mmu->address[0xff00] == 0x10)
        printf("%02x\n",mmu->address[0xff00]);
    if(pc == 0x50) {
        printf("Timer interrupt\n");
        exit(1);
    }
    */

    //printf("opcode: %02x\n", opcode);
     if(opcode != 0xCB)
        ops.insert(opcode);
    else 
        ops_cb.insert(mmu->read_memory(pc + 1));

    if (pc == 0x40) {
        n_op++;
        //debug();
        // if(n_op > 130) {
        //     if(reg_HL.get() != 0xffa8) {
        //         printf("hl : %04x\n", reg_HL.get());
        //         exit(1);
        //     }
        // }
        //printf("%i\n", n_op);  
        //debug_tile_addr();
        //debug_map_addr();
        //if (n_op >= 40 && n_op < 100 && n_op % 10 == 0)
            //debug_dump_memory();
    }

    if(true) {
        //printf("ff80 : %02x\n", mmu->read_memory(0xff80));
        /*
        10 >
        20 <
        40 ^
        80 v
        a 02
        s 01
        E 08
        */
    }
    
    //debug();
    if (n_op == 128) {
        // FILE *fp;
        // fp = fopen("opcodes_debug.txt", "w");

        // for (int i=0; i < 0xFF; i++) {
        //     fprintf(fp, "%02x %c\n", i, ops.count(i) ? 'x' : ' ');
        // }

        // for (int i=0; i < 0xFF; i++) {
        //     fprintf(fp, "cb %02x %c\n", i, ops_cb.count(i) ? 'x' : ' ');
        // }

        // fclose(fp);
        //exit(1);
    }

    // if(opcode == 0x27) {
    //     for (auto it = ops.begin(); it != ops.end(); ++it)
    //         printf("%02x \n", *it);

    //     for (auto pt = ops_cb.begin(); pt != ops_cb.end(); ++pt)
    //         printf("cb %02x \n", *pt);
    //     exit(1);
    // }
    
    // FILE *fp;
    // fp = fopen("bad_daa.txt", "a+");
    // if(opcode == 0x27) fprintf(fp, " in %04x \n", reg_AF.get());
    (*optable[opcode])(mmu, this);
    

    // if(opcode == 0x27) fprintf(fp, "out %04x \n", reg_AF.get());
    // fclose(fp);
};


void Cpu::debug() {
    // FILE *fp;
    // fp = fopen("daa.txt", "a+");
    // fprintf(fp, "\npc: %04x\n", pc);
    // fprintf(fp, "\topcode: %02x  last_clock: %2i\n", opcode, last_clock);
    // fprintf(fp, "\taf: %02x%02x    lcdc: %02x\n", reg_A, reg_F, mmu->LCDC.get());
    // fprintf(fp, "\tbc: %02x%02x    stat: %02x\n", reg_B, reg_C, mmu->STAT.get());
    // fprintf(fp, "\tde: %02x%02x    ly:   %02x  (%3i)\n", reg_D, reg_E, mmu->LY.get(), mmu->LY.get());
    // fprintf(fp, "\thl: %02x%02x    ie:   %02x\n", reg_H, reg_L,  mmu->IE.get());
    // fprintf(fp, "\tsp: %04x    if:   %02x\n", sp, mmu->IF.get());
    // fclose(fp);

    FILE *fp;
    fp = fopen("daa.txt", "a+");
    fprintf(fp, "\npc: %04x  mmu[ff44]: %02x\n", pc, mmu->read_memory(0xff44));
    fprintf(fp, "\topcode: %02x  sp: %04x\n", opcode, sp);
    fprintf(fp, "\taf: %02x%02x  bc: %02x%02x  de: %02x%02x  hl: %02x%02x\n", reg_A, reg_F, reg_B, reg_C, reg_D, reg_E, reg_H, reg_L);
    fclose(fp);
};

void Cpu::debug_tile_addr() {
    for (int tile_addr = 0x8000; tile_addr < 0x9000; tile_addr+= 0x0010) {
        printf("%04x: ", tile_addr);
        for (int line_addr = 0; line_addr < 16; line_addr++)
            printf(" %02x", mmu->address[tile_addr + line_addr]);
        printf("\n");
    }
    printf("\n");
};

void Cpu::debug_dump_memory() {
    FILE *fp;
    std::string s = "mem" + std::to_string(n_op) + ".txt";
    char *arr = &s[0];
    fp = fopen(arr, "w");

    for (int i = 0; i < 0x10000; i++) {
        if (i % 16 == 0)
            fprintf(fp, "\n%04x: ", i);
        fprintf(fp, "%02x ", mmu->address[i]);
    }
    fclose(fp);
}

void Cpu::debug_map_addr() {
    for (int tile_addr = 0x9800; tile_addr < 0x9A40; tile_addr+= 0x0010) {
        printf("%04x: ", tile_addr);
        for (int line_addr = 0; line_addr < 16; line_addr++)
            printf(" %02x", mmu->address[tile_addr + line_addr]);
        printf("\n");
    }
    printf("\n");
};

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


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
    set_n_flag(0);
    set_h_flag(0);
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
    set_c_flag(*reg_8 & 0x80);

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

    last_clock = 5;        // the clock for this operation is different
    set_z_flag(!(mmu->read_memory(reg_16->get()) & (1 << bit)));
    set_n_flag(0);
    set_h_flag(1);
};

void Cpu::set(byte *reg_8, byte bit) {
    *reg_8 |= (1 << bit);
};

void Cpu::set(PairRegister *reg_16, byte bit) {
    last_clock = 5;
    mmu->write_memory(reg_16->get(), mmu->read_memory(reg_16->get()) | (1 << bit));
};

void Cpu::res(byte *reg_8, byte bit) {
    *reg_8 &= ~(1 << bit);
};

void Cpu::res(PairRegister *reg_16, byte bit) {
    last_clock = 5;
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

    op1->set((op1->get() + op2) & 0xFFFF);
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
