
#include <stdio.h>
#include "cpu.h"

void cpu::initialize(mmu* mmu) {

    pc = 0x100; // pag 63
    memory = mmu;

    cpu_init_table();

}

void cpu::emulate_cycle() {

    // get opcode

    opcode = memory->address[pc];

    // decode and execute op

    execute_opcode();

    pc += 1;

}

void cpu::cpu_init_table() {

    optable[0x00] = &cpu::op_00;
    optable[0x01] = &cpu::op_01;
    optable[0x02] = &cpu::op_02;
    optable[0x03] = &cpu::op_03;
    optable[0x04] = &cpu::op_04;
    optable[0x05] = &cpu::op_05;
    optable[0x06] = &cpu::op_06;
    optable[0x07] = &cpu::op_07;
    optable[0x08] = &cpu::op_08;
    optable[0x09] = &cpu::op_09;
    optable[0x0A] = &cpu::op_0A;
    optable[0x0B] = &cpu::op_0B;
    optable[0x0C] = &cpu::op_0C;
    optable[0x0D] = &cpu::op_0D;
    optable[0x0E] = &cpu::op_0E;
    optable[0x0F] = &cpu::op_0F;

    optable[0x11] = &cpu::op_11;
    optable[0x12] = &cpu::op_12;
    optable[0x13] = &cpu::op_13;
    optable[0x14] = &cpu::op_14;
    optable[0x15] = &cpu::op_15;
    optable[0x16] = &cpu::op_16;
    optable[0x17] = &cpu::op_17;
    optable[0x19] = &cpu::op_19;
    optable[0x18] = &cpu::op_18;
    optable[0x1A] = &cpu::op_1A;
    optable[0x1B] = &cpu::op_1B;
    optable[0x1C] = &cpu::op_1C;
    optable[0x1D] = &cpu::op_1D;
    optable[0x1E] = &cpu::op_1E;
    optable[0x1F] = &cpu::op_1F;

    optable[0x20] = &cpu::op_20;
    optable[0x21] = &cpu::op_21;
    optable[0x22] = &cpu::op_22;
    optable[0x23] = &cpu::op_23;
    optable[0x24] = &cpu::op_24;
    optable[0x25] = &cpu::op_25;
    optable[0x26] = &cpu::op_26;
    optable[0x27] = &cpu::op_27;
    optable[0x28] = &cpu::op_28;
    optable[0x29] = &cpu::op_29;
    optable[0x2A] = &cpu::op_2A;
    optable[0x2B] = &cpu::op_2B;
    optable[0x2C] = &cpu::op_2C;
    optable[0x2D] = &cpu::op_2D;
    optable[0x2E] = &cpu::op_2E;
    optable[0x2F] = &cpu::op_2F;

    optable[0x30] = &cpu::op_30;
    optable[0x31] = &cpu::op_31;
    optable[0x32] = &cpu::op_32;
    optable[0x33] = &cpu::op_33;
    optable[0x34] = &cpu::op_34;
    optable[0x35] = &cpu::op_35;
    optable[0x36] = &cpu::op_36;
    optable[0x37] = &cpu::op_37;
    optable[0x38] = &cpu::op_38;
    optable[0x39] = &cpu::op_39;
    optable[0x3A] = &cpu::op_3A;
    optable[0x3B] = &cpu::op_3B;
    optable[0x3C] = &cpu::op_3C;
    optable[0x3D] = &cpu::op_3D;
    optable[0x3E] = &cpu::op_3E;
    optable[0x3F] = &cpu::op_3F;

    optable[0x40] = &cpu::op_40;
    optable[0x41] = &cpu::op_41;
    optable[0x42] = &cpu::op_42;
    optable[0x43] = &cpu::op_43;
    optable[0x44] = &cpu::op_44;
    optable[0x45] = &cpu::op_45;
    optable[0x46] = &cpu::op_46;
    optable[0x47] = &cpu::op_47;
    optable[0x48] = &cpu::op_48;
    optable[0x49] = &cpu::op_49;
    optable[0x4A] = &cpu::op_4A;
    optable[0x4B] = &cpu::op_4B;
    optable[0x4C] = &cpu::op_4C;
    optable[0x4D] = &cpu::op_4D;
    optable[0x4E] = &cpu::op_4E;
    optable[0x4F] = &cpu::op_4F;

    optable[0x50] = &cpu::op_50;
    optable[0x51] = &cpu::op_51;
    optable[0x52] = &cpu::op_52;
    optable[0x53] = &cpu::op_53;
    optable[0x54] = &cpu::op_54;
    optable[0x55] = &cpu::op_55;
    optable[0x56] = &cpu::op_56;
    optable[0x57] = &cpu::op_57;
    optable[0x58] = &cpu::op_58;
    optable[0x59] = &cpu::op_59;
    optable[0x5A] = &cpu::op_5A;
    optable[0x5B] = &cpu::op_5B;
    optable[0x5C] = &cpu::op_5C;
    optable[0x5D] = &cpu::op_5D;
    optable[0x5E] = &cpu::op_5E;
    optable[0x5F] = &cpu::op_5F;

    optable[0x60] = &cpu::op_60;
    optable[0x61] = &cpu::op_61;
    optable[0x62] = &cpu::op_62;
    optable[0x63] = &cpu::op_63;
    optable[0x64] = &cpu::op_64;
    optable[0x65] = &cpu::op_65;
    optable[0x66] = &cpu::op_66;
    optable[0x67] = &cpu::op_67;
    optable[0x68] = &cpu::op_68;
    optable[0x69] = &cpu::op_69;
    optable[0x6A] = &cpu::op_6A;
    optable[0x6B] = &cpu::op_6B;
    optable[0x6C] = &cpu::op_6C;
    optable[0x6D] = &cpu::op_6D;
    optable[0x6E] = &cpu::op_6E;
    optable[0x6F] = &cpu::op_6F;

    optable[0x70] = &cpu::op_70;
    optable[0x71] = &cpu::op_71;
    optable[0x72] = &cpu::op_72;
    optable[0x73] = &cpu::op_73;
    optable[0x74] = &cpu::op_74;
    optable[0x75] = &cpu::op_75;
    optable[0x76] = &cpu::op_76;
    optable[0x77] = &cpu::op_77;
    optable[0x78] = &cpu::op_78;
    optable[0x79] = &cpu::op_79;
    optable[0x7A] = &cpu::op_7A;
    optable[0x7B] = &cpu::op_7B;
    optable[0x7C] = &cpu::op_7C;
    optable[0x7D] = &cpu::op_7D;
    optable[0x7E] = &cpu::op_7E;
    optable[0x7F] = &cpu::op_7F;

    optable[0x80] = &cpu::op_80;
    optable[0x81] = &cpu::op_81;
    optable[0x82] = &cpu::op_82;
    optable[0x83] = &cpu::op_83;
    optable[0x84] = &cpu::op_84;
    optable[0x85] = &cpu::op_85;
    optable[0x86] = &cpu::op_86;
    optable[0x87] = &cpu::op_87;
    optable[0x88] = &cpu::op_88;
    optable[0x89] = &cpu::op_89;
    optable[0x8A] = &cpu::op_8A;
    optable[0x8B] = &cpu::op_8B;
    optable[0x8C] = &cpu::op_8C;
    optable[0x8D] = &cpu::op_8D;
    optable[0x8E] = &cpu::op_8E;
    optable[0x8F] = &cpu::op_8F;

    optable[0x90] = &cpu::op_90;
    optable[0x91] = &cpu::op_91;
    optable[0x92] = &cpu::op_92;
    optable[0x93] = &cpu::op_93;
    optable[0x94] = &cpu::op_94;
    optable[0x95] = &cpu::op_95;
    optable[0x96] = &cpu::op_96;
    optable[0x97] = &cpu::op_97;
    optable[0x98] = &cpu::op_98;
    optable[0x99] = &cpu::op_99;
    optable[0x9A] = &cpu::op_9A;
    optable[0x9B] = &cpu::op_9B;
    optable[0x9C] = &cpu::op_9C;
    optable[0x9D] = &cpu::op_9D;
    optable[0x9E] = &cpu::op_9E;
    optable[0x9F] = &cpu::op_9F;

    optable[0xA0] = &cpu::op_A0;
    optable[0xA1] = &cpu::op_A1;
    optable[0xA2] = &cpu::op_A2;
    optable[0xA3] = &cpu::op_A3;
    optable[0xA4] = &cpu::op_A4;
    optable[0xA5] = &cpu::op_A5;
    optable[0xA6] = &cpu::op_A6;
    optable[0xA7] = &cpu::op_A7;
    optable[0xA8] = &cpu::op_A8;
    optable[0xA9] = &cpu::op_A9;
    optable[0xAA] = &cpu::op_AA;
    optable[0xAB] = &cpu::op_AB;
    optable[0xAC] = &cpu::op_AC;
    optable[0xAD] = &cpu::op_AD;
    optable[0xAE] = &cpu::op_AE;
    optable[0xAF] = &cpu::op_AF;

    optable[0xB0] = &cpu::op_B0;
    optable[0xB1] = &cpu::op_B1;
    optable[0xB2] = &cpu::op_B2;
    optable[0xB3] = &cpu::op_B3;
    optable[0xB4] = &cpu::op_B4;
    optable[0xB5] = &cpu::op_B5;
    optable[0xB6] = &cpu::op_B6;
    optable[0xB7] = &cpu::op_B7;
    optable[0xB8] = &cpu::op_B8;
    optable[0xB9] = &cpu::op_B9;
    optable[0xBA] = &cpu::op_BA;
    optable[0xBB] = &cpu::op_BB;
    optable[0xBC] = &cpu::op_BC;
    optable[0xBD] = &cpu::op_BD;
    optable[0xBE] = &cpu::op_BE;
    optable[0xBF] = &cpu::op_BF;

    optable[0xC0] = &cpu::op_C0;
    optable[0xC1] = &cpu::op_C1;
    optable[0xC2] = &cpu::op_C2;
    optable[0xC3] = &cpu::op_C3;
    optable[0xC5] = &cpu::op_C5;
    optable[0xC6] = &cpu::op_C6;
    optable[0xC7] = &cpu::op_C7;
    optable[0xC8] = &cpu::op_C8;
    optable[0xC9] = &cpu::op_C9;
    optable[0xCA] = &cpu::op_CA;
    optable[0xCD] = &cpu::op_CD;
    optable[0xCF] = &cpu::op_CF;

    optable[0xD0] = &cpu::op_D0;
    optable[0xD1] = &cpu::op_D1;
    optable[0xD2] = &cpu::op_D2;
    optable[0xD5] = &cpu::op_D5;
    optable[0xD7] = &cpu::op_D7;
    optable[0xD8] = &cpu::op_D8;
    optable[0xD9] = &cpu::op_D9;
    optable[0xDA] = &cpu::op_DA;
    optable[0xDF] = &cpu::op_DF;

    optable[0xE0] = &cpu::op_E0;
    optable[0xE1] = &cpu::op_E1;
    optable[0xE2] = &cpu::op_E2;
    optable[0xE5] = &cpu::op_E5;
    optable[0xE6] = &cpu::op_E6;
    optable[0xE7] = &cpu::op_E7;
    optable[0xE8] = &cpu::op_E8;
    optable[0xE9] = &cpu::op_E9;
    optable[0xEA] = &cpu::op_EA;
    optable[0xEF] = &cpu::op_EF;

    optable[0xF0] = &cpu::op_F0;
    optable[0xF1] = &cpu::op_F1;
    optable[0xF2] = &cpu::op_F2;
    optable[0xF3] = &cpu::op_F3;
    optable[0xF5] = &cpu::op_F5;
    optable[0xF7] = &cpu::op_F7;
    optable[0xFA] = &cpu::op_FA;
    optable[0xFB] = &cpu::op_FB;
    optable[0xFE] = &cpu::op_FE;
    optable[0xFF] = &cpu::op_FF;

    cpu_init_table_cb();
    optable[0xCB] = &cpu::op_CB;
}

