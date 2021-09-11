
#include <stdio.h>
#include "opcodes.h"


void cpu::initialize(mmu* mmu) {

    pc = 0x100; // pag 63
    memory = mmu;

}

void cpu::emulate_cycle() {

    // get opcode

    opcode = memory->address[pc];

    // decode and execute op
    if(pc == 0x38)
        exit(0);
    execute_opcode();

    pc += 1;

}


//optable[0xCB] = &cpu::CB;  FIXME:


void cpu::execute_opcode() {
    printf("opcode: %02x \n", opcode);

    printf("%p\n",*optable[opcode]);
    (*optable[opcode])(memory, this);
}



//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


void cpu::pop_nn(byte r16) {
    // TODO: not sure about the order
    
};


void cpu::subc_a_pc() {
    // TODO:: n tem sitio xD
    registers[A] = sub8(registers[A], memory->address[pc] + get_c_flag());
};

void cpu::add_hl_r16(byte r16) {

    unsigned short res = 
        add16(registers[H] | (registers[L] << 8), registers[r16] | (registers[r16 + 1] << 8));

    registers[H] = 0xFF;
    registers[L] = 0xFF00 >> 8;
};

void cpu::add_hl_sp() {
    
    unsigned short res = 
        add16(registers[H] | (registers[L] << 8), sp);

    registers[H] = res & 0xFF;
    registers[L] = (res & 0xFF00) >> 8;    
};

void cpu::add_sp_pc() {
    // TODO: mal
    sp = add16(sp, memory->address[pc]);
};

void cpu::inc_r16(byte r16) {
    unsigned short res = inc16(registers[r16] | (registers[r16 + 1] << 8));
    registers[r16] = res & 0xFF;
    registers[r16 + 1] = (res & 0xFF00) >> 8;    
};

void cpu::dec_r16(byte r16) {
    unsigned short res = dec16(registers[r16] | (registers[r16 + 1] << 8));
    registers[r16] = res & 0xFF;
    registers[r16 + 1] = (res & 0xFF00) >> 8;    
};


void cpu::swap_r1(byte r1) {

    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);

    registers[r1] = (registers[r1] << 4) | (registers[r1] >> 4);
    if(registers[r1] == 0) set_z_flag(1);

};

void cpu::swap_r16(byte r16) {

    set_n_flag(0);
    set_h_flag(0);
    set_c_flag(0);
    
    byte temp = registers[r16];

    registers[r16] = registers[r16 + 1];
    registers[r16 + 1] = temp;
    if(registers[r16] == 0 && registers[r16 + 1] == 0) set_z_flag(1);

};



// for rl vs rlc : http://jgmalcolm.com/z80/advanced/shif

void cpu::rlc_r1(byte r1) {

    set_n_flag(0);
    set_h_flag(0);

    if(registers[r1] == 0x80) {
        set_z_flag(1);
        set_c_flag(1);
    }
    else if(registers[r1] & 0x80) {
        set_c_flag(1);
    }
    else {
        set_c_flag(0);
    }

    byte carry = get_c_flag() >> 6;
    registers[r1] = (registers[r1] << 1) | carry;
};


void cpu::rl_r1(byte r1) {

    set_n_flag(0);
    set_h_flag(0);
    byte carry = get_c_flag() >> 6;

    if(registers[r1] == 0x80) {
        set_z_flag(1);
    }
    
    if(registers[r1] & 0x80) {
        set_c_flag(1);
    }
    else {
        set_c_flag(0);
    }

    registers[r1] = (registers[r1] << 1) | carry;

};

void cpu::rrc_r1(byte r1) {

    set_n_flag(0);
    set_h_flag(0);

    if(registers[r1] == 0x01) set_z_flag(1);

    if(registers[r1] & 0x01) 
        set_c_flag(1);
    else 
        set_c_flag(0);    
    
    byte carry = registers[r1] & 0x01;
    registers[r1] =  (registers[r1] >> 1) | (carry << 7); 
};

void cpu::rr_r1(byte r1) {

    set_n_flag(0);
    set_h_flag(0);
    byte carry = get_c_flag() >> 6;

    if(registers[r1] == 0x01) set_z_flag(1);

    if(registers[r1] & 0x01) 
        set_c_flag(1);
    else 
        set_c_flag(0);    
    
    registers[r1] =  (registers[r1] >> 1) | (carry << 7); 
};

void cpu::sla_r1(byte r1) {

    set_n_flag(0);
    set_h_flag(0);

    if(registers[r1] & 0x80)
        set_c_flag(1);
    else
        set_c_flag(0);  

    registers[r1] <<= 1;
    if(registers[r1] == 0) set_z_flag(1);
};

void cpu::sra_r1(byte r1) {

    set_n_flag(0);
    set_h_flag(0);

    if(registers[r1] & 0x01) 
        set_c_flag(1);
    else
        set_c_flag(0);

    byte last_bit = registers[r1] & 0x80;
    registers[r1] >>= 1;
    registers[r1] |= last_bit;

    if(registers[r1] == 0) set_z_flag(1);
};

void cpu::srl_r1(byte r1) {

    set_n_flag(0);
    set_h_flag(0);

    if(registers[r1] & 0x01) 
        set_c_flag(1);
    else
        set_c_flag(0);

    registers[r1] >>= 1;

    if(registers[r1] == 0) set_z_flag(1);

};

