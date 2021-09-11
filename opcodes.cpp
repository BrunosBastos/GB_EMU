#include "opcodes.h"

void op_00(mmu* memory, cpu* cp) {
    ;
};

void op_01(mmu* memory, cpu* cp) {
    cp->registers[B] = memory->address[++cp->pc];
    cp->registers[C] = memory->address[++cp->pc];
};

void op_02(mmu* memory, cpu* cp) {
    memory->address[cp->registers[B] | (cp->registers[C] << 8)] = cp->registers[A];
};

void op_03(mmu* memory, cpu* cp) {
    cp->inc_r16(B);
};

void op_04(mmu* memory, cpu* cp) {
    cp->registers[B] = cp->inc8(cp->registers[B]);
};

void op_05(mmu* memory, cpu* cp) {
    cp->registers[B] = cp->dec8(cp->registers[B]);
};

void op_06(mmu* memory, cpu* cp) {
    cp->registers[B] = memory->address[++cp->pc];
};

void op_07(mmu* memory, cpu* cp) {
    cp->rlc_r1(A);
};

void op_08(mmu* memory, cpu* cp) {
    memory->address[memory->address[++cp->pc] | (memory->address[++cp->pc] << 8)] = cp->sp;
};

void op_09(mmu* memory, cpu* cp) {
    cp->add_hl_r16(B);
};

void op_0A(mmu* memory, cpu* cp) {
    cp->registers[A] = memory->address[cp->registers[B] | (cp->registers[C] << 8)];
};

void op_0B(mmu* memory, cpu* cp) {
    cp->dec_r16(B);
};

void op_0C(mmu* memory, cpu* cp) {
    cp->registers[C] = cp->inc8(cp->registers[C]);
};

void op_0D(mmu* memory, cpu* cp) {
    cp->registers[C] = cp->dec8(cp->registers[C]);
};

void op_0E(mmu* memory, cpu* cp) {
    cp->registers[C] = memory->address[++cp->pc];
};

void op_0F(mmu* memory, cpu* cp) {

};

void op_11(mmu* memory, cpu* cp) {
    cp->registers[D] = memory->address[++cp->pc];
    cp->registers[E] = memory->address[++cp->pc];
};

void op_12(mmu* memory, cpu* cp) {
    memory->address[cp->registers[D] | (cp->registers[E] << 8)] = cp->registers[A];
};

void op_13(mmu* memory, cpu* cp) {
    cp->inc_r16(D);
};

void op_14(mmu* memory, cpu* cp) {
    cp->registers[D] = cp->inc8(cp->registers[D]);
};

void op_15(mmu* memory, cpu* cp) {
    cp->registers[D] = cp->dec8(cp->registers[D]);
};

void op_16(mmu* memory, cpu* cp) {
    cp->registers[D] = memory->address[++cp->pc];
};

void op_17(mmu* memory, cpu* cp) {
    cp->rl_r1(A);
};

void op_18(mmu* memory, cpu* cp) {
    cp->pc += memory->address[++cp->pc];
};

void op_19(mmu* memory, cpu* cp) {
    cp->add_hl_r16(D);
};

void op_1A(mmu* memory, cpu* cp) {
    cp->registers[A] = memory->address[cp->registers[D] | (cp->registers[E] << 8)];
};

void op_1B(mmu* memory, cpu* cp) {
    cp->dec_r16(D);
};

void op_1C(mmu* memory, cpu* cp) {
    cp->registers[E] = cp->inc8(cp->registers[E]);
};

void op_1D(mmu* memory, cpu* cp) {
    cp->registers[E] = cp->dec8(cp->registers[E]);
};

void op_1E(mmu* memory, cpu* cp) {
    cp->registers[E] = memory->address[++cp->pc];
};

void op_1F(mmu* memory, cpu* cp) {
    cp->rr_r1(A);
};

void op_20(mmu* memory, cpu* cp) {
    if(!cp->get_z_flag()) 
        cp->pc += memory->address[++cp->pc];
};

void op_21(mmu* memory, cpu* cp) {
    cp->registers[H] = memory->address[++cp->pc];
    cp->registers[L] = memory->address[++cp->pc];
};

void op_22(mmu* memory, cpu* cp) {
    unsigned short hl = cp->registers[H] | (cp->registers[L] << 8);
    memory->address[hl++] = cp->registers[A];
    cp->registers[H] = hl & 0x00FF;
    cp->registers[L] = (hl & 0xFF00) >> 8;
};