void cpu::cpu_init_table_cb() {
    optable_cb[0x00] = &cpu::op_CB_00;
    optable_cb[0x01] = &cpu::op_CB_01;
    optable_cb[0x02] = &cpu::op_CB_02;
    optable_cb[0x03] = &cpu::op_CB_03;
    optable_cb[0x04] = &cpu::op_CB_04;
    optable_cb[0x05] = &cpu::op_CB_05;
    optable_cb[0x06] = &cpu::op_CB_06;
    optable_cb[0x07] = &cpu::op_CB_07;
    optable_cb[0x08] = &cpu::op_CB_08;
    optable_cb[0x09] = &cpu::op_CB_09;
    optable_cb[0x0a] = &cpu::op_CB_0A;
    optable_cb[0x0b] = &cpu::op_CB_0B;
    optable_cb[0x0c] = &cpu::op_CB_0C;
    optable_cb[0x0d] = &cpu::op_CB_0D;
    optable_cb[0x0e] = &cpu::op_CB_0E;
    optable_cb[0x0f] = &cpu::op_CB_0F;

    optable_cb[0x10] = &cpu::op_CB_10;
    optable_cb[0x11] = &cpu::op_CB_11;
    optable_cb[0x12] = &cpu::op_CB_12;
    optable_cb[0x13] = &cpu::op_CB_13;
    optable_cb[0x14] = &cpu::op_CB_14;
    optable_cb[0x15] = &cpu::op_CB_15;
    optable_cb[0x16] = &cpu::op_CB_16;
    optable_cb[0x17] = &cpu::op_CB_17;
    optable_cb[0x18] = &cpu::op_CB_18;
    optable_cb[0x19] = &cpu::op_CB_19;
    optable_cb[0x1A] = &cpu::op_CB_1A;
    optable_cb[0x1B] = &cpu::op_CB_1B;
    optable_cb[0x1C] = &cpu::op_CB_1C;
    optable_cb[0x1D] = &cpu::op_CB_1D;
    optable_cb[0x1E] = &cpu::op_CB_1E;
    optable_cb[0x1F] = &cpu::op_CB_1F;

    optable_cb[0x20] = &cpu::op_CB_20;
    optable_cb[0x21] = &cpu::op_CB_21;
    optable_cb[0x22] = &cpu::op_CB_22;
    optable_cb[0x23] = &cpu::op_CB_23;
    optable_cb[0x24] = &cpu::op_CB_24;
    optable_cb[0x25] = &cpu::op_CB_25;
    optable_cb[0x26] = &cpu::op_CB_26;
    optable_cb[0x27] = &cpu::op_CB_27;
    optable_cb[0x28] = &cpu::op_CB_28;
    optable_cb[0x29] = &cpu::op_CB_29;
    optable_cb[0x2A] = &cpu::op_CB_2A;
    optable_cb[0x2B] = &cpu::op_CB_2B;
    optable_cb[0x2C] = &cpu::op_CB_2C;
    optable_cb[0x2D] = &cpu::op_CB_2D;
    optable_cb[0x2E] = &cpu::op_CB_2E;
    optable_cb[0x2F] = &cpu::op_CB_2F;

    optable_cb[0x30] = &cpu::op_CB_30;
    optable_cb[0x31] = &cpu::op_CB_31;
    optable_cb[0x32] = &cpu::op_CB_32;
    optable_cb[0x33] = &cpu::op_CB_33;
    optable_cb[0x34] = &cpu::op_CB_34;
    optable_cb[0x35] = &cpu::op_CB_35;
    optable_cb[0x36] = &cpu::op_CB_36;
    optable_cb[0x37] = &cpu::op_CB_37;
    optable_cb[0x38] = &cpu::op_CB_38;
    optable_cb[0x39] = &cpu::op_CB_39;
    optable_cb[0x3A] = &cpu::op_CB_3A;
    optable_cb[0x3B] = &cpu::op_CB_3B;
    optable_cb[0x3C] = &cpu::op_CB_3C;
    optable_cb[0x3D] = &cpu::op_CB_3D;
    optable_cb[0x3E] = &cpu::op_CB_3E;
    optable_cb[0x3F] = &cpu::op_CB_3F;
}

