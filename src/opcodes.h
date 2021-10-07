#ifndef OPCODES_H
#define OPCODES_H

#include "types.h"
#include "cpu.h"
#include "mmu.h"

typedef struct {
    int cycles;
    int conditional_cycles;
} cycles;

void initialize_optable();
void initialize_optable_cb();
extern void(*optable[0xFF])(Mmu* memory, Cpu* cp);
extern void(*optable_cb[0xBF])(Mmu* memory, Cpu* cp);
extern cycles cycle_table[0xFF];
extern cycles cycle_table_cb[0xBF];


void op_00(Mmu* memory, Cpu* cp);
void op_01(Mmu* memory, Cpu* cp);
void op_02(Mmu* memory, Cpu* cp);
void op_03(Mmu* memory, Cpu* cp);
void op_04(Mmu* memory, Cpu* cp);
void op_05(Mmu* memory, Cpu* cp);
void op_06(Mmu* memory, Cpu* cp);
void op_07(Mmu* memory, Cpu* cp);
void op_08(Mmu* memory, Cpu* cp);
void op_09(Mmu* memory, Cpu* cp);
void op_0A(Mmu* memory, Cpu* cp);
void op_0B(Mmu* memory, Cpu* cp);
void op_0C(Mmu* memory, Cpu* cp);
void op_0D(Mmu* memory, Cpu* cp);
void op_0E(Mmu* memory, Cpu* cp);
void op_0F(Mmu* memory, Cpu* cp);

void op_10(Mmu* memory, Cpu* cp);
void op_11(Mmu* memory, Cpu* cp);
void op_12(Mmu* memory, Cpu* cp);
void op_13(Mmu* memory, Cpu* cp);
void op_14(Mmu* memory, Cpu* cp);
void op_15(Mmu* memory, Cpu* cp);
void op_16(Mmu* memory, Cpu* cp);
void op_17(Mmu* memory, Cpu* cp);
void op_18(Mmu* memory, Cpu* cp);
void op_19(Mmu* memory, Cpu* cp);
void op_1A(Mmu* memory, Cpu* cp);
void op_1B(Mmu* memory, Cpu* cp);
void op_1C(Mmu* memory, Cpu* cp);
void op_1D(Mmu* memory, Cpu* cp);
void op_1E(Mmu* memory, Cpu* cp);
void op_1F(Mmu* memory, Cpu* cp);

void op_20(Mmu* memory, Cpu* cp);
void op_21(Mmu* memory, Cpu* cp);
void op_22(Mmu* memory, Cpu* cp);
void op_23(Mmu* memory, Cpu* cp);
void op_24(Mmu* memory, Cpu* cp);
void op_25(Mmu* memory, Cpu* cp);
void op_26(Mmu* memory, Cpu* cp);
void op_27(Mmu* memory, Cpu* cp);
void op_28(Mmu* memory, Cpu* cp);
void op_29(Mmu* memory, Cpu* cp);
void op_2A(Mmu* memory, Cpu* cp);
void op_2B(Mmu* memory, Cpu* cp);
void op_2C(Mmu* memory, Cpu* cp);
void op_2D(Mmu* memory, Cpu* cp);
void op_2E(Mmu* memory, Cpu* cp);
void op_2F(Mmu* memory, Cpu* cp);

void op_30(Mmu* memory, Cpu* cp);
void op_31(Mmu* memory, Cpu* cp);
void op_32(Mmu* memory, Cpu* cp);
void op_33(Mmu* memory, Cpu* cp);
void op_34(Mmu* memory, Cpu* cp);
void op_35(Mmu* memory, Cpu* cp);
void op_36(Mmu* memory, Cpu* cp);
void op_37(Mmu* memory, Cpu* cp);
void op_38(Mmu* memory, Cpu* cp);
void op_39(Mmu* memory, Cpu* cp);
void op_3A(Mmu* memory, Cpu* cp);
void op_3B(Mmu* memory, Cpu* cp);
void op_3C(Mmu* memory, Cpu* cp);
void op_3D(Mmu* memory, Cpu* cp);
void op_3E(Mmu* memory, Cpu* cp);
void op_3F(Mmu* memory, Cpu* cp);