void op_23(mmu* memory, cpu* cp) {
    cp->inc_r16(H);
};

void op_24(mmu* memory, cpu* cp) {
    cp->registers[H] = cp->inc8(cp->registers[H]);
};

void op_25(mmu* memory, cpu* cp) {
    cp->registers[H] = cp->dec8(cp->registers[H]);
};

void op_26(mmu* memory, cpu* cp) {
    cp->registers[H] = memory->address[++cp->pc];
};

void op_27(mmu* memory, cpu* cp) {

};

void op_28(mmu* memory, cpu* cp) {
    if(cp->get_z_flag()) 
        cp->pc += memory->address[++cp->pc];
};

void op_29(mmu* memory, cpu* cp) {
    cp->add_hl_r16(H);
};

void op_2A(mmu* memory, cpu* cp) {
    unsigned short hl = cp->registers[H] | (cp->registers[L] << 8);
    cp->registers[A] = memory->address[hl++];
    cp->registers[H] = hl & 0x00FF;
    cp->registers[L] = (hl & 0xFF00) >> 8;
};

void op_2B(mmu* memory, cpu* cp) {
    cp->dec_r16(H);
};

void op_2C(mmu* memory, cpu* cp) {
    cp->registers[L] = cp->inc8(cp->registers[L]);
};

void op_2D(mmu* memory, cpu* cp) {
    cp->registers[L] = cp->dec8(cp->registers[L]);
};

void op_2E(mmu* memory, cpu* cp) {
    cp->registers[E] = memory->address[++cp->pc];
};

void op_2F(mmu* memory, cpu* cp) {
    cp->set_n_flag(1);
    cp->set_h_flag(1);

    cp->registers[A] = ~cp->registers[A];
};

void op_30(mmu* memory, cpu* cp) {
    if(!cp->get_c_flag()) 
        cp->pc += memory->address[++cp->pc];
};

void op_31(mmu* memory, cpu* cp) {
    cp->sp = memory->address[++cp->pc] | (memory->address[++cp->pc] << 8);
};

void op_32(mmu* memory, cpu* cp) {
    unsigned short hl = cp->registers[H] | (cp->registers[L] << 8);
    memory->address[hl--] = cp->registers[A];
    cp->registers[H] = hl & 0x00FF;
    cp->registers[L] = (hl & 0xFF00) >> 8;
};

void op_33(mmu* memory, cpu* cp) {
    
};

void op_34(mmu* memory, cpu* cp) {

};

void op_35(mmu* memory, cpu* cp) {

};

void op_36(mmu* memory, cpu* cp) {
    memory->address[cp->registers[H] | (cp->registers[L] << 8)] = memory->address[++cp->pc];
};

void op_37(mmu* memory, cpu* cp) {
    cp->set_n_flag(0);
    cp->set_h_flag(0);
    cp->set_c_flag(1);
};

void op_38(mmu* memory, cpu* cp) {
    if(cp->get_c_flag()) 
        cp->pc += memory->address[++cp->pc];
};

void op_39(mmu* memory, cpu* cp) {
    cp->add_hl_sp();
};

void op_3A(mmu* memory, cpu* cp) {
    unsigned short hl = cp->registers[H] | (cp->registers[L] << 8);
    cp->registers[A] = memory->address[hl--];
    cp->registers[H] = hl & 0x00FF;
    cp->registers[L] = (hl & 0xFF00) >> 8;
};

void op_3B(mmu* memory, cpu* cp) {

};

void op_3C(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->inc8(cp->registers[A]);
};

void op_3D(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->dec8(cp->registers[A]);
};

void op_3E(mmu* memory, cpu* cp) {
    cp->registers[A] = memory->address[cp->pc];
};

void op_3F(mmu* memory, cpu* cp) {
    cp->set_n_flag(0);
    cp->set_h_flag(0);

    if(cp->get_c_flag()) 
        cp->set_c_flag(0);
    else 
        cp->set_c_flag(1);
};

void op_40(mmu* memory, cpu* cp) {
    cp->registers[B] = cp->registers[B];
};

void op_41(mmu* memory, cpu* cp) {
    cp->registers[B] = cp->registers[C];
};

void op_42(mmu* memory, cpu* cp) {
    cp->registers[B] = cp->registers[D];
};

void op_43(mmu* memory, cpu* cp) {
    cp->registers[B] = cp->registers[E];
};