void cpu::execute_opcode() {
    printf("opcode: %02x \n", opcode);

    if(true) {
        //cb
        if(opcode >= 0xC0) {
            op_set_r1(opcode & 0x07, opcode & 0x38);
        }
        else if(opcode < 0xC0 && opcode >= 0x80) {
            op_res_r1(opcode & 0x07, opcode & 0x38);
        }
        else if(opcode < 0x80 && opcode >= 0x40) {
            op_bit_r1(opcode & 0x07, opcode & 0x38);
        }
        else {
            (this->*optable_cb[opcode])();
            
            // opfunc_t* opfunc = &optable[op];
            // (*opfunc->func)(cpu, mmu);
        }
    }
    else{
        (this->*optable[opcode])();
    }
}


void cpu::op_00() {
    ;
};

void cpu::op_01() {
    registers[B] = memory->address[++pc];
    registers[C] = memory->address[++pc];
};

void cpu::op_02() {
    memory->address[registers[B] | (registers[C] << 8)] = registers[A];
};

void cpu::op_03() {
    op_inc_r16(B);
};

void cpu::op_04() {
    registers[B] = inc8(registers[B]);
};

void cpu::op_05() {
    registers[B] = dec8(registers[B]);
};

void cpu::op_06() {
    registers[B] = memory->address[++pc];
};

void cpu::op_07() {
    op_rlc_r1(A);
};

void cpu::op_08() {
    memory->address[memory->address[++pc] | (memory->address[++pc] << 8)] = sp;
};

void cpu::op_09() {
    op_add_hl_r16(B);
};

void cpu::op_0A() {
    registers[A] = memory->address[registers[B] | (registers[C] << 8)];
};

void cpu::op_0B() {
    op_dec_r16(B);
};

void cpu::op_0C() {
    registers[C] = inc8(registers[C]);
};

void cpu::op_0D() {
    registers[C] = dec8(registers[C]);
};

void cpu::op_0E() {
    registers[C] = memory->address[++pc];
};

void cpu::op_0F() {

};

void cpu::op_11() {
    registers[D] = memory->address[++pc];
    registers[E] = memory->address[++pc];
};

void cpu::op_12() {
    memory->address[registers[D] | (registers[E] << 8)] = registers[A];
};

void cpu::op_13() {
    op_inc_r16(D);
};

void cpu::op_14() {
    registers[D] = inc8(registers[D]);
};

void cpu::op_15() {
    registers[D] = dec8(registers[D]);
};

void cpu::op_16() {
    registers[D] = memory->address[++pc];
};

void cpu::op_17() {
    op_rl_r1(A);
};

void cpu::op_18() {
    pc += memory->address[++pc];
};

void cpu::op_19() {
    op_add_hl_r16(D);
};

void cpu::op_1A() {
    registers[A] = memory->address[registers[D] | (registers[E] << 8)];
};

void cpu::op_1B() {
    op_dec_r16(D);
};

void cpu::op_1C() {
    registers[E] = inc8(registers[E]);
};

void cpu::op_1D() {
    registers[E] = dec8(registers[E]);
};

void cpu::op_1E() {
    registers[E] = memory->address[++pc];
};

void cpu::op_1F() {
    op_rr_r1(A);
};

void cpu::op_20() {
    if(!get_z_flag()) 
        pc += memory->address[++pc];
};

void cpu::op_21() {
    registers[H] = memory->address[++pc];
    registers[L] = memory->address[++pc];
};