void op_40(Mmu* memory, Cpu* cp);
void op_41(Mmu* memory, Cpu* cp);
void op_42(Mmu* memory, Cpu* cp);
void op_43(Mmu* memory, Cpu* cp);
void op_44(Mmu* memory, Cpu* cp);
void op_45(Mmu* memory, Cpu* cp);
void op_46(Mmu* memory, Cpu* cp);
void op_47(Mmu* memory, Cpu* cp);
void op_48(Mmu* memory, Cpu* cp);
void op_49(Mmu* memory, Cpu* cp);
void op_4A(Mmu* memory, Cpu* cp);
void op_4B(Mmu* memory, Cpu* cp);
void op_4C(Mmu* memory, Cpu* cp);
void op_4D(Mmu* memory, Cpu* cp);
void op_4E(Mmu* memory, Cpu* cp);
void op_4F(Mmu* memory, Cpu* cp);

void op_50(Mmu* memory, Cpu* cp);
void op_51(Mmu* memory, Cpu* cp);
void op_52(Mmu* memory, Cpu* cp);
void op_53(Mmu* memory, Cpu* cp);
void op_54(Mmu* memory, Cpu* cp);
void op_55(Mmu* memory, Cpu* cp);
void op_56(Mmu* memory, Cpu* cp);
void op_57(Mmu* memory, Cpu* cp);
void op_58(Mmu* memory, Cpu* cp);
void op_59(Mmu* memory, Cpu* cp);
void op_5A(Mmu* memory, Cpu* cp);
void op_5B(Mmu* memory, Cpu* cp);
void op_5C(Mmu* memory, Cpu* cp);
void op_5D(Mmu* memory, Cpu* cp);
void op_5E(Mmu* memory, Cpu* cp);
void op_5F(Mmu* memory, Cpu* cp);

void op_60(Mmu* memory, Cpu* cp);
void op_61(Mmu* memory, Cpu* cp);
void op_62(Mmu* memory, Cpu* cp);
void op_63(Mmu* memory, Cpu* cp);
void op_64(Mmu* memory, Cpu* cp);
void op_65(Mmu* memory, Cpu* cp);
void op_66(Mmu* memory, Cpu* cp);
void op_67(Mmu* memory, Cpu* cp);
void op_68(Mmu* memory, Cpu* cp);
void op_69(Mmu* memory, Cpu* cp);
void op_6A(Mmu* memory, Cpu* cp);
void op_6B(Mmu* memory, Cpu* cp);
void op_6C(Mmu* memory, Cpu* cp);
void op_6D(Mmu* memory, Cpu* cp);
void op_6E(Mmu* memory, Cpu* cp);
void op_6F(Mmu* memory, Cpu* cp);

void op_70(Mmu* memory, Cpu* cp);
void op_71(Mmu* memory, Cpu* cp);
void op_72(Mmu* memory, Cpu* cp);
void op_73(Mmu* memory, Cpu* cp);
void op_74(Mmu* memory, Cpu* cp);
void op_75(Mmu* memory, Cpu* cp);
void op_76(Mmu* memory, Cpu* cp);
void op_77(Mmu* memory, Cpu* cp);
void op_78(Mmu* memory, Cpu* cp);
void op_79(Mmu* memory, Cpu* cp);
void op_7A(Mmu* memory, Cpu* cp);
void op_7B(Mmu* memory, Cpu* cp);
void op_7C(Mmu* memory, Cpu* cp);
void op_7D(Mmu* memory, Cpu* cp);
void op_7E(Mmu* memory, Cpu* cp);
void op_7F(Mmu* memory, Cpu* cp);