void op_44(mmu* memory, cpu* cp) {
    cp->registers[B] = cp->registers[H];
};

void op_45(mmu* memory, cpu* cp) {
    cp->registers[B] = cp->registers[L];
};

void op_46(mmu* memory, cpu* cp) {
    cp->registers[B] = memory->address[cp->registers[H] | (cp->registers[L] << 8)];
};

void op_47(mmu* memory, cpu* cp) {
    cp->registers[B] = cp->registers[A];
};

void op_48(mmu* memory, cpu* cp) {
    cp->registers[C] = cp->registers[B];
};

void op_49(mmu* memory, cpu* cp) {
    cp->registers[C] = cp->registers[C];
};

void op_4A(mmu* memory, cpu* cp) {
    cp->registers[C] = cp->registers[D];
};

void op_4B(mmu* memory, cpu* cp) {
    cp->registers[C] = cp->registers[E];
};

void op_4C(mmu* memory, cpu* cp) {
    cp->registers[C] = cp->registers[H];
};

void op_4D(mmu* memory, cpu* cp) {
    cp->registers[C] = cp->registers[L];
};

void op_4E(mmu* memory, cpu* cp) {
    cp->registers[C] = memory->address[cp->registers[H] | (cp->registers[L] << 8)];
};

void op_4F(mmu* memory, cpu* cp) {
    cp->registers[C] = cp->registers[A];
};

void op_50(mmu* memory, cpu* cp) {
    cp->registers[D] = cp->registers[B];
};

void op_51(mmu* memory, cpu* cp) {
    cp->registers[D] = cp->registers[C];
};

void op_52(mmu* memory, cpu* cp) {
    cp->registers[D] = cp->registers[D];
};

void op_53(mmu* memory, cpu* cp) {
    cp->registers[D] = cp->registers[E];
};

void op_54(mmu* memory, cpu* cp) {
    cp->registers[D] = cp->registers[H];
};

void op_55(mmu* memory, cpu* cp) {
    cp->registers[D] = cp->registers[L];
};

void op_56(mmu* memory, cpu* cp) {
    cp->registers[D] = memory->address[cp->registers[H] | (cp->registers[L] << 8)];
};

void op_57(mmu* memory, cpu* cp) {
    cp->registers[D] = cp->registers[A];
};

void op_58(mmu* memory, cpu* cp) {
    cp->registers[E] = cp->registers[B];
};

void op_59(mmu* memory, cpu* cp) {
    cp->registers[E] = cp->registers[C];
};

void op_5A(mmu* memory, cpu* cp) {
    cp->registers[E] = cp->registers[D];
};

void op_5B(mmu* memory, cpu* cp) {
    cp->registers[E] = cp->registers[E];
};

void op_5C(mmu* memory, cpu* cp) {
    cp->registers[E] = cp->registers[H];
};

void op_5D(mmu* memory, cpu* cp) {
    cp->registers[E] = cp->registers[L];
};

void op_5E(mmu* memory, cpu* cp) {
    cp->registers[E] = memory->address[cp->registers[H] | (cp->registers[L] << 8)];
};

void op_5F(mmu* memory, cpu* cp) {
    cp->registers[E] = cp->registers[A];
};

void op_60(mmu* memory, cpu* cp) {
    cp->registers[H] = cp->registers[B];
};

void op_61(mmu* memory, cpu* cp) {
    cp->registers[H] = cp->registers[C];
};

void op_62(mmu* memory, cpu* cp) {
    cp->registers[H] = cp->registers[D];
};

void op_63(mmu* memory, cpu* cp) {
    cp->registers[H] = cp->registers[E];
};

void op_64(mmu* memory, cpu* cp) {
    cp->registers[H] = cp->registers[H];
};

void op_65(mmu* memory, cpu* cp) {
    cp->registers[H] = cp->registers[L];
};

void op_66(mmu* memory, cpu* cp) {
    cp->registers[H] = memory->address[cp->registers[H] | (cp->registers[L] << 8)];
};

void op_67(mmu* memory, cpu* cp) {
    cp->registers[H] = cp->registers[A];
};

void op_68(mmu* memory, cpu* cp) {
    cp->registers[L] = cp->registers[B];
};

void op_69(mmu* memory, cpu* cp) {
    cp->registers[L] = cp->registers[C];
};

void op_6A(mmu* memory, cpu* cp) {
    cp->registers[L] = cp->registers[D];
};