void cpu::op_22() {
    unsigned short hl = registers[H] | (registers[L] << 8);
    memory->address[hl++] = registers[A];
    registers[H] = hl & 0x00FF;
    registers[L] = (hl & 0xFF00) >> 8;
};

void cpu::op_23() {
    op_inc_r16(H);
};

void cpu::op_24() {
    registers[H] = inc8(registers[H]);
};

void cpu::op_25() {
    registers[H] = dec8(registers[H]);
};

void cpu::op_26() {
    registers[H] = memory->address[++pc];
};

void cpu::op_27() {

};

void cpu::op_28() {
    if(get_z_flag()) 
        pc += memory->address[++pc];
};

void cpu::op_29() {
    op_add_hl_r16(H);
};

void cpu::op_2A() {
    unsigned short hl = registers[H] | (registers[L] << 8);
    registers[A] = memory->address[hl++];
    registers[H] = hl & 0x00FF;
    registers[L] = (hl & 0xFF00) >> 8;
};

void cpu::op_2B() {
    op_dec_r16(H);
};

void cpu::op_2C() {
    registers[L] = inc8(registers[L]);
};

void cpu::op_2D() {
    registers[L] = dec8(registers[L]);
};

void cpu::op_2E() {
    registers[E] = memory->address[++pc];
};

void cpu::op_2F() {
    set_n_flag();
    set_h_flag();

    registers[A] = ~registers[A];
};

void cpu::op_30() {
    if(!get_c_flag()) 
        pc += memory->address[++pc];
};

void cpu::op_31() {
    sp = memory->address[++pc] | (memory->address[++pc] << 8);
};

void cpu::op_32() {
    unsigned short hl = registers[H] | (registers[L] << 8);
    memory->address[hl--] = registers[A];
    registers[H] = hl & 0x00FF;
    registers[L] = (hl & 0xFF00) >> 8;
};

void cpu::op_33() {
    
};

void cpu::op_34() {

};

void cpu::op_35() {

};

void cpu::op_36() {
    memory->address[registers[H] | (registers[L] << 8)] = memory->address[++pc];
};

void cpu::op_37() {
    reset_n_flag();
    reset_h_flag();
    set_c_flag();
};

void cpu::op_38() {
    if(get_c_flag()) 
        pc += memory->address[++pc];
};

void cpu::op_39() {
    op_add_hl_sp();
};

void cpu::op_3A() {
    unsigned short hl = registers[H] | (registers[L] << 8);
    registers[A] = memory->address[hl--];
    registers[H] = hl & 0x00FF;
    registers[L] = (hl & 0xFF00) >> 8;
};

void cpu::op_3B() {

};

void cpu::op_3C() {
    registers[A] = inc8(registers[A]);
};

void cpu::op_3D() {
    registers[A] = dec8(registers[A]);
};

void cpu::op_3E() {
    registers[A] = memory->address[pc];
};

void cpu::op_3F() {
    reset_n_flag();
    reset_h_flag();

    if(get_c_flag()) 
        reset_c_flag();
    else 
        set_c_flag();
};

void cpu::op_40() {
    registers[B] = registers[B];
};

void cpu::op_41() {
    registers[B] = registers[C];
};

void cpu::op_42() {
    registers[B] = registers[D];
};

void cpu::op_43() {
    registers[B] = registers[E];
};

void cpu::op_44() {
    registers[B] = registers[H];
};

void cpu::op_45() {
    registers[B] = registers[L];
};

void cpu::op_46() {
    registers[B] = memory->address[registers[H] | (registers[L] << 8)];
};

void cpu::op_47() {
    registers[B] = registers[A];
};

void cpu::op_48() {
    registers[C] = registers[B];
};

void cpu::op_49() {
    registers[C] = registers[C];
};

void cpu::op_4A() {
    registers[C] = registers[D];
};

void cpu::op_4B() {
    registers[C] = registers[E];
};

void cpu::op_4C() {
    registers[C] = registers[H];
};

void cpu::op_4D() {
    registers[C] = registers[L];
};

void cpu::op_4E() {
    registers[C] = memory->address[registers[H] | (registers[L] << 8)];
};

void cpu::op_4F() {
    registers[C] = registers[A];
};

void cpu::op_50() {
    registers[D] = registers[B];
};

void cpu::op_51() {
    registers[D] = registers[C];
};

void cpu::op_52() {
    registers[D] = registers[D];
};

void cpu::op_53() {
    registers[D] = registers[E];
};

void cpu::op_54() {
    registers[D] = registers[H];
};

void cpu::op_55() {
    registers[D] = registers[L];
};

void cpu::op_56() {
    registers[D] = memory->address[registers[H] | (registers[L] << 8)];
};

void cpu::op_57() {
    registers[D] = registers[A];
};

void cpu::op_58() {
    registers[E] = registers[B];
};

void cpu::op_59() {
    registers[E] = registers[C];
};

void cpu::op_5A() {
    registers[E] = registers[D];
};

void cpu::op_5B() {
    registers[E] = registers[E];
};

void cpu::op_5C() {
    registers[E] = registers[H];
};

void cpu::op_5D() {
    registers[E] = registers[L];
};

void cpu::op_5E() {
    registers[E] = memory->address[registers[H] | (registers[L] << 8)];
};

void cpu::op_5F() {
    registers[E] = registers[A];
};

void cpu::op_60() {
    registers[H] = registers[B];
};

void cpu::op_61() {
    registers[H] = registers[C];
};

void cpu::op_62() {
    registers[H] = registers[D];
};

void cpu::op_63() {
    registers[H] = registers[E];
};

void cpu::op_64() {
    registers[H] = registers[H];
};

void cpu::op_65() {
    registers[H] = registers[L];
};

void cpu::op_66() {
    registers[H] = memory->address[registers[H] | (registers[L] << 8)];
};

void cpu::op_67() {
    registers[H] = registers[A];
};

void cpu::op_68() {
    registers[L] = registers[B];
};

void cpu::op_69() {
    registers[L] = registers[C];
};

void cpu::op_6A() {
    registers[L] = registers[D];
};

void cpu::op_6B() {
    registers[L] = registers[E];
};

void cpu::op_6C() {
    registers[L] = registers[H];
};

void cpu::op_6D() {
    registers[L] = registers[L];
};

void cpu::op_6E() {
    registers[L] = memory->address[registers[H] | (registers[L] << 8)];
};

void cpu::op_6F() {
    registers[L] = registers[A];
};

void cpu::op_70() {
    memory->address[registers[H] | (registers[L] << 8)] = registers[B];
};

void cpu::op_71() {
    memory->address[registers[H] | (registers[L] << 8)] = registers[C];
};