void op_80(Mmu* memory, Cpu* cp);
void op_81(Mmu* memory, Cpu* cp);
void op_82(Mmu* memory, Cpu* cp);
void op_83(Mmu* memory, Cpu* cp);
void op_84(Mmu* memory, Cpu* cp);
void op_85(Mmu* memory, Cpu* cp);
void op_86(Mmu* memory, Cpu* cp);
void op_87(Mmu* memory, Cpu* cp);
void op_88(Mmu* memory, Cpu* cp);
void op_89(Mmu* memory, Cpu* cp);
void op_8A(Mmu* memory, Cpu* cp);
void op_8B(Mmu* memory, Cpu* cp);
void op_8C(Mmu* memory, Cpu* cp);
void op_8D(Mmu* memory, Cpu* cp);
void op_8E(Mmu* memory, Cpu* cp);
void op_8F(Mmu* memory, Cpu* cp);

void op_90(Mmu* memory, Cpu* cp);
void op_91(Mmu* memory, Cpu* cp);
void op_92(Mmu* memory, Cpu* cp);
void op_93(Mmu* memory, Cpu* cp);
void op_94(Mmu* memory, Cpu* cp);
void op_95(Mmu* memory, Cpu* cp);
void op_96(Mmu* memory, Cpu* cp);
void op_97(Mmu* memory, Cpu* cp);
void op_98(Mmu* memory, Cpu* cp);
void op_99(Mmu* memory, Cpu* cp);
void op_9A(Mmu* memory, Cpu* cp);
void op_9B(Mmu* memory, Cpu* cp);
void op_9C(Mmu* memory, Cpu* cp);
void op_9D(Mmu* memory, Cpu* cp);
void op_9E(Mmu* memory, Cpu* cp);
void op_9F(Mmu* memory, Cpu* cp);

void op_A0(Mmu* memory, Cpu* cp);
void op_A1(Mmu* memory, Cpu* cp);
void op_A2(Mmu* memory, Cpu* cp);
void op_A3(Mmu* memory, Cpu* cp);
void op_A4(Mmu* memory, Cpu* cp);
void op_A5(Mmu* memory, Cpu* cp);
void op_A6(Mmu* memory, Cpu* cp);
void op_A7(Mmu* memory, Cpu* cp);
void op_A8(Mmu* memory, Cpu* cp);
void op_A9(Mmu* memory, Cpu* cp);
void op_AA(Mmu* memory, Cpu* cp);
void op_AB(Mmu* memory, Cpu* cp);
void op_AC(Mmu* memory, Cpu* cp);
void op_AD(Mmu* memory, Cpu* cp);
void op_AE(Mmu* memory, Cpu* cp);
void op_AF(Mmu* memory, Cpu* cp);

void op_B0(Mmu* memory, Cpu* cp);
void op_B1(Mmu* memory, Cpu* cp);
void op_B2(Mmu* memory, Cpu* cp);
void op_B3(Mmu* memory, Cpu* cp);
void op_B4(Mmu* memory, Cpu* cp);
void op_B5(Mmu* memory, Cpu* cp);
void op_B6(Mmu* memory, Cpu* cp);
void op_B7(Mmu* memory, Cpu* cp);
void op_B8(Mmu* memory, Cpu* cp);
void op_B9(Mmu* memory, Cpu* cp);
void op_BA(Mmu* memory, Cpu* cp);
void op_BB(Mmu* memory, Cpu* cp);
void op_BC(Mmu* memory, Cpu* cp);
void op_BD(Mmu* memory, Cpu* cp);
void op_BE(Mmu* memory, Cpu* cp);
void op_BF(Mmu* memory, Cpu* cp);