void op_6B(mmu* memory, cpu* cp) {
    cp->registers[L] = cp->registers[E];
};

void op_6C(mmu* memory, cpu* cp) {
    cp->registers[L] = cp->registers[H];
};

void op_6D(mmu* memory, cpu* cp) {
    cp->registers[L] = cp->registers[L];
};

void op_6E(mmu* memory, cpu* cp) {
    cp->registers[L] = memory->address[cp->registers[H] | (cp->registers[L] << 8)];
};

void op_6F(mmu* memory, cpu* cp) {
    cp->registers[L] = cp->registers[A];
};

void op_70(mmu* memory, cpu* cp) {
    memory->address[cp->registers[H] | (cp->registers[L] << 8)] = cp->registers[B];
};

void op_71(mmu* memory, cpu* cp) {
    memory->address[cp->registers[H] | (cp->registers[L] << 8)] = cp->registers[C];
};

void op_72(mmu* memory, cpu* cp) {
    memory->address[cp->registers[H] | (cp->registers[L] << 8)] = cp->registers[D];
};

void op_73(mmu* memory, cpu* cp) {
    memory->address[cp->registers[H] | (cp->registers[L] << 8)] = cp->registers[E];
};

void op_74(mmu* memory, cpu* cp) {
    memory->address[cp->registers[H] | (cp->registers[L] << 8)] = cp->registers[H];
};

void op_75(mmu* memory, cpu* cp) {
    memory->address[cp->registers[H] | (cp->registers[L] << 8)] = cp->registers[L];
};

void op_76(mmu* memory, cpu* cp) {

};

void op_77(mmu* memory, cpu* cp) {
    memory->address[cp->registers[H] | (cp->registers[L] << 8)] = cp->registers[A];
};

void op_78(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->registers[B];
};

void op_79(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->registers[C];
};

void op_7A(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->registers[D];
};

void op_7B(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->registers[E];
};

void op_7C(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->registers[H];
};

void op_7D(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->registers[L];
};

void op_7E(mmu* memory, cpu* cp) {
    cp->registers[A] = memory->address[cp->registers[H] | (cp->registers[L] << 8)];
};

void op_7F(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->registers[A];
};

void op_80(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], cp->registers[B]);
};

void op_81(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], cp->registers[C]);
};

void op_82(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], cp->registers[D]);
};

void op_83(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], cp->registers[E]);
};

void op_84(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], cp->registers[H]);
};

void op_85(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], cp->registers[L]);
};

void op_86(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], memory->address[cp->registers[H] | (cp->registers[L] << 8)]);
};

void op_87(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], cp->registers[A]);
};

void op_88(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], cp->registers[B] + cp->get_c_flag());
};

void op_89(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], cp->registers[C] + cp->get_c_flag());
};

void op_8A(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], cp->registers[D] + cp->get_c_flag());
};

void op_8B(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], cp->registers[E] + cp->get_c_flag());
};

void op_8C(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], cp->registers[H] + cp->get_c_flag());
};

void op_8D(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], cp->registers[L] + cp->get_c_flag());
};

void op_8E(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], memory->address[cp->registers[H] | (cp->registers[L] << 8)] + cp->get_c_flag());
};

void op_8F(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], cp->registers[A] + cp->get_c_flag());
};

void op_90(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], cp->registers[B]);
};

void op_91(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], cp->registers[C]);
};

void op_92(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], cp->registers[D]);
};

void op_93(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], cp->registers[E]);
};

void op_94(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], cp->registers[H]);
};

void op_95(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], cp->registers[L]);
};

void op_96(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], memory->address[cp->registers[H] | (cp->registers[L] << 8)]);
};

void op_97(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], cp->registers[A]);
};

void op_98(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], cp->registers[B] + cp->get_c_flag());
};

void op_99(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], cp->registers[C] + cp->get_c_flag());
};

void op_9A(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], cp->registers[D] + cp->get_c_flag());
};

void op_9B(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], cp->registers[E] + cp->get_c_flag());
};

void op_9C(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], cp->registers[H] + cp->get_c_flag());
};

void op_9D(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], cp->registers[L] + cp->get_c_flag());
};

void op_9E(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], memory->address[cp->registers[H] | (cp->registers[L] << 8)] + cp->get_c_flag());
};

void op_9F(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], cp->registers[A] + cp->get_c_flag());
};

void op_A0(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->and8(cp->registers[A], cp->registers[B]);
};

void op_A1(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->and8(cp->registers[A], cp->registers[C]);
};

