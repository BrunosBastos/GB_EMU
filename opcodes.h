#include "types.h"
#include "cpu.h"
#include "mmu.h"


void(*optable[0xFF])(mmu* memory, cpu* cp);
void(*optable_cb[0xBF])(mmu* memory, cpu* cp);
byte *cycle_table[0xFF];
byte *cycle_table_cb[0xBF];


void op_00(mmu* memory, cpu* cp);
void op_01(mmu* memory, cpu* cp);
void op_02(mmu* memory, cpu* cp);
void op_03(mmu* memory, cpu* cp);
void op_04(mmu* memory, cpu* cp);
void op_05(mmu* memory, cpu* cp);
void op_06(mmu* memory, cpu* cp);
void op_07(mmu* memory, cpu* cp);
void op_08(mmu* memory, cpu* cp);
void op_09(mmu* memory, cpu* cp);
void op_0A(mmu* memory, cpu* cp);
void op_0B(mmu* memory, cpu* cp);
void op_0C(mmu* memory, cpu* cp);
void op_0D(mmu* memory, cpu* cp);
void op_0E(mmu* memory, cpu* cp);
void op_0F(mmu* memory, cpu* cp);

void op_10(mmu* memory, cpu* cp);
void op_11(mmu* memory, cpu* cp);
void op_12(mmu* memory, cpu* cp);
void op_13(mmu* memory, cpu* cp);
void op_14(mmu* memory, cpu* cp);
void op_15(mmu* memory, cpu* cp);
void op_16(mmu* memory, cpu* cp);
void op_17(mmu* memory, cpu* cp);
void op_18(mmu* memory, cpu* cp);
void op_19(mmu* memory, cpu* cp);
void op_1A(mmu* memory, cpu* cp);
void op_1B(mmu* memory, cpu* cp);
void op_1C(mmu* memory, cpu* cp);
void op_1D(mmu* memory, cpu* cp);
void op_1E(mmu* memory, cpu* cp);
void op_1F(mmu* memory, cpu* cp);

void op_20(mmu* memory, cpu* cp);
void op_21(mmu* memory, cpu* cp);
void op_22(mmu* memory, cpu* cp);
void op_23(mmu* memory, cpu* cp);
void op_24(mmu* memory, cpu* cp);
void op_25(mmu* memory, cpu* cp);
void op_26(mmu* memory, cpu* cp);
void op_27(mmu* memory, cpu* cp);
void op_28(mmu* memory, cpu* cp);
void op_29(mmu* memory, cpu* cp);
void op_2A(mmu* memory, cpu* cp);
void op_2B(mmu* memory, cpu* cp);
void op_2C(mmu* memory, cpu* cp);
void op_2D(mmu* memory, cpu* cp);
void op_2E(mmu* memory, cpu* cp);
void op_2F(mmu* memory, cpu* cp);

void op_30(mmu* memory, cpu* cp);
void op_31(mmu* memory, cpu* cp);
void op_32(mmu* memory, cpu* cp);
void op_33(mmu* memory, cpu* cp);
void op_34(mmu* memory, cpu* cp);
void op_35(mmu* memory, cpu* cp);
void op_36(mmu* memory, cpu* cp);
void op_37(mmu* memory, cpu* cp);
void op_38(mmu* memory, cpu* cp);
void op_39(mmu* memory, cpu* cp);
void op_3A(mmu* memory, cpu* cp);
void op_3B(mmu* memory, cpu* cp);
void op_3C(mmu* memory, cpu* cp);
void op_3D(mmu* memory, cpu* cp);
void op_3E(mmu* memory, cpu* cp);
void op_3F(mmu* memory, cpu* cp);

void op_40(mmu* memory, cpu* cp);
void op_41(mmu* memory, cpu* cp);
void op_42(mmu* memory, cpu* cp);
void op_43(mmu* memory, cpu* cp);
void op_44(mmu* memory, cpu* cp);
void op_45(mmu* memory, cpu* cp);
void op_46(mmu* memory, cpu* cp);
void op_47(mmu* memory, cpu* cp);
void op_48(mmu* memory, cpu* cp);
void op_49(mmu* memory, cpu* cp);
void op_4A(mmu* memory, cpu* cp);
void op_4B(mmu* memory, cpu* cp);
void op_4C(mmu* memory, cpu* cp);
void op_4D(mmu* memory, cpu* cp);
void op_4E(mmu* memory, cpu* cp);
void op_4F(mmu* memory, cpu* cp);