void op_C0(Mmu* memory, Cpu* cp);
void op_C1(Mmu* memory, Cpu* cp);
void op_C2(Mmu* memory, Cpu* cp);
void op_C3(Mmu* memory, Cpu* cp);
void op_C4(Mmu* memory, Cpu* cp);
void op_C5(Mmu* memory, Cpu* cp);
void op_C6(Mmu* memory, Cpu* cp);
void op_C7(Mmu* memory, Cpu* cp);
void op_C8(Mmu* memory, Cpu* cp);
void op_C9(Mmu* memory, Cpu* cp);
void op_CA(Mmu* memory, Cpu* cp);
void op_CB(Mmu* memory, Cpu* cp);
void op_CC(Mmu* memory, Cpu* cp);
void op_CD(Mmu* memory, Cpu* cp);
void op_CE(Mmu* memory, Cpu* cp);
void op_CF(Mmu* memory, Cpu* cp);

void op_D0(Mmu* memory, Cpu* cp);
void op_D1(Mmu* memory, Cpu* cp);
void op_D2(Mmu* memory, Cpu* cp);
void op_D3(Mmu* memory, Cpu* cp);
void op_D4(Mmu* memory, Cpu* cp);
void op_D5(Mmu* memory, Cpu* cp);
void op_D6(Mmu* memory, Cpu* cp);
void op_D7(Mmu* memory, Cpu* cp);
void op_D8(Mmu* memory, Cpu* cp);
void op_D9(Mmu* memory, Cpu* cp);
void op_DA(Mmu* memory, Cpu* cp);
void op_DB(Mmu* memory, Cpu* cp);
void op_DC(Mmu* memory, Cpu* cp);
void op_DD(Mmu* memory, Cpu* cp);
void op_DE(Mmu* memory, Cpu* cp);
void op_DF(Mmu* memory, Cpu* cp);

void op_E0(Mmu* memory, Cpu* cp);
void op_E1(Mmu* memory, Cpu* cp);
void op_E2(Mmu* memory, Cpu* cp);
void op_E3(Mmu* memory, Cpu* cp);
void op_E4(Mmu* memory, Cpu* cp);
void op_E5(Mmu* memory, Cpu* cp);
void op_E6(Mmu* memory, Cpu* cp);
void op_E7(Mmu* memory, Cpu* cp);
void op_E8(Mmu* memory, Cpu* cp);
void op_E9(Mmu* memory, Cpu* cp);
void op_EA(Mmu* memory, Cpu* cp);
void op_EB(Mmu* memory, Cpu* cp);
void op_EC(Mmu* memory, Cpu* cp);
void op_ED(Mmu* memory, Cpu* cp);
void op_EE(Mmu* memory, Cpu* cp);
void op_EF(Mmu* memory, Cpu* cp);

void op_F0(Mmu* memory, Cpu* cp);
void op_F1(Mmu* memory, Cpu* cp);
void op_F2(Mmu* memory, Cpu* cp);
void op_F3(Mmu* memory, Cpu* cp);
void op_F4(Mmu* memory, Cpu* cp);
void op_F5(Mmu* memory, Cpu* cp);
void op_F6(Mmu* memory, Cpu* cp);
void op_F7(Mmu* memory, Cpu* cp);
void op_F8(Mmu* memory, Cpu* cp);
void op_F9(Mmu* memory, Cpu* cp);
void op_FA(Mmu* memory, Cpu* cp);
void op_FB(Mmu* memory, Cpu* cp);
void op_FC(Mmu* memory, Cpu* cp);
void op_FD(Mmu* memory, Cpu* cp);
void op_FE(Mmu* memory, Cpu* cp);
void op_FF(Mmu* memory, Cpu* cp);

void op_CB_00(Mmu* memory, Cpu* cp);
void op_CB_01(Mmu* memory, Cpu* cp);
void op_CB_02(Mmu* memory, Cpu* cp);
void op_CB_03(Mmu* memory, Cpu* cp);
void op_CB_04(Mmu* memory, Cpu* cp);
void op_CB_05(Mmu* memory, Cpu* cp);
void op_CB_06(Mmu* memory, Cpu* cp);
void op_CB_07(Mmu* memory, Cpu* cp);
void op_CB_08(Mmu* memory, Cpu* cp);
void op_CB_09(Mmu* memory, Cpu* cp);
void op_CB_0A(Mmu* memory, Cpu* cp);
void op_CB_0B(Mmu* memory, Cpu* cp);
void op_CB_0C(Mmu* memory, Cpu* cp);
void op_CB_0D(Mmu* memory, Cpu* cp);
void op_CB_0E(Mmu* memory, Cpu* cp);
void op_CB_0F(Mmu* memory, Cpu* cp);