void cpu::bit_r1(byte r1, byte bit) {

    set_n_flag(0);
    set_h_flag(1); 

    if(!(registers[r1] & (1 << bit))) set_z_flag(1);
};

void cpu::set_r1(byte r1, byte bit) {
    registers[r1] |= (1 << bit);
};

void cpu::res_r1(byte r1, byte bit) {
    registers[r1] &= ~(1 << bit);
};



void cpu::call_cc_nn(byte cc) {

    unsigned short nn = memory->address[memory->address[++pc] | (memory->address[++pc] << 8)];

    if(cc == 0 && !get_z_flag()) {
        stack[--sp] = pc;
        pc = nn;
    }
    else if(cc == 1 && get_z_flag()) {
        stack[--sp] = pc;
        pc = nn;
    }
    else if(cc == 2 && !get_c_flag()) {
        stack[--sp] = pc;
        pc = nn;
    }
    else if(cc == 3 && get_c_flag()) {
        stack[--sp] = pc;
        pc = nn;    
    }
};  

void cpu::ret_cc(byte cc) {
    if(cc == 0 && !get_z_flag()) {
        pc = stack[sp++];
    }
    else if(cc == 1 && get_z_flag()) {
        pc = stack[sp++];
    }
    else if(cc == 2 && !get_c_flag()) {
        pc = stack[sp++];
    }
    else if(cc == 3 && get_c_flag()) {
        pc = stack[sp++];    
    }
};


byte cpu::add8(byte op1, byte op2) {

    set_n_flag(0);

    byte res = op1 + op2;
    
    if(res == 0) {
        set_z_flag(1);
    }

    if((op1 + op2) > 0xFF) {
        set_c_flag(1);
    }

    if((op1 & 0x0F) + (op2 & 0x0F) > 0x0F ) {
        set_h_flag(1);
    } 

    return res;
};

byte cpu::sub8(byte op1, byte op2) {

    set_n_flag(1);

    byte res = op1 - op2;

    if(res == 0) {
        set_z_flag(1);
    }

    if(op2 < op1) {
        set_c_flag(1);
    }

    if((op2 & 0x0F) < (op1 & 0x0F)) {
        set_h_flag(1);
    }
    return res;
};

byte cpu::and8(byte op1, byte op2) {

    set_c_flag(0);
    set_h_flag(1);
    set_n_flag(0);

    byte res = op1 & op2;

    if(res == 0) set_z_flag(1);
    
    return res;
};

byte cpu::or8(byte op1, byte op2) {

    set_c_flag(0);
    set_h_flag(0);
    set_n_flag(0);

    byte res = op1 | op2;

    if(res == 0) set_z_flag(1);

    return res;
};

byte cpu::xor8(byte op1, byte op2) {

    set_c_flag(0);
    set_h_flag(0);
    set_n_flag(0);

    byte res = op1 ^ op2;

    if(res == 0) set_z_flag(1);

    return res;
};

void cpu::cp(byte op1, byte op2) {

    set_n_flag(1);

    if(op1 == op2) set_z_flag(1);

    if(op1 < op2) set_c_flag(1);

    if((op1 & 0xF) < (op2 & 0xF)) set_h_flag(1);

};

byte cpu::inc8(byte op1) {

    set_n_flag(0);

    byte res = op1 + 1;

    if(res == 0) set_z_flag(1);

    if(op1 & 0x0F) set_h_flag(1);

    return res;
};

byte cpu::dec8(byte op1) {

    set_n_flag(1);

    byte res = op1 - 1;

    if(res == 0) set_z_flag(1);

    if((res & 0x0F) == 0x0F) set_c_flag(1);      // not sure

    return res;
};


unsigned short cpu::add16(unsigned short op1, unsigned short op2) {
    // this operation uses the values of the registers and not the addresses

    set_n_flag(0);

    if((0xFFFF - op1) < op2) set_c_flag(1);

    if((0x0FFF & op1) + (0X0FFF & op2) > 0x0FFF) set_h_flag(1);  // not sure

    return op1 + op2;
};

unsigned short cpu::inc16(unsigned short op1) {
    // no flags are affected making this function kinda useless
    return op1 + 1;
};

unsigned short cpu::dec16(unsigned short op1) {
    // no flags are affected making this function kinda useless
    return op1 - 1;
};



void cpu::set_z_flag(byte value) {
    registers[F] |= (registers[F] & ~(1 << 7)) | (value << 7);
};

void cpu::set_n_flag(byte value) {
    registers[F] |= (registers[F] & ~(1 << 6)) | (value << 6);
};

void cpu::set_h_flag(byte value) {
    registers[F] |= (registers[F] & ~(1 << 5)) | (value << 5);
};

void cpu::set_c_flag(byte value) {
    registers[F] |= (registers[F] & ~(1 << 4)) | (value << 4);
};



bool cpu::get_z_flag() {
    return registers[F] & 0x80;
};

bool cpu::get_n_flag() {
    return registers[F] & 0x40;
};

bool cpu::get_h_flag() {
    return registers[F] & 0x20;
};

bool cpu::get_c_flag() {
    return registers[F] & 0x10;
};