void op_50(mmu* memory, cpu* cp);
void op_51(mmu* memory, cpu* cp);
void op_52(mmu* memory, cpu* cp);
void op_53(mmu* memory, cpu* cp);
void op_54(mmu* memory, cpu* cp);
void op_55(mmu* memory, cpu* cp);
void op_56(mmu* memory, cpu* cp);
void op_57(mmu* memory, cpu* cp);
void op_58(mmu* memory, cpu* cp);
void op_59(mmu* memory, cpu* cp);
void op_5A(mmu* memory, cpu* cp);
void op_5B(mmu* memory, cpu* cp);
void op_5C(mmu* memory, cpu* cp);
void op_5D(mmu* memory, cpu* cp);
void op_5E(mmu* memory, cpu* cp);
void op_5F(mmu* memory, cpu* cp);

void op_60(mmu* memory, cpu* cp);
void op_61(mmu* memory, cpu* cp);
void op_62(mmu* memory, cpu* cp);
void op_63(mmu* memory, cpu* cp);
void op_64(mmu* memory, cpu* cp);
void op_65(mmu* memory, cpu* cp);
void op_66(mmu* memory, cpu* cp);
void op_67(mmu* memory, cpu* cp);
void op_68(mmu* memory, cpu* cp);
void op_69(mmu* memory, cpu* cp);
void op_6A(mmu* memory, cpu* cp);
void op_6B(mmu* memory, cpu* cp);
void op_6C(mmu* memory, cpu* cp);
void op_6D(mmu* memory, cpu* cp);
void op_6E(mmu* memory, cpu* cp);
void op_6F(mmu* memory, cpu* cp);

void op_70(mmu* memory, cpu* cp);
void op_71(mmu* memory, cpu* cp);
void op_72(mmu* memory, cpu* cp);
void op_73(mmu* memory, cpu* cp);
void op_74(mmu* memory, cpu* cp);
void op_75(mmu* memory, cpu* cp);
void op_76(mmu* memory, cpu* cp);
void op_77(mmu* memory, cpu* cp);
void op_78(mmu* memory, cpu* cp);
void op_79(mmu* memory, cpu* cp);
void op_7A(mmu* memory, cpu* cp);
void op_7B(mmu* memory, cpu* cp);
void op_7C(mmu* memory, cpu* cp);
void op_7D(mmu* memory, cpu* cp);
void op_7E(mmu* memory, cpu* cp);
void op_7F(mmu* memory, cpu* cp);

void op_80(mmu* memory, cpu* cp);
void op_81(mmu* memory, cpu* cp);
void op_82(mmu* memory, cpu* cp);
void op_83(mmu* memory, cpu* cp);
void op_84(mmu* memory, cpu* cp);
void op_85(mmu* memory, cpu* cp);
void op_86(mmu* memory, cpu* cp);
void op_87(mmu* memory, cpu* cp);
void op_88(mmu* memory, cpu* cp);
void op_89(mmu* memory, cpu* cp);
void op_8A(mmu* memory, cpu* cp);
void op_8B(mmu* memory, cpu* cp);
void op_8C(mmu* memory, cpu* cp);
void op_8D(mmu* memory, cpu* cp);
void op_8E(mmu* memory, cpu* cp);
void op_8F(mmu* memory, cpu* cp);

void op_90(mmu* memory, cpu* cp);
void op_91(mmu* memory, cpu* cp);
void op_92(mmu* memory, cpu* cp);
void op_93(mmu* memory, cpu* cp);
void op_94(mmu* memory, cpu* cp);
void op_95(mmu* memory, cpu* cp);
void op_96(mmu* memory, cpu* cp);
void op_97(mmu* memory, cpu* cp);
void op_98(mmu* memory, cpu* cp);
void op_99(mmu* memory, cpu* cp);
void op_9A(mmu* memory, cpu* cp);
void op_9B(mmu* memory, cpu* cp);
void op_9C(mmu* memory, cpu* cp);
void op_9D(mmu* memory, cpu* cp);
void op_9E(mmu* memory, cpu* cp);
void op_9F(mmu* memory, cpu* cp);