void op_CB_10(Mmu* memory, Cpu* cp);
void op_CB_11(Mmu* memory, Cpu* cp);
void op_CB_12(Mmu* memory, Cpu* cp);
void op_CB_13(Mmu* memory, Cpu* cp);
void op_CB_14(Mmu* memory, Cpu* cp);
void op_CB_15(Mmu* memory, Cpu* cp);
void op_CB_16(Mmu* memory, Cpu* cp);
void op_CB_17(Mmu* memory, Cpu* cp);
void op_CB_18(Mmu* memory, Cpu* cp);
void op_CB_19(Mmu* memory, Cpu* cp);
void op_CB_1A(Mmu* memory, Cpu* cp);
void op_CB_1B(Mmu* memory, Cpu* cp);
void op_CB_1C(Mmu* memory, Cpu* cp);
void op_CB_1D(Mmu* memory, Cpu* cp);
void op_CB_1E(Mmu* memory, Cpu* cp);
void op_CB_1F(Mmu* memory, Cpu* cp);

void op_CB_20(Mmu* memory, Cpu* cp);
void op_CB_21(Mmu* memory, Cpu* cp);
void op_CB_22(Mmu* memory, Cpu* cp);
void op_CB_23(Mmu* memory, Cpu* cp);
void op_CB_24(Mmu* memory, Cpu* cp);
void op_CB_25(Mmu* memory, Cpu* cp);
void op_CB_26(Mmu* memory, Cpu* cp);
void op_CB_27(Mmu* memory, Cpu* cp);
void op_CB_28(Mmu* memory, Cpu* cp);
void op_CB_29(Mmu* memory, Cpu* cp);
void op_CB_2A(Mmu* memory, Cpu* cp);
void op_CB_2B(Mmu* memory, Cpu* cp);
void op_CB_2C(Mmu* memory, Cpu* cp);
void op_CB_2D(Mmu* memory, Cpu* cp);
void op_CB_2E(Mmu* memory, Cpu* cp);
void op_CB_2F(Mmu* memory, Cpu* cp);

void op_CB_30(Mmu* memory, Cpu* cp);
void op_CB_31(Mmu* memory, Cpu* cp);
void op_CB_32(Mmu* memory, Cpu* cp);
void op_CB_33(Mmu* memory, Cpu* cp);
void op_CB_34(Mmu* memory, Cpu* cp);
void op_CB_35(Mmu* memory, Cpu* cp);
void op_CB_36(Mmu* memory, Cpu* cp);
void op_CB_37(Mmu* memory, Cpu* cp);
void op_CB_38(Mmu* memory, Cpu* cp);
void op_CB_39(Mmu* memory, Cpu* cp);
void op_CB_3A(Mmu* memory, Cpu* cp);
void op_CB_3B(Mmu* memory, Cpu* cp);
void op_CB_3C(Mmu* memory, Cpu* cp);
void op_CB_3D(Mmu* memory, Cpu* cp);
void op_CB_3E(Mmu* memory, Cpu* cp);
void op_CB_3F(Mmu* memory, Cpu* cp);