void op_A2(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->and8(cp->registers[A], cp->registers[D]);
};

void op_A3(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->and8(cp->registers[A], cp->registers[E]);
};

void op_A4(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->and8(cp->registers[A], cp->registers[H]);
};

void op_A5(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->and8(cp->registers[A], cp->registers[L]);
};

void op_A6(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->and8(cp->registers[A], memory->address[cp->registers[H] | (cp->registers[L] << 8)]);
};

void op_A7(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->and8(cp->registers[A], cp->registers[A]);
};

void op_A8(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->xor8(cp->registers[A], cp->registers[B]);
};

void op_A9(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->xor8(cp->registers[A], cp->registers[C]);
};

void op_AA(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->xor8(cp->registers[A], cp->registers[D]);
};

void op_AB(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->xor8(cp->registers[A], cp->registers[E]);
};

void op_AC(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->xor8(cp->registers[A], cp->registers[H]);
};

void op_AD(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->xor8(cp->registers[A], cp->registers[L]);
};

void op_AE(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->xor8(cp->registers[A], memory->address[cp->registers[H] | (cp->registers[L] << 8)]);
};

void op_AF(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->xor8(cp->registers[A], cp->registers[A]);
};

void op_B0(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->or8(cp->registers[A], cp->registers[B]);
};

void op_B1(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->or8(cp->registers[A], cp->registers[C]);
};

void op_B2(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->or8(cp->registers[A], cp->registers[D]);
};

void op_B3(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->or8(cp->registers[A], cp->registers[E]);
};

void op_B4(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->or8(cp->registers[A], cp->registers[H]);
};

void op_B5(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->or8(cp->registers[A], cp->registers[L]);
};

void op_B6(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->or8(cp->registers[A], memory->address[cp->registers[H] | (cp->registers[L] << 8)]);
};

void op_B7(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->or8(cp->registers[A], cp->registers[A]);
};

void op_B8(mmu* memory, cpu* cp) {
    cp->cp(cp->registers[A], cp->registers[B]);
};

void op_B9(mmu* memory, cpu* cp) {
    cp->cp(cp->registers[A], cp->registers[C]);
};

void op_BA(mmu* memory, cpu* cp) {
    cp->cp(cp->registers[A], cp->registers[D]);
};

void op_BB(mmu* memory, cpu* cp) {
    cp->cp(cp->registers[A], cp->registers[E]);
};

void op_BC(mmu* memory, cpu* cp) {
    cp->cp(cp->registers[A], cp->registers[H]);
};

void op_BD(mmu* memory, cpu* cp) {
    cp->cp(cp->registers[A], cp->registers[L]);
};

void op_BE(mmu* memory, cpu* cp) {
    cp->cp(cp->registers[A],  memory->address[cp->registers[H] | (cp->registers[L] << 8)]);
};

void op_BF(mmu* memory, cpu* cp) {
    cp->cp(cp->registers[A], cp->registers[A]);
};

void op_C0(mmu* memory, cpu* cp) {
    if(!cp->get_z_flag())
        cp->pc = cp->stack[cp->sp++];
};

void op_C1(mmu* memory, cpu* cp) {
    cp->registers[C] = cp->stack[cp->sp++];
    cp->registers[B] = cp->stack[cp->sp++];
};

void op_C2(mmu* memory, cpu* cp) {
    if(!cp->get_z_flag())
        cp->pc = memory->address[memory->address[++cp->pc] | (memory->address[++cp->pc] << 8)];
};

void op_C3(mmu* memory, cpu* cp) {
    cp->pc = memory->address[memory->address[++cp->pc] | (memory->address[++cp->pc] << 8)];
};

void op_C4(mmu* memory, cpu* cp) {
    // TODO:
    unsigned short nn = memory->address[memory->address[++cp->pc] | (memory->address[++cp->pc] << 8)];

    if(!cp->get_z_flag()) {
        cp->stack[--cp->sp] = cp->pc;
        cp->pc = nn;
    }
}

void op_C5(mmu* memory, cpu* cp) {
    cp->stack[--cp->sp] = cp->registers[B];
    cp->stack[--cp->sp] = cp->registers[C];
};

void op_C6(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], memory->address[cp->pc]);
};

void op_C7(mmu* memory, cpu* cp) {
    cp->stack[--cp->sp] = cp->pc;
    cp->pc = 0x00;
};