void op_A0(mmu* memory, cpu* cp);
void op_A1(mmu* memory, cpu* cp);
void op_A2(mmu* memory, cpu* cp);
void op_A3(mmu* memory, cpu* cp);
void op_A4(mmu* memory, cpu* cp);
void op_A5(mmu* memory, cpu* cp);
void op_A6(mmu* memory, cpu* cp);
void op_A7(mmu* memory, cpu* cp);
void op_A8(mmu* memory, cpu* cp);
void op_A9(mmu* memory, cpu* cp);
void op_AA(mmu* memory, cpu* cp);
void op_AB(mmu* memory, cpu* cp);
void op_AC(mmu* memory, cpu* cp);
void op_AD(mmu* memory, cpu* cp);
void op_AE(mmu* memory, cpu* cp);
void op_AF(mmu* memory, cpu* cp);

void op_B0(mmu* memory, cpu* cp);
void op_B1(mmu* memory, cpu* cp);
void op_B2(mmu* memory, cpu* cp);
void op_B3(mmu* memory, cpu* cp);
void op_B4(mmu* memory, cpu* cp);
void op_B5(mmu* memory, cpu* cp);
void op_B6(mmu* memory, cpu* cp);
void op_B7(mmu* memory, cpu* cp);
void op_B8(mmu* memory, cpu* cp);
void op_B9(mmu* memory, cpu* cp);
void op_BA(mmu* memory, cpu* cp);
void op_BB(mmu* memory, cpu* cp);
void op_BC(mmu* memory, cpu* cp);
void op_BD(mmu* memory, cpu* cp);
void op_BE(mmu* memory, cpu* cp);
void op_BF(mmu* memory, cpu* cp);

void op_C0(mmu* memory, cpu* cp);
void op_C1(mmu* memory, cpu* cp);
void op_C2(mmu* memory, cpu* cp);
void op_C3(mmu* memory, cpu* cp);
void op_C4(mmu* memory, cpu* cp);
void op_C5(mmu* memory, cpu* cp);
void op_C6(mmu* memory, cpu* cp);
void op_C7(mmu* memory, cpu* cp);
void op_C8(mmu* memory, cpu* cp);
void op_C9(mmu* memory, cpu* cp);
void op_CA(mmu* memory, cpu* cp);
void op_CB(mmu* memory, cpu* cp);
void op_CC(mmu* memory, cpu* cp);
void op_CD(mmu* memory, cpu* cp);
void op_CE(mmu* memory, cpu* cp);
void op_CF(mmu* memory, cpu* cp);

void op_D0(mmu* memory, cpu* cp);
void op_D1(mmu* memory, cpu* cp);
void op_D2(mmu* memory, cpu* cp);
void op_D3(mmu* memory, cpu* cp);
void op_D4(mmu* memory, cpu* cp);
void op_D5(mmu* memory, cpu* cp);
void op_D6(mmu* memory, cpu* cp);
void op_D7(mmu* memory, cpu* cp);
void op_D8(mmu* memory, cpu* cp);
void op_D9(mmu* memory, cpu* cp);
void op_DA(mmu* memory, cpu* cp);
void op_DB(mmu* memory, cpu* cp);
void op_DC(mmu* memory, cpu* cp);
void op_DD(mmu* memory, cpu* cp);
void op_DE(mmu* memory, cpu* cp);
void op_DF(mmu* memory, cpu* cp);

void op_E0(mmu* memory, cpu* cp);
void op_E1(mmu* memory, cpu* cp);
void op_E2(mmu* memory, cpu* cp);
void op_E3(mmu* memory, cpu* cp);
void op_E4(mmu* memory, cpu* cp);
void op_E5(mmu* memory, cpu* cp);
void op_E6(mmu* memory, cpu* cp);
void op_E7(mmu* memory, cpu* cp);
void op_E8(mmu* memory, cpu* cp);
void op_E9(mmu* memory, cpu* cp);
void op_EA(mmu* memory, cpu* cp);
void op_EB(mmu* memory, cpu* cp);
void op_EC(mmu* memory, cpu* cp);
void op_ED(mmu* memory, cpu* cp);
void op_EE(mmu* memory, cpu* cp);
void op_EF(mmu* memory, cpu* cp);