void cpu::op_72() {
    memory->address[registers[H] | (registers[L] << 8)] = registers[D];
};

void cpu::op_73() {
    memory->address[registers[H] | (registers[L] << 8)] = registers[E];
};

void cpu::op_74() {
    memory->address[registers[H] | (registers[L] << 8)] = registers[H];
};

void cpu::op_75() {
    memory->address[registers[H] | (registers[L] << 8)] = registers[L];
};

void cpu::op_76() {

};

void cpu::op_77() {
    memory->address[registers[H] | (registers[L] << 8)] = registers[A];
};

void cpu::op_78() {
    registers[A] = registers[B];
};

void cpu::op_79() {
    registers[A] = registers[C];
};

void cpu::op_7A() {
    registers[A] = registers[D];
};

void cpu::op_7B() {
    registers[A] = registers[E];
};

void cpu::op_7C() {
    registers[A] = registers[H];
};

void cpu::op_7D() {
    registers[A] = registers[L];
};

void cpu::op_7E() {
    registers[A] = memory->address[registers[H] | (registers[L] << 8)];
};

void cpu::op_7F() {
    registers[A] = registers[A];
};

void cpu::op_80() {
    registers[A] = add8(registers[A], registers[B]);
};

void cpu::op_81() {
    registers[A] = add8(registers[A], registers[C]);
};

void cpu::op_82() {
    registers[A] = add8(registers[A], registers[D]);
};

void cpu::op_83() {
    registers[A] = add8(registers[A], registers[E]);
};

void cpu::op_84() {
    registers[A] = add8(registers[A], registers[H]);
};

void cpu::op_85() {
    registers[A] = add8(registers[A], registers[L]);
};

void cpu::op_86() {
    registers[A] = add8(registers[A], memory->address[registers[H] | (registers[L] << 8)]);
};

void cpu::op_87() {
    registers[A] = add8(registers[A], registers[A]);
};

void cpu::op_88() {
    registers[A] = add8(registers[A], registers[B] + get_c_flag());
};

void cpu::op_89() {
    registers[A] = add8(registers[A], registers[C] + get_c_flag());
};

void cpu::op_8A() {
    registers[A] = add8(registers[A], registers[D] + get_c_flag());
};

void cpu::op_8B() {
    registers[A] = add8(registers[A], registers[E] + get_c_flag());
};

void cpu::op_8C() {
    registers[A] = add8(registers[A], registers[H] + get_c_flag());
};

void cpu::op_8D() {
    registers[A] = add8(registers[A], registers[L] + get_c_flag());
};

void cpu::op_8E() {
    registers[A] = add8(registers[A], memory->address[registers[H] | (registers[L] << 8)] + get_c_flag());
};

void cpu::op_8F() {
    registers[A] = add8(registers[A], registers[A] + get_c_flag());
};

void cpu::op_90() {
    registers[A] = sub8(registers[A], registers[B]);
};

void cpu::op_91() {
    registers[A] = sub8(registers[A], registers[C]);
};

void cpu::op_92() {
    registers[A] = sub8(registers[A], registers[D]);
};

void cpu::op_93() {
    registers[A] = sub8(registers[A], registers[E]);
};

void cpu::op_94() {
    registers[A] = sub8(registers[A], registers[H]);
};

void cpu::op_95() {
    registers[A] = sub8(registers[A], registers[L]);
};

void cpu::op_96() {
    registers[A] = sub8(registers[A], memory->address[registers[H] | (registers[L] << 8)]);
};

void cpu::op_97() {
    registers[A] = sub8(registers[A], registers[A]);
};

void cpu::op_98() {
    registers[A] = sub8(registers[A], registers[B] + get_c_flag());
};

void cpu::op_99() {
    registers[A] = sub8(registers[A], registers[C] + get_c_flag());
};

void cpu::op_9A() {
    registers[A] = sub8(registers[A], registers[D] + get_c_flag());
};

void cpu::op_9B() {
    registers[A] = sub8(registers[A], registers[E] + get_c_flag());
};

void cpu::op_9C() {
    registers[A] = sub8(registers[A], registers[H] + get_c_flag());
};

void cpu::op_9D() {
    registers[A] = sub8(registers[A], registers[L] + get_c_flag());
};

void cpu::op_9E() {
    registers[A] = sub8(registers[A], memory->address[registers[H] | (registers[L] << 8)] + get_c_flag());
};

void cpu::op_9F() {
    registers[A] = sub8(registers[A], registers[A] + get_c_flag());
};

void cpu::op_A0() {
    registers[A] = and8(registers[A], registers[B]);
};

void cpu::op_A1() {
    registers[A] = and8(registers[A], registers[C]);
};

void cpu::op_A2() {
    registers[A] = and8(registers[A], registers[D]);
};

void cpu::op_A3() {
    registers[A] = and8(registers[A], registers[E]);
};

void cpu::op_A4() {
    registers[A] = and8(registers[A], registers[H]);
};

void cpu::op_A5() {
    registers[A] = and8(registers[A], registers[L]);
};

void cpu::op_A6() {
    registers[A] = and8(registers[A], memory->address[registers[H] | (registers[L] << 8)]);
};

void cpu::op_A7() {
    registers[A] = and8(registers[A], registers[A]);
};

void cpu::op_A8() {
    registers[A] = xor8(registers[A], registers[B]);
};

void cpu::op_A9() {
    registers[A] = xor8(registers[A], registers[C]);
};

void cpu::op_AA() {
    registers[A] = xor8(registers[A], registers[D]);
};

void cpu::op_AB() {
    registers[A] = xor8(registers[A], registers[E]);
};

void cpu::op_AC() {
    registers[A] = xor8(registers[A], registers[H]);
};

void cpu::op_AD() {
    registers[A] = xor8(registers[A], registers[L]);
};

void cpu::op_AE() {
    registers[A] = xor8(registers[A], memory->address[registers[H] | (registers[L] << 8)]);
};

void cpu::op_AF() {
    registers[A] = xor8(registers[A], registers[A]);
};

void cpu::op_B0() {
    registers[A] = or8(registers[A], registers[B]);
};

void cpu::op_B1() {
    registers[A] = or8(registers[A], registers[C]);
};

void cpu::op_B2() {
    registers[A] = or8(registers[A], registers[D]);
};

void cpu::op_B3() {
    registers[A] = or8(registers[A], registers[E]);
};

void cpu::op_B4() {
    registers[A] = or8(registers[A], registers[H]);
};

void cpu::op_B5() {
    registers[A] = or8(registers[A], registers[L]);
};