void op_C8(mmu* memory, cpu* cp) {
    if(cp->get_z_flag())
        cp->pc = cp->stack[cp->sp++];
};

void op_C9(mmu* memory, cpu* cp) {
    cp->pc = cp->stack[cp->sp++];
};

void op_CA(mmu* memory, cpu* cp) {
    if(cp->get_z_flag())
        cp->pc = memory->address[memory->address[++cp->pc] | (memory->address[++cp->pc] << 8)];
};

void op_CC(mmu* memory, cpu* cp) {
    // TODO:
    unsigned short nn = memory->address[memory->address[++cp->pc] | (memory->address[++cp->pc] << 8)];

    if(cp->get_z_flag()) {
        cp->stack[--cp->sp] = cp->pc;
        cp->pc = nn;
    }
}

void op_CD(mmu* memory, cpu* cp) {
    // TODO: cp->pc value that is pushed to the cp->stack might be wrong because of the order
    unsigned short nn = memory->address[memory->address[++cp->pc] | (memory->address[++cp->pc] << 8)];
    cp->stack[--cp->sp] = cp->pc;
    cp->pc = nn;
};

void op_CE(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->add8(cp->registers[A], memory->address[cp->pc] + cp->get_c_flag());
}

void op_CF(mmu* memory, cpu* cp) {
    cp->stack[--cp->sp] = cp->pc;
    cp->pc = 0x08;
};

void op_D0(mmu* memory, cpu* cp) {
    if(!cp->get_c_flag())
        cp->pc = cp->stack[cp->sp++];
};

void op_D1(mmu* memory, cpu* cp) {
    cp->registers[E] = cp->stack[cp->sp++];
    cp->registers[D] = cp->stack[cp->sp++];
};

void op_D2(mmu* memory, cpu* cp) {
    if(!cp->get_c_flag())
        cp->pc = memory->address[memory->address[++cp->pc] | (memory->address[++cp->pc] << 8)];
};

void op_D4(mmu* memory, cpu* cp) {
    // TODO:
    unsigned short nn = memory->address[memory->address[++cp->pc] | (memory->address[++cp->pc] << 8)];

    if(!cp->get_c_flag()) {
        cp->stack[--cp->sp] = cp->pc;
        cp->pc = nn;
    }
};

void op_D5(mmu* memory, cpu* cp) {
    cp->stack[--cp->sp] = cp->registers[D];
    cp->stack[--cp->sp] = cp->registers[E];
};

void op_D6(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->sub8(cp->registers[A], memory->address[cp->pc]);
};

void op_D7(mmu* memory, cpu* cp) {
    cp->stack[--cp->sp] = cp->pc;
    cp->pc = 0x10;
};

void op_D8(mmu* memory, cpu* cp) {
    if(cp->get_c_flag())
        cp->pc = cp->stack[cp->sp++];
};

void op_D9(mmu* memory, cpu* cp) {
    // TODO: enable interrupts
    cp->pc = cp->stack[cp->sp++];
};

void op_DA(mmu* memory, cpu* cp) {
    if(cp->get_c_flag())
        cp->pc = memory->address[memory->address[++cp->pc] | (memory->address[++cp->pc] << 8)];
};

void op_DC(mmu* memory, cpu* cp) {
    // TODO:
    unsigned short nn = memory->address[memory->address[++cp->pc] | (memory->address[++cp->pc] << 8)];

    if(cp->get_c_flag()) {
        cp->stack[--cp->sp] = cp->pc;
        cp->pc = nn;
    }
};

void op_DF(mmu* memory, cpu* cp) {
    cp->stack[--cp->sp] = cp->pc;
    cp->pc = 0x18;
};

void op_E0(mmu* memory, cpu* cp) {
    memory->address[0xFF00 + memory->address[++cp->pc]] = cp->registers[A];
};

void op_E1(mmu* memory, cpu* cp) {
    cp->registers[L] = cp->stack[cp->sp++];
    cp->registers[H] = cp->stack[cp->sp++];
};

void op_E2(mmu* memory, cpu* cp) {
    memory->address[0xFF + cp->registers[C]] = cp->registers[A];
};

void op_E5(mmu* memory, cpu* cp) {
    cp->stack[--cp->sp] = cp->registers[H];
    cp->stack[--cp->sp] = cp->registers[L];  
};

void op_E6(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->and8(cp->registers[A], memory->address[cp->pc]);
};