void op_CB_40(Mmu* memory, Cpu* cp);
void op_CB_41(Mmu* memory, Cpu* cp);
void op_CB_42(Mmu* memory, Cpu* cp);
void op_CB_43(Mmu* memory, Cpu* cp);
void op_CB_44(Mmu* memory, Cpu* cp);
void op_CB_45(Mmu* memory, Cpu* cp);
void op_CB_46(Mmu* memory, Cpu* cp);
void op_CB_47(Mmu* memory, Cpu* cp);
void op_CB_48(Mmu* memory, Cpu* cp);
void op_CB_49(Mmu* memory, Cpu* cp);
void op_CB_4A(Mmu* memory, Cpu* cp);
void op_CB_4B(Mmu* memory, Cpu* cp);
void op_CB_4C(Mmu* memory, Cpu* cp);
void op_CB_4D(Mmu* memory, Cpu* cp);
void op_CB_4E(Mmu* memory, Cpu* cp);
void op_CB_4F(Mmu* memory, Cpu* cp);

void op_CB_50(Mmu* memory, Cpu* cp);
void op_CB_51(Mmu* memory, Cpu* cp);
void op_CB_52(Mmu* memory, Cpu* cp);
void op_CB_53(Mmu* memory, Cpu* cp);
void op_CB_54(Mmu* memory, Cpu* cp);
void op_CB_55(Mmu* memory, Cpu* cp);
void op_CB_56(Mmu* memory, Cpu* cp);
void op_CB_57(Mmu* memory, Cpu* cp);
void op_CB_58(Mmu* memory, Cpu* cp);
void op_CB_59(Mmu* memory, Cpu* cp);
void op_CB_5A(Mmu* memory, Cpu* cp);
void op_CB_5B(Mmu* memory, Cpu* cp);
void op_CB_5C(Mmu* memory, Cpu* cp);
void op_CB_5D(Mmu* memory, Cpu* cp);
void op_CB_5E(Mmu* memory, Cpu* cp);
void op_CB_5F(Mmu* memory, Cpu* cp);

void op_CB_60(Mmu* memory, Cpu* cp);
void op_CB_61(Mmu* memory, Cpu* cp);
void op_CB_62(Mmu* memory, Cpu* cp);
void op_CB_63(Mmu* memory, Cpu* cp);
void op_CB_64(Mmu* memory, Cpu* cp);
void op_CB_65(Mmu* memory, Cpu* cp);
void op_CB_66(Mmu* memory, Cpu* cp);
void op_CB_67(Mmu* memory, Cpu* cp);
void op_CB_68(Mmu* memory, Cpu* cp);
void op_CB_69(Mmu* memory, Cpu* cp);
void op_CB_6A(Mmu* memory, Cpu* cp);
void op_CB_6B(Mmu* memory, Cpu* cp);
void op_CB_6C(Mmu* memory, Cpu* cp);
void op_CB_6D(Mmu* memory, Cpu* cp);
void op_CB_6E(Mmu* memory, Cpu* cp);
void op_CB_6F(Mmu* memory, Cpu* cp);

void op_CB_70(Mmu* memory, Cpu* cp);
void op_CB_71(Mmu* memory, Cpu* cp);
void op_CB_72(Mmu* memory, Cpu* cp);
void op_CB_73(Mmu* memory, Cpu* cp);
void op_CB_74(Mmu* memory, Cpu* cp);
void op_CB_75(Mmu* memory, Cpu* cp);
void op_CB_76(Mmu* memory, Cpu* cp);
void op_CB_77(Mmu* memory, Cpu* cp);
void op_CB_78(Mmu* memory, Cpu* cp);
void op_CB_79(Mmu* memory, Cpu* cp);
void op_CB_7A(Mmu* memory, Cpu* cp);
void op_CB_7B(Mmu* memory, Cpu* cp);
void op_CB_7C(Mmu* memory, Cpu* cp);
void op_CB_7D(Mmu* memory, Cpu* cp);
void op_CB_7E(Mmu* memory, Cpu* cp);
void op_CB_7F(Mmu* memory, Cpu* cp);