void cpu::op_B6() {
    registers[A] = or8(registers[A], memory->address[registers[H] | (registers[L] << 8)]);
};

void cpu::op_B7() {
    registers[A] = or8(registers[A], registers[A]);
};

void cpu::op_B8() {
    cp(registers[A], registers[B]);
};

void cpu::op_B9() {
    cp(registers[A], registers[C]);
};

void cpu::op_BA() {
    cp(registers[A], registers[D]);
};

void cpu::op_BB() {
    cp(registers[A], registers[E]);
};

void cpu::op_BC() {
    cp(registers[A], registers[H]);
};

void cpu::op_BD() {
    cp(registers[A], registers[L]);
};

void cpu::op_BE() {
    cp(registers[A],  memory->address[registers[H] | (registers[L] << 8)]);
};

void cpu::op_BF() {
    cp(registers[A], registers[A]);
};

void cpu::op_C0() {
    if(!get_z_flag())
        pc = stack[sp++];
};

void cpu::op_C1() {
    registers[C] = stack[sp++];
    registers[B] = stack[sp++];
};

void cpu::op_C2() {
    if(!get_z_flag())
        pc = memory->address[memory->address[++pc] | (memory->address[++pc] << 8)];
};

void cpu::op_C3() {
    pc = memory->address[memory->address[++pc] | (memory->address[++pc] << 8)];
};

void cpu::op_C4() {
    // TODO:
    unsigned short nn = memory->address[memory->address[++pc] | (memory->address[++pc] << 8)];

    if(!get_z_flag()) {
        stack[--sp] = pc;
        pc = nn;
    }
}

void cpu::op_C5() {
    stack[--sp] = registers[B];
    stack[--sp] = registers[C];
};

void cpu::op_C6() {
    registers[A] = add8(registers[A], memory->address[pc]);
};

void cpu::op_C7() {
    stack[--sp] = pc;
    pc = 0x00;
};

void cpu::op_C8() {
    if(get_z_flag())
        pc = stack[sp++];
};

void cpu::op_C9() {
    pc = stack[sp++];
};

void cpu::op_CA() {
    if(get_z_flag())
        pc = memory->address[memory->address[++pc] | (memory->address[++pc] << 8)];
};

void cpu::op_CC() {
    // TODO:
    unsigned short nn = memory->address[memory->address[++pc] | (memory->address[++pc] << 8)];

    if(get_z_flag()) {
        stack[--sp] = pc;
        pc = nn;
    }
}

void cpu::op_CD() {
    // TODO: pc value that is pushed to the stack might be wrong because of the order
    unsigned short nn = memory->address[memory->address[++pc] | (memory->address[++pc] << 8)];
    stack[--sp] = pc;
    pc = nn;
};

void cpu::op_CE() {
    registers[A] = add8(registers[A], memory->address[pc] + get_c_flag());
}

void cpu::op_CF() {
    stack[--sp] = pc;
    pc = 0x08;
};

void cpu::op_D0() {
    if(!get_c_flag())
        pc = stack[sp++];
};

void cpu::op_D1() {
    registers[E] = stack[sp++];
    registers[D] = stack[sp++];
};

void cpu::op_D2() {
    if(!get_c_flag())
        pc = memory->address[memory->address[++pc] | (memory->address[++pc] << 8)];
};

void cpu::op_D4() {
    // TODO:
    unsigned short nn = memory->address[memory->address[++pc] | (memory->address[++pc] << 8)];

    if(!get_c_flag()) {
        stack[--sp] = pc;
        pc = nn;
    }
};

void cpu::op_D5() {
    stack[--sp] = registers[D];
    stack[--sp] = registers[E];
};

void cpu::op_D6() {
    registers[A] = sub8(registers[A], memory->address[pc]);
};

void cpu::op_D7() {
    stack[--sp] = pc;
    pc = 0x10;
};

void cpu::op_D8() {
    if(get_c_flag())
        pc = stack[sp++];
};

void cpu::op_D9() {
    // TODO: enable interrupts
    pc = stack[sp++];
};

void cpu::op_DA() {
    if(get_c_flag())
        pc = memory->address[memory->address[++pc] | (memory->address[++pc] << 8)];
};

void cpu::op_DC() {
    // TODO:
    unsigned short nn = memory->address[memory->address[++pc] | (memory->address[++pc] << 8)];

    if(get_c_flag()) {
        stack[--sp] = pc;
        pc = nn;
    }
};

void cpu::op_DF() {
    stack[--sp] = pc;
    pc = 0x18;
};

void cpu::op_E0() {
    memory->address[0xFF00 + memory->address[++pc]] = registers[A];
};

void cpu::op_E1() {
    registers[L] = stack[sp++];
    registers[H] = stack[sp++];
};

void cpu::op_E2() {
    memory->address[0xFF + registers[C]] = registers[A];
};

void cpu::op_E5() {
    stack[--sp] = registers[H];
    stack[--sp] = registers[L];  
};

void cpu::op_E6() {
    registers[A] = and8(registers[A], memory->address[pc]);
};

void cpu::op_E7() {
    stack[--sp] = pc;
    pc = 0x20;
};

void cpu::op_E8() {

};

void cpu::op_E9() {
    pc = registers[H] | (registers[L] << 8);
};

void cpu::op_EA() {
    memory->address[memory->address[++pc] | (memory->address[++pc] << 8)] = registers[A];
};

void cpu::op_EE() {
    registers[A] = xor8(registers[A], memory->address[pc]);
};

void cpu::op_EF() {
    stack[--sp] = pc;
    pc = 0x28;
};

void cpu::op_F0() {
    registers[A] = memory->address[0xFF00 + memory->address[++pc]];
};

void cpu::op_F1() {
    registers[F] = stack[sp++];
    registers[A] = stack[sp++];
};

void cpu::op_F2() {
    registers[A] = memory->address[0xFF + registers[C]];
};

void cpu::op_F3() {

};

void cpu::op_F5() {
    stack[--sp] = registers[A];
    stack[--sp] = registers[F];
};

void cpu::op_F6() {
    registers[A] = or8(registers[A], memory->address[pc]);
}

void cpu::op_F7() {
    stack[--sp] = pc;
    pc = 0x30;
};

void cpu::op_F8() {
    unsigned short spn = sp + (signed char)memory->address[++pc];   // the value prob is gonna be read as unsigned
    registers[H] = spn & 0x00FF;
    registers[L] = (spn & 0xFF00) >> 8;
};

void cpu::op_F9() {
    sp = registers[H] | (registers[L] << 8);
};