void op_F0(mmu* memory, cpu* cp);
void op_F1(mmu* memory, cpu* cp);
void op_F2(mmu* memory, cpu* cp);
void op_F3(mmu* memory, cpu* cp);
void op_F4(mmu* memory, cpu* cp);
void op_F5(mmu* memory, cpu* cp);
void op_F6(mmu* memory, cpu* cp);
void op_F7(mmu* memory, cpu* cp);
void op_F8(mmu* memory, cpu* cp);
void op_F9(mmu* memory, cpu* cp);
void op_FA(mmu* memory, cpu* cp);
void op_FB(mmu* memory, cpu* cp);
void op_FC(mmu* memory, cpu* cp);
void op_FD(mmu* memory, cpu* cp);
void op_FE(mmu* memory, cpu* cp);
void op_FF(mmu* memory, cpu* cp);

void op_CB_00(mmu* memory, cpu* cp);
void op_CB_01(mmu* memory, cpu* cp);
void op_CB_02(mmu* memory, cpu* cp);
void op_CB_03(mmu* memory, cpu* cp);
void op_CB_04(mmu* memory, cpu* cp);
void op_CB_05(mmu* memory, cpu* cp);
void op_CB_06(mmu* memory, cpu* cp);
void op_CB_07(mmu* memory, cpu* cp);
void op_CB_08(mmu* memory, cpu* cp);
void op_CB_09(mmu* memory, cpu* cp);
void op_CB_0A(mmu* memory, cpu* cp);
void op_CB_0B(mmu* memory, cpu* cp);
void op_CB_0C(mmu* memory, cpu* cp);
void op_CB_0D(mmu* memory, cpu* cp);
void op_CB_0E(mmu* memory, cpu* cp);
void op_CB_0F(mmu* memory, cpu* cp);

void op_CB_10(mmu* memory, cpu* cp);
void op_CB_11(mmu* memory, cpu* cp);
void op_CB_12(mmu* memory, cpu* cp);
void op_CB_13(mmu* memory, cpu* cp);
void op_CB_14(mmu* memory, cpu* cp);
void op_CB_15(mmu* memory, cpu* cp);
void op_CB_16(mmu* memory, cpu* cp);
void op_CB_17(mmu* memory, cpu* cp);
void op_CB_18(mmu* memory, cpu* cp);
void op_CB_19(mmu* memory, cpu* cp);
void op_CB_1A(mmu* memory, cpu* cp);
void op_CB_1B(mmu* memory, cpu* cp);
void op_CB_1C(mmu* memory, cpu* cp);
void op_CB_1D(mmu* memory, cpu* cp);
void op_CB_1E(mmu* memory, cpu* cp);
void op_CB_1F(mmu* memory, cpu* cp);

void op_CB_20(mmu* memory, cpu* cp);
void op_CB_21(mmu* memory, cpu* cp);
void op_CB_22(mmu* memory, cpu* cp);
void op_CB_23(mmu* memory, cpu* cp);
void op_CB_24(mmu* memory, cpu* cp);
void op_CB_25(mmu* memory, cpu* cp);
void op_CB_26(mmu* memory, cpu* cp);
void op_CB_27(mmu* memory, cpu* cp);
void op_CB_28(mmu* memory, cpu* cp);
void op_CB_29(mmu* memory, cpu* cp);
void op_CB_2A(mmu* memory, cpu* cp);
void op_CB_2B(mmu* memory, cpu* cp);
void op_CB_2C(mmu* memory, cpu* cp);
void op_CB_2D(mmu* memory, cpu* cp);
void op_CB_2E(mmu* memory, cpu* cp);
void op_CB_2F(mmu* memory, cpu* cp);