void op_E7(mmu* memory, cpu* cp) {
    cp->stack[--cp->sp] = cp->pc;
    cp->pc = 0x20;
};

void op_E8(mmu* memory, cpu* cp) {

};

void op_E9(mmu* memory, cpu* cp) {
    cp->pc = cp->registers[H] | (cp->registers[L] << 8);
};

void op_EA(mmu* memory, cpu* cp) {
    memory->address[memory->address[++cp->pc] | (memory->address[++cp->pc] << 8)] = cp->registers[A];
};

void op_EE(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->xor8(cp->registers[A], memory->address[cp->pc]);
};

void op_EF(mmu* memory, cpu* cp) {
    cp->stack[--cp->sp] = cp->pc;
    cp->pc = 0x28;
};

void op_F0(mmu* memory, cpu* cp) {
    cp->registers[A] = memory->address[0xFF00 + memory->address[++cp->pc]];
};

void op_F1(mmu* memory, cpu* cp) {
    cp->registers[F] = cp->stack[cp->sp++];
    cp->registers[A] = cp->stack[cp->sp++];
};

void op_F2(mmu* memory, cpu* cp) {
    cp->registers[A] = memory->address[0xFF + cp->registers[C]];
};

void op_F3(mmu* memory, cpu* cp) {

};

void op_F5(mmu* memory, cpu* cp) {
    cp->stack[--cp->sp] = cp->registers[A];
    cp->stack[--cp->sp] = cp->registers[F];
};

void op_F6(mmu* memory, cpu* cp) {
    cp->registers[A] = cp->or8(cp->registers[A], memory->address[cp->pc]);
}

void op_F7(mmu* memory, cpu* cp) {
    cp->stack[--cp->sp] = cp->pc;
    cp->pc = 0x30;
};

void op_F8(mmu* memory, cpu* cp) {
    unsigned short spn = cp->sp + (signed char)memory->address[++cp->pc];   // the value prob is gonna be read as unsigned
    cp->registers[H] = spn & 0x00FF;
    cp->registers[L] = (spn & 0xFF00) >> 8;
};

void op_F9(mmu* memory, cpu* cp) {
    cp->sp = cp->registers[H] | (cp->registers[L] << 8);
};

void op_FA(mmu* memory, cpu* cp) {
    cp->registers[A] = memory->address[++cp->pc] | (memory->address[++cp->pc] << 8);
};

void op_FB(mmu* memory, cpu* cp) {

};

void op_FE(mmu* memory, cpu* cp) {
    cp->cp(cp->registers[A], memory->address[cp->pc]);
};

void op_FF(mmu* memory, cpu* cp) {
    cp->stack[--cp->sp] = cp->pc;
    cp->pc = 0x38;
};

void op_CB(mmu* memory, cpu* cp) {

};

void op_CB_00(mmu* memory, cpu* cp) {
    cp->rlc_r1(B);
};

void op_CB_01(mmu* memory, cpu* cp) {
    cp->rlc_r1(C);
};

void op_CB_02(mmu* memory, cpu* cp) {
    cp->rlc_r1(D);
};

void op_CB_03(mmu* memory, cpu* cp) {
    cp->rlc_r1(E);
};

void op_CB_04(mmu* memory, cpu* cp) {
    cp->rlc_r1(H);
};

void op_CB_05(mmu* memory, cpu* cp) {
    cp->rlc_r1(L);
};

void op_CB_06(mmu* memory, cpu* cp) {

};

void op_CB_07(mmu* memory, cpu* cp) {
    cp->rlc_r1(A);
};

void op_CB_08(mmu* memory, cpu* cp) {
    cp->rrc_r1(B);
};

void op_CB_09(mmu* memory, cpu* cp) {
    cp->rrc_r1(C);
};

void op_CB_0A(mmu* memory, cpu* cp) {
    cp->rrc_r1(D);
};

void op_CB_0B(mmu* memory, cpu* cp) {
    cp->rrc_r1(E);
};

void op_CB_0C(mmu* memory, cpu* cp) {
    cp->rrc_r1(H);
};

void op_CB_0D(mmu* memory, cpu* cp) {
    cp->rrc_r1(L);
};

void op_CB_0E(mmu* memory, cpu* cp) {

};

void op_CB_0F(mmu* memory, cpu* cp) {
    cp->rrc_r1(A);
};

void op_CB_10(mmu* memory, cpu* cp) {
    cp->rl_r1(B);
};

void op_CB_11(mmu* memory, cpu* cp) {
    cp->rl_r1(C);
};