void cpu::op_FA() {
    registers[A] = memory->address[++pc] | (memory->address[++pc] << 8);
};

void cpu::op_FB() {

};

void cpu::op_FE() {
    cp(registers[A], memory->address[pc]);
};

void cpu::op_FF() {
    stack[--sp] = pc;
    pc = 0x38;
};

void cpu::op_CB() {

};

void cpu::op_CB_00() {
    op_rlc_r1(B);
};

void cpu::op_CB_01() {
    op_rlc_r1(C);
};

void cpu::op_CB_02() {
    op_rlc_r1(D);
};

void cpu::op_CB_03() {
    op_rlc_r1(E);
};

void cpu::op_CB_04() {
    op_rlc_r1(H);
};

void cpu::op_CB_05() {
    op_rlc_r1(L);
};

void cpu::op_CB_06() {

};

void cpu::op_CB_07() {
    op_rlc_r1(A);
};

void cpu::op_CB_08() {
    op_rrc_r1(B);
};

void cpu::op_CB_09() {
    op_rrc_r1(C);
};

void cpu::op_CB_0A() {
    op_rrc_r1(D);
};

void cpu::op_CB_0B() {
    op_rrc_r1(E);
};

void cpu::op_CB_0C() {
    op_rrc_r1(H);
};

void cpu::op_CB_0D() {
    op_rrc_r1(L);
};

void cpu::op_CB_0E() {

};

void cpu::op_CB_0F() {
    op_rrc_r1(A);
};

void cpu::op_CB_10() {
    op_rl_r1(B);
};

void cpu::op_CB_11() {
    op_rl_r1(C);
};

void cpu::op_CB_12() {
    op_rl_r1(D);
};

void cpu::op_CB_13() {
    op_rl_r1(E);
};

void cpu::op_CB_14() {
    op_rl_r1(H);
};

void cpu::op_CB_15() {
    op_rl_r1(L);
};

void cpu::op_CB_16() {

};

void cpu::op_CB_17() {
    op_rl_r1(A);
};

void cpu::op_CB_18() {
    op_rr_r1(B);
};

void cpu::op_CB_19() {
    op_rr_r1(C);
};

void cpu::op_CB_1A() {
    op_rr_r1(D);
};

void cpu::op_CB_1B() {
    op_rr_r1(E);
};

void cpu::op_CB_1C() {
    op_rr_r1(H);
};

void cpu::op_CB_1D() {
    op_rr_r1(L);
};

void cpu::op_CB_1E() {

};

void cpu::op_CB_1F() {
    op_rr_r1(A);
};

void cpu::op_CB_20() {
    op_sla_r1(B);
};

void cpu::op_CB_21() {
    op_sla_r1(C);
};

void cpu::op_CB_22() {
    op_sla_r1(D);
};

void cpu::op_CB_23() {
    op_sla_r1(E);
};

void cpu::op_CB_24() {
    op_sla_r1(H);
};

void cpu::op_CB_25() {
    op_sla_r1(L);
};

void cpu::op_CB_26() {

};

void cpu::op_CB_27() {
    op_sla_r1(A);
};

void cpu::op_CB_28() {
    op_sra_r1(B);
};

void cpu::op_CB_29() {
    op_sra_r1(C);
};

void cpu::op_CB_2A() {
    op_sra_r1(D);
};

void cpu::op_CB_2B() {
    op_sra_r1(E);
};

void cpu::op_CB_2C() {
    op_sra_r1(H);
};

void cpu::op_CB_2D() {
    op_sra_r1(L);
};

void cpu::op_CB_2E() {

};

void cpu::op_CB_2F() {
    op_sra_r1(A);
};

void cpu::op_CB_30() {
    op_swap_r1(B);
};

void cpu::op_CB_31() {
    op_swap_r1(C);
};

void cpu::op_CB_32() {
    op_swap_r1(D);
};

void cpu::op_CB_33() {
    op_swap_r1(E);
};

void cpu::op_CB_34() {
    op_swap_r1(H);
};

void cpu::op_CB_35() {
    op_swap_r1(L);
};

void cpu::op_CB_36() {
    op_swap_r16(H);
};

void cpu::op_CB_37() {
    op_swap_r1(A);
};

void cpu::op_CB_38() {
    op_srl_r1(B);
};

void cpu::op_CB_39() {
    op_srl_r1(C);
};

void cpu::op_CB_3A() {
    op_srl_r1(D);
};

void cpu::op_CB_3B() {
    op_srl_r1(E);
};

void cpu::op_CB_3C() {
    op_srl_r1(H);
};

void cpu::op_CB_3D() {
    op_srl_r1(L);
};

void cpu::op_CB_3E() {

};

void cpu::op_CB_3F() {
    op_srl_r1(A);
};




//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


void cpu::op_pop_nn(byte r16) {
    // TODO: not sure about the order
    
};


void cpu::op_subc_a_pc() {
    // TODO:: n tem sitio xD
    registers[A] = sub8(registers[A], memory->address[pc] + get_c_flag());
};

void cpu::op_add_hl_r16(byte r16) {

    unsigned short res = 
        add16(registers[H] | (registers[L] << 8), registers[r16] | (registers[r16 + 1] << 8));

    registers[H] = 0xFF;
    registers[L] = 0xFF00 >> 8;
};

void cpu::op_add_hl_sp() {
    
    unsigned short res = 
        add16(registers[H] | (registers[L] << 8), sp);

    registers[H] = res & 0xFF;
    registers[L] = (res & 0xFF00) >> 8;    
};

void cpu::op_add_sp_pc() {
    // TODO: mal
    sp = add16(sp, memory->address[pc]);
};

void cpu::op_inc_r16(byte r16) {
    unsigned short res = inc16(registers[r16] | (registers[r16 + 1] << 8));
    registers[r16] = res & 0xFF;
    registers[r16 + 1] = (res & 0xFF00) >> 8;    
};

void cpu::op_dec_r16(byte r16) {
    unsigned short res = dec16(registers[r16] | (registers[r16 + 1] << 8));
    registers[r16] = res & 0xFF;
    registers[r16 + 1] = (res & 0xFF00) >> 8;    
};


void cpu::op_swap_r1(byte r1) {

    reset_n_flag();
    reset_h_flag();
    reset_c_flag();

    registers[r1] = (registers[r1] << 4) | (registers[r1] >> 4);
    if(registers[r1] == 0) set_z_flag();

};

void cpu::op_swap_r16(byte r16) {

    reset_n_flag();
    reset_h_flag();
    reset_c_flag();
    
    byte temp = registers[r16];

    registers[r16] = registers[r16 + 1];
    registers[r16 + 1] = temp;
    if(registers[r16] == 0 && registers[r16 + 1] == 0) set_z_flag();

};