void op_CB_30(mmu* memory, cpu* cp);
void op_CB_31(mmu* memory, cpu* cp);
void op_CB_32(mmu* memory, cpu* cp);
void op_CB_33(mmu* memory, cpu* cp);
void op_CB_34(mmu* memory, cpu* cp);
void op_CB_35(mmu* memory, cpu* cp);
void op_CB_36(mmu* memory, cpu* cp);
void op_CB_37(mmu* memory, cpu* cp);
void op_CB_38(mmu* memory, cpu* cp);
void op_CB_39(mmu* memory, cpu* cp);
void op_CB_3A(mmu* memory, cpu* cp);
void op_CB_3B(mmu* memory, cpu* cp);
void op_CB_3C(mmu* memory, cpu* cp);
void op_CB_3D(mmu* memory, cpu* cp);
void op_CB_3E(mmu* memory, cpu* cp);
void op_CB_3F(mmu* memory, cpu* cp);

void op_CB_40(mmu* memory, cpu* cp);
void op_CB_41(mmu* memory, cpu* cp);
void op_CB_42(mmu* memory, cpu* cp);
void op_CB_43(mmu* memory, cpu* cp);
void op_CB_44(mmu* memory, cpu* cp);
void op_CB_45(mmu* memory, cpu* cp);
void op_CB_46(mmu* memory, cpu* cp);
void op_CB_47(mmu* memory, cpu* cp);
void op_CB_48(mmu* memory, cpu* cp);
void op_CB_49(mmu* memory, cpu* cp);
void op_CB_4A(mmu* memory, cpu* cp);
void op_CB_4B(mmu* memory, cpu* cp);
void op_CB_4C(mmu* memory, cpu* cp);
void op_CB_4D(mmu* memory, cpu* cp);
void op_CB_4E(mmu* memory, cpu* cp);
void op_CB_4F(mmu* memory, cpu* cp);

void op_CB_50(mmu* memory, cpu* cp);
void op_CB_51(mmu* memory, cpu* cp);
void op_CB_52(mmu* memory, cpu* cp);
void op_CB_53(mmu* memory, cpu* cp);
void op_CB_54(mmu* memory, cpu* cp);
void op_CB_55(mmu* memory, cpu* cp);
void op_CB_56(mmu* memory, cpu* cp);
void op_CB_57(mmu* memory, cpu* cp);
void op_CB_58(mmu* memory, cpu* cp);
void op_CB_59(mmu* memory, cpu* cp);
void op_CB_5A(mmu* memory, cpu* cp);
void op_CB_5B(mmu* memory, cpu* cp);
void op_CB_5C(mmu* memory, cpu* cp);
void op_CB_5D(mmu* memory, cpu* cp);
void op_CB_5E(mmu* memory, cpu* cp);
void op_CB_5F(mmu* memory, cpu* cp);

void op_CB_60(mmu* memory, cpu* cp);
void op_CB_61(mmu* memory, cpu* cp);
void op_CB_62(mmu* memory, cpu* cp);
void op_CB_63(mmu* memory, cpu* cp);
void op_CB_64(mmu* memory, cpu* cp);
void op_CB_65(mmu* memory, cpu* cp);
void op_CB_66(mmu* memory, cpu* cp);
void op_CB_67(mmu* memory, cpu* cp);
void op_CB_68(mmu* memory, cpu* cp);
void op_CB_69(mmu* memory, cpu* cp);
void op_CB_6A(mmu* memory, cpu* cp);
void op_CB_6B(mmu* memory, cpu* cp);
void op_CB_6C(mmu* memory, cpu* cp);
void op_CB_6D(mmu* memory, cpu* cp);
void op_CB_6E(mmu* memory, cpu* cp);
void op_CB_6F(mmu* memory, cpu* cp);

void op_CB_70(mmu* memory, cpu* cp);
void op_CB_71(mmu* memory, cpu* cp);
void op_CB_72(mmu* memory, cpu* cp);
void op_CB_73(mmu* memory, cpu* cp);
void op_CB_74(mmu* memory, cpu* cp);
void op_CB_75(mmu* memory, cpu* cp);
void op_CB_76(mmu* memory, cpu* cp);
void op_CB_77(mmu* memory, cpu* cp);
void op_CB_78(mmu* memory, cpu* cp);
void op_CB_79(mmu* memory, cpu* cp);
void op_CB_7A(mmu* memory, cpu* cp);
void op_CB_7B(mmu* memory, cpu* cp);
void op_CB_7C(mmu* memory, cpu* cp);
void op_CB_7D(mmu* memory, cpu* cp);
void op_CB_7E(mmu* memory, cpu* cp);
void op_CB_7F(mmu* memory, cpu* cp);