void op_CB_12(mmu* memory, cpu* cp) {
    cp->rl_r1(D);
};

void op_CB_13(mmu* memory, cpu* cp) {
    cp->rl_r1(E);
};

void op_CB_14(mmu* memory, cpu* cp) {
    cp->rl_r1(H);
};

void op_CB_15(mmu* memory, cpu* cp) {
    cp->rl_r1(L);
};

void op_CB_16(mmu* memory, cpu* cp) {

};

void op_CB_17(mmu* memory, cpu* cp) {
    cp->rl_r1(A);
};

void op_CB_18(mmu* memory, cpu* cp) {
    cp->rr_r1(B);
};

void op_CB_19(mmu* memory, cpu* cp) {
    cp->rr_r1(C);
};

void op_CB_1A(mmu* memory, cpu* cp) {
    cp->rr_r1(D);
};

void op_CB_1B(mmu* memory, cpu* cp) {
    cp->rr_r1(E);
};

void op_CB_1C(mmu* memory, cpu* cp) {
    cp->rr_r1(H);
};

void op_CB_1D(mmu* memory, cpu* cp) {
    cp->rr_r1(L);
};

void op_CB_1E(mmu* memory, cpu* cp) {

};

void op_CB_1F(mmu* memory, cpu* cp) {
    cp->rr_r1(A);
};

void op_CB_20(mmu* memory, cpu* cp) {
    cp->sla_r1(B);
};

void op_CB_21(mmu* memory, cpu* cp) {
    cp->sla_r1(C);
};

void op_CB_22(mmu* memory, cpu* cp) {
    cp->sla_r1(D);
};

void op_CB_23(mmu* memory, cpu* cp) {
    cp->sla_r1(E);
};

void op_CB_24(mmu* memory, cpu* cp) {
    cp->sla_r1(H);
};

void op_CB_25(mmu* memory, cpu* cp) {
    cp->sla_r1(L);
};

void op_CB_26(mmu* memory, cpu* cp) {

};

void op_CB_27(mmu* memory, cpu* cp) {
    cp->sla_r1(A);
};

void op_CB_28(mmu* memory, cpu* cp) {
    cp->sra_r1(B);
};

void op_CB_29(mmu* memory, cpu* cp) {
    cp->sra_r1(C);
};

void op_CB_2A(mmu* memory, cpu* cp) {
    cp->sra_r1(D);
};

void op_CB_2B(mmu* memory, cpu* cp) {
    cp->sra_r1(E);
};

void op_CB_2C(mmu* memory, cpu* cp) {
    cp->sra_r1(H);
};

void op_CB_2D(mmu* memory, cpu* cp) {
    cp->sra_r1(L);
};

void op_CB_2E(mmu* memory, cpu* cp) {

};

void op_CB_2F(mmu* memory, cpu* cp) {
    cp->sra_r1(A);
};

void op_CB_30(mmu* memory, cpu* cp) {
    cp->swap_r1(B);
};

void op_CB_31(mmu* memory, cpu* cp) {
    cp->swap_r1(C);
};

void op_CB_32(mmu* memory, cpu* cp) {
    cp->swap_r1(D);
};

void op_CB_33(mmu* memory, cpu* cp) {
    cp->swap_r1(E);
};

void op_CB_34(mmu* memory, cpu* cp) {
    cp->swap_r1(H);
};

void op_CB_35(mmu* memory, cpu* cp) {
    cp->swap_r1(L);
};

void op_CB_36(mmu* memory, cpu* cp) {
    cp->swap_r16(H);
};

void op_CB_37(mmu* memory, cpu* cp) {
    cp->swap_r1(A);
};

void op_CB_38(mmu* memory, cpu* cp) {
    cp->srl_r1(B);
};

void op_CB_39(mmu* memory, cpu* cp) {
    cp->srl_r1(C);
};

void op_CB_3A(mmu* memory, cpu* cp) {
    cp->srl_r1(D);
};

void op_CB_3B(mmu* memory, cpu* cp) {
    cp->srl_r1(E);
};

void op_CB_3C(mmu* memory, cpu* cp) {
    cp->srl_r1(H);
};

void op_CB_3D(mmu* memory, cpu* cp) {
    cp->srl_r1(L);
};

void op_CB_3E(mmu* memory, cpu* cp) {

};

void op_CB_3F(mmu* memory, cpu* cp) {
    cp->srl_r1(A);
};