void op_CB_80(Mmu* memory, Cpu* cp);
void op_CB_81(Mmu* memory, Cpu* cp);
void op_CB_82(Mmu* memory, Cpu* cp);
void op_CB_83(Mmu* memory, Cpu* cp);
void op_CB_84(Mmu* memory, Cpu* cp);
void op_CB_85(Mmu* memory, Cpu* cp);
void op_CB_86(Mmu* memory, Cpu* cp);
void op_CB_87(Mmu* memory, Cpu* cp);
void op_CB_88(Mmu* memory, Cpu* cp);
void op_CB_89(Mmu* memory, Cpu* cp);
void op_CB_8A(Mmu* memory, Cpu* cp);
void op_CB_8B(Mmu* memory, Cpu* cp);
void op_CB_8C(Mmu* memory, Cpu* cp);
void op_CB_8D(Mmu* memory, Cpu* cp);
void op_CB_8E(Mmu* memory, Cpu* cp);
void op_CB_8F(Mmu* memory, Cpu* cp);

void op_CB_90(Mmu* memory, Cpu* cp);
void op_CB_91(Mmu* memory, Cpu* cp);
void op_CB_92(Mmu* memory, Cpu* cp);
void op_CB_93(Mmu* memory, Cpu* cp);
void op_CB_94(Mmu* memory, Cpu* cp);
void op_CB_95(Mmu* memory, Cpu* cp);
void op_CB_96(Mmu* memory, Cpu* cp);
void op_CB_97(Mmu* memory, Cpu* cp);
void op_CB_98(Mmu* memory, Cpu* cp);
void op_CB_99(Mmu* memory, Cpu* cp);
void op_CB_9A(Mmu* memory, Cpu* cp);
void op_CB_9B(Mmu* memory, Cpu* cp);
void op_CB_9C(Mmu* memory, Cpu* cp);
void op_CB_9D(Mmu* memory, Cpu* cp);
void op_CB_9E(Mmu* memory, Cpu* cp);
void op_CB_9F(Mmu* memory, Cpu* cp);

void op_CB_A0(Mmu* memory, Cpu* cp);
void op_CB_A1(Mmu* memory, Cpu* cp);
void op_CB_A2(Mmu* memory, Cpu* cp);
void op_CB_A3(Mmu* memory, Cpu* cp);
void op_CB_A4(Mmu* memory, Cpu* cp);
void op_CB_A5(Mmu* memory, Cpu* cp);
void op_CB_A6(Mmu* memory, Cpu* cp);
void op_CB_A7(Mmu* memory, Cpu* cp);
void op_CB_A8(Mmu* memory, Cpu* cp);
void op_CB_A9(Mmu* memory, Cpu* cp);
void op_CB_AA(Mmu* memory, Cpu* cp);
void op_CB_AB(Mmu* memory, Cpu* cp);
void op_CB_AC(Mmu* memory, Cpu* cp);
void op_CB_AD(Mmu* memory, Cpu* cp);
void op_CB_AE(Mmu* memory, Cpu* cp);
void op_CB_AF(Mmu* memory, Cpu* cp);

void op_CB_B0(Mmu* memory, Cpu* cp);
void op_CB_B1(Mmu* memory, Cpu* cp);
void op_CB_B2(Mmu* memory, Cpu* cp);
void op_CB_B3(Mmu* memory, Cpu* cp);
void op_CB_B4(Mmu* memory, Cpu* cp);
void op_CB_B5(Mmu* memory, Cpu* cp);
void op_CB_B6(Mmu* memory, Cpu* cp);
void op_CB_B7(Mmu* memory, Cpu* cp);
void op_CB_B8(Mmu* memory, Cpu* cp);
void op_CB_B9(Mmu* memory, Cpu* cp);
void op_CB_BA(Mmu* memory, Cpu* cp);
void op_CB_BB(Mmu* memory, Cpu* cp);
void op_CB_BC(Mmu* memory, Cpu* cp);
void op_CB_BD(Mmu* memory, Cpu* cp);
void op_CB_BE(Mmu* memory, Cpu* cp);
void op_CB_BF(Mmu* memory, Cpu* cp);

#endif