void op_CB_80(mmu* memory, cpu* cp);
void op_CB_81(mmu* memory, cpu* cp);
void op_CB_82(mmu* memory, cpu* cp);
void op_CB_83(mmu* memory, cpu* cp);
void op_CB_84(mmu* memory, cpu* cp);
void op_CB_85(mmu* memory, cpu* cp);
void op_CB_86(mmu* memory, cpu* cp);
void op_CB_87(mmu* memory, cpu* cp);
void op_CB_88(mmu* memory, cpu* cp);
void op_CB_89(mmu* memory, cpu* cp);
void op_CB_8A(mmu* memory, cpu* cp);
void op_CB_8B(mmu* memory, cpu* cp);
void op_CB_8C(mmu* memory, cpu* cp);
void op_CB_8D(mmu* memory, cpu* cp);
void op_CB_8E(mmu* memory, cpu* cp);
void op_CB_8F(mmu* memory, cpu* cp);

void op_CB_90(mmu* memory, cpu* cp);
void op_CB_91(mmu* memory, cpu* cp);
void op_CB_92(mmu* memory, cpu* cp);
void op_CB_93(mmu* memory, cpu* cp);
void op_CB_94(mmu* memory, cpu* cp);
void op_CB_95(mmu* memory, cpu* cp);
void op_CB_96(mmu* memory, cpu* cp);
void op_CB_97(mmu* memory, cpu* cp);
void op_CB_98(mmu* memory, cpu* cp);
void op_CB_99(mmu* memory, cpu* cp);
void op_CB_9A(mmu* memory, cpu* cp);
void op_CB_9B(mmu* memory, cpu* cp);
void op_CB_9C(mmu* memory, cpu* cp);
void op_CB_9D(mmu* memory, cpu* cp);
void op_CB_9E(mmu* memory, cpu* cp);
void op_CB_9F(mmu* memory, cpu* cp);

void op_CB_A0(mmu* memory, cpu* cp);
void op_CB_A1(mmu* memory, cpu* cp);
void op_CB_A2(mmu* memory, cpu* cp);
void op_CB_A3(mmu* memory, cpu* cp);
void op_CB_A4(mmu* memory, cpu* cp);
void op_CB_A5(mmu* memory, cpu* cp);
void op_CB_A6(mmu* memory, cpu* cp);
void op_CB_A7(mmu* memory, cpu* cp);
void op_CB_A8(mmu* memory, cpu* cp);
void op_CB_A9(mmu* memory, cpu* cp);
void op_CB_AA(mmu* memory, cpu* cp);
void op_CB_AB(mmu* memory, cpu* cp);
void op_CB_AC(mmu* memory, cpu* cp);
void op_CB_AD(mmu* memory, cpu* cp);
void op_CB_AE(mmu* memory, cpu* cp);
void op_CB_AF(mmu* memory, cpu* cp);

void op_CB_B0(mmu* memory, cpu* cp);
void op_CB_B1(mmu* memory, cpu* cp);
void op_CB_B2(mmu* memory, cpu* cp);
void op_CB_B3(mmu* memory, cpu* cp);
void op_CB_B4(mmu* memory, cpu* cp);
void op_CB_B5(mmu* memory, cpu* cp);
void op_CB_B6(mmu* memory, cpu* cp);
void op_CB_B7(mmu* memory, cpu* cp);
void op_CB_B8(mmu* memory, cpu* cp);
void op_CB_B9(mmu* memory, cpu* cp);
void op_CB_BA(mmu* memory, cpu* cp);
void op_CB_BB(mmu* memory, cpu* cp);
void op_CB_BC(mmu* memory, cpu* cp);
void op_CB_BD(mmu* memory, cpu* cp);
void op_CB_BE(mmu* memory, cpu* cp);
void op_CB_BF(mmu* memory, cpu* cp);