// for rl vs rlc : http://jgmalcolm.com/z80/advanced/shif

void cpu::op_rlc_r1(byte r1) {

    reset_n_flag();
    reset_h_flag();

    if(registers[r1] == 0x80) {
        set_z_flag();
        set_c_flag();
    }
    else if(registers[r1] & 0x80) {
        set_c_flag();
    }
    else {
        reset_c_flag();
    }

    byte carry = get_c_flag() >> 6;
    registers[r1] = (registers[r1] << 1) | carry;
};


void cpu::op_rl_r1(byte r1) {

    reset_n_flag();
    reset_h_flag();
    byte carry = get_c_flag() >> 6;

    if(registers[r1] == 0x80) {
        set_z_flag();
    }
    
    if(registers[r1] & 0x80) {
        set_c_flag();
    }
    else {
        reset_c_flag();
    }

    registers[r1] = (registers[r1] << 1) | carry;

};

void cpu::op_rrc_r1(byte r1) {

    reset_n_flag();
    reset_h_flag();

    if(registers[r1] == 0x01) set_z_flag();

    if(registers[r1] & 0x01) 
        set_c_flag();
    else 
        reset_c_flag();    
    
    byte carry = registers[r1] & 0x01;
    registers[r1] =  (registers[r1] >> 1) | (carry << 7); 
};

void cpu::op_rr_r1(byte r1) {

    reset_n_flag();
    reset_h_flag();
    byte carry = get_c_flag() >> 6;

    if(registers[r1] == 0x01) set_z_flag();

    if(registers[r1] & 0x01) 
        set_c_flag();
    else 
        reset_c_flag();    
    
    registers[r1] =  (registers[r1] >> 1) | (carry << 7); 
};

void cpu::op_sla_r1(byte r1) {

    reset_n_flag();
    reset_h_flag();

    if(registers[r1] & 0x80)
        set_c_flag();
    else
        reset_c_flag();  

    registers[r1] <<= 1;
    if(registers[r1] == 0) set_z_flag();
};

void cpu::op_sra_r1(byte r1) {

    reset_n_flag();
    reset_h_flag();

    if(registers[r1] & 0x01) 
        set_c_flag();
    else
        reset_c_flag();

    byte last_bit = registers[r1] & 0x80;
    registers[r1] >>= 1;
    registers[r1] |= last_bit;

    if(registers[r1] == 0) set_z_flag();
};

void cpu::op_srl_r1(byte r1) {

    reset_n_flag();
    reset_h_flag();

    if(registers[r1] & 0x01) 
        set_c_flag();
    else
        reset_c_flag();

    registers[r1] >>= 1;

    if(registers[r1] == 0) set_z_flag();

};

void cpu::op_bit_r1(byte r1, byte bit) {

    reset_n_flag();
    set_h_flag(); 

    if(!(registers[r1] & (1 << bit))) set_z_flag();
};

void cpu::op_set_r1(byte r1, byte bit) {
    registers[r1] |= (1 << bit);
};

void cpu::op_res_r1(byte r1, byte bit) {
    registers[r1] &= ~(1 << bit);
};



void cpu::op_call_cc_nn(byte cc) {

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

void cpu::op_ret_cc(byte cc) {
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

    reset_n_flag();

    byte res = op1 + op2;
    
    if(res == 0) {
        set_z_flag();
    }

    if((op1 + op2) > 0xFF) {
        set_c_flag();
    }

    if((op1 & 0x0F) + (op2 & 0x0F) > 0x0F ) {
        set_h_flag();
    } 

    return res;
};

byte cpu::sub8(byte op1, byte op2) {

    set_n_flag();

    byte res = op1 - op2;

    if(res == 0) {
        set_z_flag();
    }

    if(op2 < op1) {
        set_c_flag();
    }

    if((op2 & 0x0F) < (op1 & 0x0F)) {
        set_h_flag();
    }
    return res;
};

byte cpu::and8(byte op1, byte op2) {

    reset_c_flag();
    set_h_flag();
    reset_n_flag();

    byte res = op1 & op2;

    if(res == 0) set_z_flag();
    
    return res;
};

byte cpu::or8(byte op1, byte op2) {

    reset_c_flag();
    reset_h_flag();
    reset_n_flag();

    byte res = op1 | op2;

    if(res == 0) set_z_flag();

    return res;
};

byte cpu::xor8(byte op1, byte op2) {

    reset_c_flag();
    reset_h_flag();
    reset_n_flag();

    byte res = op1 ^ op2;

    if(res == 0) set_z_flag();

    return res;
};

void cpu::cp(byte op1, byte op2) {

    set_n_flag();

    if(op1 == op2) set_z_flag();

    if(op1 < op2) set_c_flag();

    if((op1 & 0xF) < (op2 & 0xF)) set_h_flag();

};

byte cpu::inc8(byte op1) {

    reset_n_flag();

    byte res = op1 + 1;

    if(res == 0) set_z_flag();

    if(op1 & 0x0F) set_h_flag();

    return res;
};

byte cpu::dec8(byte op1) {

    set_n_flag();

    byte res = op1 - 1;

    if(res == 0) set_z_flag();

    if((res & 0x0F) == 0x0F) set_c_flag();      // not sure

    return res;
};


unsigned short cpu::add16(unsigned short op1, unsigned short op2) {
    // this operation uses the values of the registers and not the addresses

    reset_n_flag();

    if((0xFFFF - op1) < op2) set_c_flag();

    if((0x0FFF & op1) + (0X0FFF & op2) > 0x0FFF) set_h_flag();  // not sure

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



void cpu::set_z_flag() {
    registers[F] |= 0x80;
};

void cpu::set_n_flag() {
    registers[F] |= 0x40;
};

void cpu::set_h_flag() {
    registers[F] |= 0x20;
};

void cpu::set_c_flag() {
    registers[F] |= 0x10;
};


void cpu::reset_z_flag() {
    registers[F] &= 0x7F;
};

void cpu::reset_n_flag() {
    registers[F] &= 0xBF;    
};

void cpu::reset_h_flag() {
    registers[F] &= 0xDF;
};

void cpu::reset_c_flag() {
    registers[F] &= 0xEF;
};


byte cpu::get_z_flag() {
    return registers[F] & 0x80;
};

byte cpu::get_n_flag() {
    return registers[F] & 0x40;
};

byte cpu::get_h_flag() {
    return registers[F] & 0x20;
};

byte cpu::get_c_flag() {
    return registers[F] & 0x10;
};