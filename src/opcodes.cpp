#include "opcodes.h"


void (*optable[0xFF])(Mmu* mmu, Cpu* cp);
void (*optable_cb[0xBF])(Mmu* mmu, Cpu* cp);
cycles cycle_table[0xFF];
cycles cycle_table_cb[0xBF];


void initialize_optable() {
    optable[0x00] = &op_00; cycle_table[0x00] = {1, 0};
    optable[0x01] = &op_01; cycle_table[0x01] = {3, 0};
    optable[0x02] = &op_02; cycle_table[0x02] = {2, 0};
    optable[0x03] = &op_03; cycle_table[0x03] = {2, 0};
    optable[0x04] = &op_04; cycle_table[0x04] = {1, 0};
    optable[0x05] = &op_05; cycle_table[0x05] = {1, 0};
    optable[0x06] = &op_06; cycle_table[0x06] = {2, 0};
    optable[0x07] = &op_07; cycle_table[0x07] = {1, 0};
    optable[0x08] = &op_08; cycle_table[0x08] = {5, 0};
    optable[0x09] = &op_09; cycle_table[0x09] = {2, 0};
    optable[0x0A] = &op_0A; cycle_table[0x0A] = {2, 0};
    optable[0x0B] = &op_0B; cycle_table[0x0B] = {2, 0};
    optable[0x0C] = &op_0C; cycle_table[0x0C] = {1, 0};
    optable[0x0D] = &op_0D; cycle_table[0x0D] = {1, 0};
    optable[0x0E] = &op_0E; cycle_table[0x0E] = {2, 0};
    optable[0x0F] = &op_0F; cycle_table[0x0F] = {1, 0};

    optable[0x10] = &op_10; cycle_table[0x10] = {1, 0};
    optable[0x11] = &op_11; cycle_table[0x11] = {3, 0};
    optable[0x12] = &op_12; cycle_table[0x12] = {2, 0};
    optable[0x13] = &op_13; cycle_table[0x13] = {2, 0};
    optable[0x14] = &op_14; cycle_table[0x14] = {1, 0};
    optable[0x15] = &op_15; cycle_table[0x15] = {1, 0};
    optable[0x16] = &op_16; cycle_table[0x16] = {2, 0};
    optable[0x17] = &op_17; cycle_table[0x17] = {1, 0};
    optable[0x18] = &op_18; cycle_table[0x18] = {3, 0};
    optable[0x19] = &op_19; cycle_table[0x19] = {2, 0};
    optable[0x1A] = &op_1A; cycle_table[0x1A] = {2, 0};
    optable[0x1B] = &op_1B; cycle_table[0x1B] = {2, 0};
    optable[0x1C] = &op_1C; cycle_table[0x1C] = {1, 0};
    optable[0x1D] = &op_1D; cycle_table[0x1D] = {1, 0};
    optable[0x1E] = &op_1E; cycle_table[0x1E] = {2, 0};
    optable[0x1F] = &op_1F; cycle_table[0x1F] = {1, 0};

    optable[0x20] = &op_20; cycle_table[0x20] = {2, 1};
    optable[0x21] = &op_21; cycle_table[0x21] = {3, 0};
    optable[0x22] = &op_22; cycle_table[0x22] = {2, 0};
    optable[0x23] = &op_23; cycle_table[0x23] = {2, 0};
    optable[0x24] = &op_24; cycle_table[0x24] = {1, 0};
    optable[0x25] = &op_25; cycle_table[0x25] = {1, 0};
    optable[0x26] = &op_26; cycle_table[0x26] = {2, 0};
    optable[0x27] = &op_27; cycle_table[0x27] = {1, 0};
    optable[0x28] = &op_28; cycle_table[0x28] = {2, 1};
    optable[0x29] = &op_29; cycle_table[0x29] = {2, 0};
    optable[0x2A] = &op_2A; cycle_table[0x2A] = {2, 0};
    optable[0x2B] = &op_2B; cycle_table[0x2B] = {2, 0};
    optable[0x2C] = &op_2C; cycle_table[0x2C] = {1, 0};
    optable[0x2D] = &op_2D; cycle_table[0x2D] = {1, 0};
    optable[0x2E] = &op_2E; cycle_table[0x2E] = {2, 0};
    optable[0x2F] = &op_2F; cycle_table[0x2F] = {1, 0};

    optable[0x30] = &op_30; cycle_table[0x30] = {2, 1};
    optable[0x31] = &op_31; cycle_table[0x31] = {3, 0};
    optable[0x32] = &op_32; cycle_table[0x32] = {2, 0};
    optable[0x33] = &op_33; cycle_table[0x33] = {2, 0};
    optable[0x34] = &op_34; cycle_table[0x34] = {3, 0};
    optable[0x35] = &op_35; cycle_table[0x35] = {3, 0};
    optable[0x36] = &op_36; cycle_table[0x36] = {3, 0};
    optable[0x37] = &op_37; cycle_table[0x37] = {1, 0};
    optable[0x38] = &op_38; cycle_table[0x38] = {2, 1};
    optable[0x39] = &op_39; cycle_table[0x39] = {2, 0};
    optable[0x3A] = &op_3A; cycle_table[0x3A] = {2, 0};
    optable[0x3B] = &op_3B; cycle_table[0x3B] = {2, 0};
    optable[0x3C] = &op_3C; cycle_table[0x3C] = {1, 0};
    optable[0x3D] = &op_3D; cycle_table[0x3D] = {1, 0};
    optable[0x3E] = &op_3E; cycle_table[0x3E] = {2, 0};
    optable[0x3F] = &op_3F; cycle_table[0x3F] = {1, 0};

    optable[0x40] = &op_40; cycle_table[0x40] = {1, 0};
    optable[0x41] = &op_41; cycle_table[0x41] = {1, 0};
    optable[0x42] = &op_42; cycle_table[0x42] = {1, 0};
    optable[0x43] = &op_43; cycle_table[0x43] = {1, 0};
    optable[0x44] = &op_44; cycle_table[0x44] = {1, 0};
    optable[0x45] = &op_45; cycle_table[0x45] = {1, 0};
    optable[0x46] = &op_46; cycle_table[0x46] = {2, 0};
    optable[0x47] = &op_47; cycle_table[0x47] = {1, 0};
    optable[0x48] = &op_48; cycle_table[0x48] = {1, 0};
    optable[0x49] = &op_49; cycle_table[0x49] = {1, 0};
    optable[0x4A] = &op_4A; cycle_table[0x4A] = {1, 0};
    optable[0x4B] = &op_4B; cycle_table[0x4B] = {1, 0};
    optable[0x4C] = &op_4C; cycle_table[0x4C] = {1, 0};
    optable[0x4D] = &op_4D; cycle_table[0x4D] = {1, 0};
    optable[0x4E] = &op_4E; cycle_table[0x4E] = {2, 0};
    optable[0x4F] = &op_4F; cycle_table[0x4F] = {1, 0};

    optable[0x50] = &op_50; cycle_table[0x50] = {1, 0};
    optable[0x51] = &op_51; cycle_table[0x51] = {1, 0};
    optable[0x52] = &op_52; cycle_table[0x52] = {1, 0};
    optable[0x53] = &op_53; cycle_table[0x53] = {1, 0};
    optable[0x54] = &op_54; cycle_table[0x54] = {1, 0};
    optable[0x55] = &op_55; cycle_table[0x55] = {1, 0};
    optable[0x56] = &op_56; cycle_table[0x56] = {2, 0};
    optable[0x57] = &op_57; cycle_table[0x57] = {1, 0};
    optable[0x58] = &op_58; cycle_table[0x58] = {1, 0};
    optable[0x59] = &op_59; cycle_table[0x59] = {1, 0};
    optable[0x5A] = &op_5A; cycle_table[0x5A] = {1, 0};
    optable[0x5B] = &op_5B; cycle_table[0x5B] = {1, 0};
    optable[0x5C] = &op_5C; cycle_table[0x5C] = {1, 0};
    optable[0x5D] = &op_5D; cycle_table[0x5D] = {1, 0};
    optable[0x5E] = &op_5E; cycle_table[0x5E] = {2, 0};
    optable[0x5F] = &op_5F; cycle_table[0x5F] = {1, 0};

    optable[0x60] = &op_60; cycle_table[0x60] = {1, 0};
    optable[0x61] = &op_61; cycle_table[0x61] = {1, 0};
    optable[0x62] = &op_62; cycle_table[0x62] = {1, 0};
    optable[0x63] = &op_63; cycle_table[0x63] = {1, 0};
    optable[0x64] = &op_64; cycle_table[0x64] = {1, 0};
    optable[0x65] = &op_65; cycle_table[0x65] = {1, 0};
    optable[0x66] = &op_66; cycle_table[0x66] = {2, 0};
    optable[0x67] = &op_67; cycle_table[0x67] = {1, 0};
    optable[0x68] = &op_68; cycle_table[0x68] = {1, 0};
    optable[0x69] = &op_69; cycle_table[0x69] = {1, 0};
    optable[0x6A] = &op_6A; cycle_table[0x6A] = {1, 0};
    optable[0x6B] = &op_6B; cycle_table[0x6B] = {1, 0};
    optable[0x6C] = &op_6C; cycle_table[0x6C] = {1, 0};
    optable[0x6D] = &op_6D; cycle_table[0x6D] = {1, 0};
    optable[0x6E] = &op_6E; cycle_table[0x6E] = {2, 0};
    optable[0x6F] = &op_6F; cycle_table[0x6F] = {1, 0};

    optable[0x70] = &op_70; cycle_table[0x70] = {2, 0};
    optable[0x71] = &op_71; cycle_table[0x71] = {2, 0};
    optable[0x72] = &op_72; cycle_table[0x72] = {2, 0};
    optable[0x73] = &op_73; cycle_table[0x73] = {2, 0};
    optable[0x74] = &op_74; cycle_table[0x74] = {2, 0};
    optable[0x75] = &op_75; cycle_table[0x75] = {2, 0};
    optable[0x76] = &op_76; cycle_table[0x76] = {1, 0};
    optable[0x77] = &op_77; cycle_table[0x77] = {2, 0};
    optable[0x78] = &op_78; cycle_table[0x78] = {1, 0};
    optable[0x79] = &op_79; cycle_table[0x79] = {1, 0};
    optable[0x7A] = &op_7A; cycle_table[0x7A] = {1, 0};
    optable[0x7B] = &op_7B; cycle_table[0x7B] = {1, 0};
    optable[0x7C] = &op_7C; cycle_table[0x7C] = {1, 0};
    optable[0x7D] = &op_7D; cycle_table[0x7D] = {1, 0};
    optable[0x7E] = &op_7E; cycle_table[0x7E] = {2, 0};
    optable[0x7F] = &op_7F; cycle_table[0x7F] = {1, 0};

    optable[0x80] = &op_80; cycle_table[0x80] = {1, 0};
    optable[0x81] = &op_81; cycle_table[0x81] = {1, 0};
    optable[0x82] = &op_82; cycle_table[0x82] = {1, 0};
    optable[0x83] = &op_83; cycle_table[0x83] = {1, 0};
    optable[0x84] = &op_84; cycle_table[0x84] = {1, 0};
    optable[0x85] = &op_85; cycle_table[0x85] = {1, 0};
    optable[0x86] = &op_86; cycle_table[0x86] = {2, 0};
    optable[0x87] = &op_87; cycle_table[0x87] = {1, 0};
    optable[0x88] = &op_88; cycle_table[0x88] = {1, 0};
    optable[0x89] = &op_89; cycle_table[0x89] = {1, 0};
    optable[0x8A] = &op_8A; cycle_table[0x8A] = {1, 0};
    optable[0x8B] = &op_8B; cycle_table[0x8B] = {1, 0};
    optable[0x8C] = &op_8C; cycle_table[0x8C] = {1, 0};
    optable[0x8D] = &op_8D; cycle_table[0x8D] = {1, 0};
    optable[0x8E] = &op_8E; cycle_table[0x8E] = {2, 0};
    optable[0x8F] = &op_8F; cycle_table[0x8F] = {1, 0};

    optable[0x90] = &op_90; cycle_table[0x90] = {1, 0};
    optable[0x91] = &op_91; cycle_table[0x91] = {1, 0};
    optable[0x92] = &op_92; cycle_table[0x92] = {1, 0};
    optable[0x93] = &op_93; cycle_table[0x93] = {1, 0};
    optable[0x94] = &op_94; cycle_table[0x94] = {1, 0};
    optable[0x95] = &op_95; cycle_table[0x95] = {1, 0};
    optable[0x96] = &op_96; cycle_table[0x96] = {2, 0};
    optable[0x97] = &op_97; cycle_table[0x97] = {1, 0};
    optable[0x98] = &op_98; cycle_table[0x98] = {1, 0};
    optable[0x99] = &op_99; cycle_table[0x99] = {1, 0};
    optable[0x9A] = &op_9A; cycle_table[0x9A] = {1, 0};
    optable[0x9B] = &op_9B; cycle_table[0x9B] = {1, 0};
    optable[0x9C] = &op_9C; cycle_table[0x9C] = {1, 0};
    optable[0x9D] = &op_9D; cycle_table[0x9D] = {1, 0};
    optable[0x9E] = &op_9E; cycle_table[0x9E] = {2, 0};
    optable[0x9F] = &op_9F; cycle_table[0x9F] = {1, 0};

    optable[0xA0] = &op_A0; cycle_table[0xA0] = {1, 0};
    optable[0xA1] = &op_A1; cycle_table[0xA1] = {1, 0};
    optable[0xA2] = &op_A2; cycle_table[0xA2] = {1, 0};
    optable[0xA3] = &op_A3; cycle_table[0xA3] = {1, 0};
    optable[0xA4] = &op_A4; cycle_table[0xA4] = {1, 0};
    optable[0xA5] = &op_A5; cycle_table[0xA5] = {1, 0};
    optable[0xA6] = &op_A6; cycle_table[0xA6] = {2, 0};
    optable[0xA7] = &op_A7; cycle_table[0xA7] = {1, 0};
    optable[0xA8] = &op_A8; cycle_table[0xA8] = {1, 0};
    optable[0xA9] = &op_A9; cycle_table[0xA9] = {1, 0};
    optable[0xAA] = &op_AA; cycle_table[0xAA] = {1, 0};
    optable[0xAB] = &op_AB; cycle_table[0xAB] = {1, 0};
    optable[0xAC] = &op_AC; cycle_table[0xAC] = {1, 0};
    optable[0xAD] = &op_AD; cycle_table[0xAD] = {1, 0};
    optable[0xAE] = &op_AE; cycle_table[0xAE] = {2, 0};
    optable[0xAF] = &op_AF; cycle_table[0xAF] = {1, 0};

    optable[0xB0] = &op_B0; cycle_table[0xB0] = {1, 0};
    optable[0xB1] = &op_B1; cycle_table[0xB1] = {1, 0};
    optable[0xB2] = &op_B2; cycle_table[0xB2] = {1, 0};
    optable[0xB3] = &op_B3; cycle_table[0xB3] = {1, 0};
    optable[0xB4] = &op_B4; cycle_table[0xB4] = {1, 0};
    optable[0xB5] = &op_B5; cycle_table[0xB5] = {1, 0};
    optable[0xB6] = &op_B6; cycle_table[0xB6] = {2, 0};
    optable[0xB7] = &op_B7; cycle_table[0xB7] = {1, 0};
    optable[0xB8] = &op_B8; cycle_table[0xB8] = {1, 0};
    optable[0xB9] = &op_B9; cycle_table[0xB9] = {1, 0};
    optable[0xBA] = &op_BA; cycle_table[0xBA] = {1, 0};
    optable[0xBB] = &op_BB; cycle_table[0xBB] = {1, 0};
    optable[0xBC] = &op_BC; cycle_table[0xBC] = {1, 0};
    optable[0xBD] = &op_BD; cycle_table[0xBD] = {1, 0};
    optable[0xBE] = &op_BE; cycle_table[0xBE] = {2, 0};
    optable[0xBF] = &op_BF; cycle_table[0xBF] = {1, 0};

    optable[0xC0] = &op_C0; cycle_table[0xC0] = {2, 3};
    optable[0xC1] = &op_C1; cycle_table[0xC1] = {3, 0};
    optable[0xC2] = &op_C2; cycle_table[0xC2] = {3, 1};
    optable[0xC3] = &op_C3; cycle_table[0xC3] = {4, 0};
    optable[0xC4] = &op_C4; cycle_table[0xC4] = {3, 3};
    optable[0xC5] = &op_C5; cycle_table[0xC5] = {4, 0};
    optable[0xC6] = &op_C6; cycle_table[0xC6] = {2, 0};
    optable[0xC7] = &op_C7; cycle_table[0xC7] = {4, 0};
    optable[0xC8] = &op_C8; cycle_table[0xC8] = {2, 3};
    optable[0xC9] = &op_C9; cycle_table[0xC9] = {4, 0};
    optable[0xCA] = &op_CA; cycle_table[0xCA] = {3, 1};
    optable[0xCC] = &op_CC; cycle_table[0xCC] = {3, 3};
    optable[0xCD] = &op_CD; cycle_table[0xCD] = {6, 0};
    optable[0xCE] = &op_CE; cycle_table[0xCE] = {2, 0};
    optable[0xCF] = &op_CF; cycle_table[0xCF] = {4, 0};

    optable[0xD0] = &op_D0; cycle_table[0xD0] = {2, 3};
    optable[0xD1] = &op_D1; cycle_table[0xD1] = {3, 0};
    optable[0xD2] = &op_D2; cycle_table[0xD2] = {3, 1};
    optable[0xD4] = &op_D4; cycle_table[0xD4] = {3, 3};
    optable[0xD5] = &op_D5; cycle_table[0xD5] = {4, 0};
    optable[0xD6] = &op_D6; cycle_table[0xD6] = {2, 0};
    optable[0xD7] = &op_D7; cycle_table[0xD7] = {4, 0};
    optable[0xD8] = &op_D8; cycle_table[0xD8] = {2, 3};
    optable[0xD9] = &op_D9; cycle_table[0xD9] = {4, 0};
    optable[0xDA] = &op_DA; cycle_table[0xDA] = {3, 1};
    optable[0xDC] = &op_DC; cycle_table[0xDC] = {3, 3};
    optable[0xDE] = &op_DE; cycle_table[0xDE] = {2, 0};
    optable[0xDF] = &op_DF; cycle_table[0xDF] = {4, 0};

    optable[0xE0] = &op_E0; cycle_table[0xE0] = {3, 0};
    optable[0xE1] = &op_E1; cycle_table[0xE1] = {3, 0};
    optable[0xE2] = &op_E2; cycle_table[0xE2] = {2, 0};
    optable[0xE5] = &op_E5; cycle_table[0xE5] = {4, 0};
    optable[0xE6] = &op_E6; cycle_table[0xE6] = {2, 0};
    optable[0xE7] = &op_E7; cycle_table[0xE7] = {4, 0};
    optable[0xE8] = &op_E8; cycle_table[0xE8] = {4, 0};
    optable[0xE9] = &op_E9; cycle_table[0xE9] = {1, 0};
    optable[0xEA] = &op_EA; cycle_table[0xEA] = {4, 0};
    optable[0xEE] = &op_EE; cycle_table[0xEE] = {2, 0};
    optable[0xEF] = &op_EF; cycle_table[0xEF] = {4, 0};

    optable[0xF0] = &op_F0; cycle_table[0xF0] = {3, 0};
    optable[0xF1] = &op_F1; cycle_table[0xF1] = {3, 0};
    optable[0xF2] = &op_F2; cycle_table[0xF2] = {2, 0};
    optable[0xF3] = &op_F3; cycle_table[0xF3] = {1, 0};
    optable[0xF5] = &op_F5; cycle_table[0xF5] = {4, 0};
    optable[0xF6] = &op_F6; cycle_table[0xF6] = {2, 0};
    optable[0xF7] = &op_F7; cycle_table[0xF7] = {4, 0};
    optable[0xF8] = &op_F8; cycle_table[0xF8] = {3, 0};
    optable[0xF9] = &op_F9; cycle_table[0xF9] = {2, 0};
    optable[0xFA] = &op_FA; cycle_table[0xFA] = {4, 0};
    optable[0xFB] = &op_FB; cycle_table[0xFB] = {1, 0};
    optable[0xFE] = &op_FE; cycle_table[0xFE] = {2, 0};
    optable[0xFF] = &op_FF; cycle_table[0xFF] = {4, 0};

    initialize_optable_cb();
    optable[0xCB] = &op_CB;
}

void initialize_optable_cb() {
    optable_cb[0x00] = &op_CB_00; cycle_table_cb[0x00] = {2, 0};
    optable_cb[0x01] = &op_CB_01; cycle_table_cb[0x01] = {2, 0};
    optable_cb[0x02] = &op_CB_02; cycle_table_cb[0x02] = {2, 0};
    optable_cb[0x03] = &op_CB_03; cycle_table_cb[0x03] = {2, 0};
    optable_cb[0x04] = &op_CB_04; cycle_table_cb[0x04] = {2, 0};
    optable_cb[0x05] = &op_CB_05; cycle_table_cb[0x05] = {2, 0};
    optable_cb[0x06] = &op_CB_06; cycle_table_cb[0x06] = {4, 0};
    optable_cb[0x07] = &op_CB_07; cycle_table_cb[0x07] = {2, 0};
    optable_cb[0x08] = &op_CB_08; cycle_table_cb[0x08] = {2, 0};
    optable_cb[0x09] = &op_CB_09; cycle_table_cb[0x09] = {2, 0};
    optable_cb[0x0a] = &op_CB_0A; cycle_table_cb[0x0a] = {2, 0};
    optable_cb[0x0b] = &op_CB_0B; cycle_table_cb[0x0b] = {2, 0};
    optable_cb[0x0c] = &op_CB_0C; cycle_table_cb[0x0c] = {2, 0};
    optable_cb[0x0d] = &op_CB_0D; cycle_table_cb[0x0d] = {2, 0};
    optable_cb[0x0e] = &op_CB_0E; cycle_table_cb[0x0e] = {4, 0};
    optable_cb[0x0f] = &op_CB_0F; cycle_table_cb[0x0f] = {2, 0};

    optable_cb[0x10] = &op_CB_10; cycle_table_cb[0x10] = {2, 0};
    optable_cb[0x11] = &op_CB_11; cycle_table_cb[0x11] = {2, 0};
    optable_cb[0x12] = &op_CB_12; cycle_table_cb[0x12] = {2, 0};
    optable_cb[0x13] = &op_CB_13; cycle_table_cb[0x13] = {2, 0};
    optable_cb[0x14] = &op_CB_14; cycle_table_cb[0x14] = {2, 0};
    optable_cb[0x15] = &op_CB_15; cycle_table_cb[0x15] = {2, 0};
    optable_cb[0x16] = &op_CB_16; cycle_table_cb[0x16] = {4, 0};
    optable_cb[0x17] = &op_CB_17; cycle_table_cb[0x17] = {2, 0};
    optable_cb[0x18] = &op_CB_18; cycle_table_cb[0x18] = {2, 0};
    optable_cb[0x19] = &op_CB_19; cycle_table_cb[0x19] = {2, 0};
    optable_cb[0x1A] = &op_CB_1A; cycle_table_cb[0x1A] = {2, 0};
    optable_cb[0x1B] = &op_CB_1B; cycle_table_cb[0x1B] = {2, 0};
    optable_cb[0x1C] = &op_CB_1C; cycle_table_cb[0x1C] = {2, 0};
    optable_cb[0x1D] = &op_CB_1D; cycle_table_cb[0x1D] = {2, 0};
    optable_cb[0x1E] = &op_CB_1E; cycle_table_cb[0x1E] = {4, 0};
    optable_cb[0x1F] = &op_CB_1F; cycle_table_cb[0x1F] = {2, 0};

    optable_cb[0x20] = &op_CB_20; cycle_table_cb[0x20] = {2, 0};
    optable_cb[0x21] = &op_CB_21; cycle_table_cb[0x21] = {2, 0};
    optable_cb[0x22] = &op_CB_22; cycle_table_cb[0x22] = {2, 0};
    optable_cb[0x23] = &op_CB_23; cycle_table_cb[0x23] = {2, 0};
    optable_cb[0x24] = &op_CB_24; cycle_table_cb[0x24] = {2, 0};
    optable_cb[0x25] = &op_CB_25; cycle_table_cb[0x25] = {2, 0};
    optable_cb[0x26] = &op_CB_26; cycle_table_cb[0x26] = {4, 0};
    optable_cb[0x27] = &op_CB_27; cycle_table_cb[0x27] = {2, 0};
    optable_cb[0x28] = &op_CB_28; cycle_table_cb[0x28] = {2, 0};
    optable_cb[0x29] = &op_CB_29; cycle_table_cb[0x29] = {2, 0};
    optable_cb[0x2A] = &op_CB_2A; cycle_table_cb[0x2A] = {2, 0};
    optable_cb[0x2B] = &op_CB_2B; cycle_table_cb[0x2B] = {2, 0};
    optable_cb[0x2C] = &op_CB_2C; cycle_table_cb[0x2C] = {2, 0};
    optable_cb[0x2D] = &op_CB_2D; cycle_table_cb[0x2D] = {2, 0};
    optable_cb[0x2E] = &op_CB_2E; cycle_table_cb[0x2E] = {4, 0};
    optable_cb[0x2F] = &op_CB_2F; cycle_table_cb[0x2F] = {2, 0};

    optable_cb[0x30] = &op_CB_30; cycle_table_cb[0x30] = {2, 0};
    optable_cb[0x31] = &op_CB_31; cycle_table_cb[0x31] = {2, 0};
    optable_cb[0x32] = &op_CB_32; cycle_table_cb[0x32] = {2, 0};
    optable_cb[0x33] = &op_CB_33; cycle_table_cb[0x33] = {2, 0};
    optable_cb[0x34] = &op_CB_34; cycle_table_cb[0x34] = {2, 0};
    optable_cb[0x35] = &op_CB_35; cycle_table_cb[0x35] = {2, 0};
    optable_cb[0x36] = &op_CB_36; cycle_table_cb[0x36] = {4, 0};
    optable_cb[0x37] = &op_CB_37; cycle_table_cb[0x37] = {2, 0};
    optable_cb[0x38] = &op_CB_38; cycle_table_cb[0x38] = {2, 0};
    optable_cb[0x39] = &op_CB_39; cycle_table_cb[0x39] = {2, 0};
    optable_cb[0x3A] = &op_CB_3A; cycle_table_cb[0x3A] = {2, 0};
    optable_cb[0x3B] = &op_CB_3B; cycle_table_cb[0x3B] = {2, 0};
    optable_cb[0x3C] = &op_CB_3C; cycle_table_cb[0x3C] = {2, 0};
    optable_cb[0x3D] = &op_CB_3D; cycle_table_cb[0x3D] = {2, 0};
    optable_cb[0x3E] = &op_CB_3E; cycle_table_cb[0x3E] = {4, 0};
    optable_cb[0x3F] = &op_CB_3F; cycle_table_cb[0x3F] = {2, 0};
}

void op_00(Mmu* mmu, Cpu* cp) {
    // NOP
    ;
};

void op_01(Mmu* mmu, Cpu* cp) {
    // LD BC, nn
    cp->reg_C = mmu->read_memory(++cp->pc);
    cp->reg_B = mmu->read_memory(++cp->pc);
};

void op_02(Mmu* mmu, Cpu* cp) {
    // LD (BC), A
    mmu->write_memory(cp->reg_BC.get(), cp->reg_A);
};

void op_03(Mmu* mmu, Cpu* cp) {
    // INC BC 
    cp->reg_BC++;
};

void op_04(Mmu* mmu, Cpu* cp) {
    // INC B
    cp->inc8(&cp->reg_B);
};

void op_05(Mmu* mmu, Cpu* cp) { 
    // DEC B
    cp->dec8(&cp->reg_B);
};

void op_06(Mmu* mmu, Cpu* cp) {
    // LD B, n
    cp->reg_B = mmu->read_memory(++cp->pc);
};

void op_07(Mmu* mmu, Cpu* cp) { 
    // RLCA
    cp->rlc8(&cp->reg_A);
    /*
        idk why but according to 2 emulators they set the z flag to false always
    */
   cp->set_z_flag(0); // FIXME: 
};

void op_08(Mmu* mmu, Cpu* cp) {
    // LD NN, SP
    word nn = mmu->read_memory(++cp->pc) | (mmu->read_memory(++cp->pc) << 8);
    mmu->write_memory(nn++, cp->sp & 0xFF);
    mmu->write_memory(nn, (cp->sp & 0xFF00) >> 8);
};

void op_09(Mmu* mmu, Cpu* cp) { 
    // ADD HL, BC
    cp->add16(&cp->reg_HL, cp->reg_BC.get());
};

void op_0A(Mmu* mmu, Cpu* cp) {
    // LD A, (BC)
    cp->reg_A = mmu->read_memory(cp->reg_BC.get());
};

void op_0B(Mmu* mmu, Cpu* cp) { 
    // DEC BC
    cp->reg_BC--;
};

void op_0C(Mmu* mmu, Cpu* cp) {
    // INC C 
    cp->inc8(&cp->reg_C);
};

void op_0D(Mmu* mmu, Cpu* cp) { 
    // DEC C
    cp->dec8(&cp->reg_C); 
};

void op_0E(Mmu* mmu, Cpu* cp) {
    // LD C, N
    cp->reg_C = mmu->read_memory(++cp->pc);
};

void op_0F(Mmu* mmu, Cpu* cp) { 
    // RRCA
    cp->rrc8(&cp->reg_A);
    cp->set_z_flag(0); // FIXME: same as op 07 
};

void op_10(Mmu* mmu, Cpu* cp) {
    // TODO: STOP
};

void op_11(Mmu* mmu, Cpu* cp) {
    // LD DE, NN
    cp->reg_E = mmu->read_memory(++cp->pc);
    cp->reg_D = mmu->read_memory(++cp->pc);
};

void op_12(Mmu* mmu, Cpu* cp) {
    // LD (DE), A
    mmu->write_memory(cp->reg_DE.get(), cp->reg_A);
};

void op_13(Mmu* mmu, Cpu* cp) {
    // INC DE 
    cp->reg_DE++; 
};

void op_14(Mmu* mmu, Cpu* cp) {
    // INC D 
    cp->inc8(&cp->reg_D); 
};

void op_15(Mmu* mmu, Cpu* cp) { 
    // DEC D
    cp->dec8(&cp->reg_D); 
};

void op_16(Mmu* mmu, Cpu* cp) {
    // LD D, N
    cp->reg_D = mmu->read_memory(++cp->pc);
};

void op_17(Mmu* mmu, Cpu* cp) {
    // RLCA 
    cp->rl8(&cp->reg_A);
    cp->set_z_flag(0); // FIXME: same as others 
};

void op_18(Mmu* mmu, Cpu* cp) { 
    // JR NN
    cp->pc += (char)mmu->read_memory(++cp->pc);
};

void op_19(Mmu* mmu, Cpu* cp) {
    // ADD HL, DE 
    cp->add16(&cp->reg_HL, cp->reg_DE.get()); 
};

void op_1A(Mmu* mmu, Cpu* cp) {
    // ADD (DE), A
    cp->reg_A = mmu->read_memory(cp->reg_DE.get());
};

void op_1B(Mmu* mmu, Cpu* cp) { 
    // DEC DE
    cp->reg_DE--;
};

void op_1C(Mmu* mmu, Cpu* cp) { 
    // INC E
    cp->inc8(&cp->reg_E); 
};

void op_1D(Mmu* mmu, Cpu* cp) { 
    // DEC 8
    cp->dec8(&cp->reg_E);
};

void op_1E(Mmu* mmu, Cpu* cp) {
    // LD E, N
    cp->reg_E = mmu->read_memory(++cp->pc);
};

void op_1F(Mmu* mmu, Cpu* cp) { 
    // RRA
    cp->rr8(&cp->reg_A); 
    cp->set_z_flag(0); // FIXME: same as others
};

void op_20(Mmu* mmu, Cpu* cp) {
    // JR NZ, NN
    cp->pc++;
    if (!cp->get_z_flag()) {
        cp->last_clock += cycle_table[0x20].conditional_cycles;
        cp->pc += (char)mmu->read_memory(cp->pc);
    }
};

void op_21(Mmu* mmu, Cpu* cp) {
    // LD HL, NN
    cp->reg_L = mmu->read_memory(++cp->pc);
    cp->reg_H = mmu->read_memory(++cp->pc);
};

void op_22(Mmu* mmu, Cpu* cp) {
    // LDI (HL), A
    mmu->write_memory(cp->reg_HL++, cp->reg_A);
};

void op_23(Mmu* mmu, Cpu* cp) { 
    // INC HL
    cp->reg_HL++; 
};

void op_24(Mmu* mmu, Cpu* cp) { 
    // INC H
    cp->inc8(&cp->reg_H); 
};

void op_25(Mmu* mmu, Cpu* cp) {
    // DEC H 
    cp->dec8(&cp->reg_H); 
};

void op_26(Mmu* mmu, Cpu* cp) {
    // LD H, N
    cp->reg_H = mmu->read_memory(++cp->pc);
};


void op_27(Mmu* mmu, Cpu* cp) {
    // DAA
    uint8_t a = cp->reg_A;
    bool n = cp->get_n_flag();
    bool h = cp->get_h_flag();
    bool c = cp->get_c_flag();
    uint8_t adjust = 0;
    bool set_c = false;

    if (!n) {
        if (h || (a & 0x0F) > 0x09)
            adjust |= 0x06;
        if (c || a > 0x99) {
            adjust |= 0x60;
            set_c = true;
        }
        a += adjust;
    } else {
        if (h) adjust |= 0x06;
        if (c) adjust |= 0x60;
        a -= adjust;
    }

    cp->reg_A = a;
    cp->set_z_flag(a == 0);
    cp->set_h_flag(0);
    if (set_c) cp->set_c_flag(1);
};

void op_28(Mmu* mmu, Cpu* cp) {
    // JR Z, N
    cp->pc++;
    if (cp->get_z_flag()) {
        cp->last_clock += cycle_table[0x28].conditional_cycles;
        cp->pc += (char)mmu->read_memory(cp->pc);
    }
};

void op_29(Mmu* mmu, Cpu* cp) { 
    // ADD HL, HL
    cp->add16(&cp->reg_HL, cp->reg_HL.get());
};

void op_2A(Mmu* mmu, Cpu* cp) {
    // LDI A, (HL)
    cp->reg_A = mmu->read_memory(cp->reg_HL++);
};

void op_2B(Mmu* mmu, Cpu* cp) { 
    // DEC HL
    cp->reg_HL--;
};

void op_2C(Mmu* mmu, Cpu* cp) { 
    // INC L
    cp->inc8(&cp->reg_L);
};

void op_2D(Mmu* mmu, Cpu* cp) { 
    // DEC L
    cp->dec8(&cp->reg_L);
};

void op_2E(Mmu* mmu, Cpu* cp) {
    // LD L, N
    cp->reg_L = mmu->read_memory(++cp->pc);
};

void op_2F(Mmu* mmu, Cpu* cp) {
    // CPL
    cp->set_n_flag(1);
    cp->set_h_flag(1);

    cp->reg_A ^= 0xFF;
};

void op_30(Mmu* mmu, Cpu* cp) {
    // JR NC, N
    cp->pc++;
    if (!cp->get_c_flag()) {
        cp->last_clock += cycle_table[0x30].conditional_cycles;
        cp->pc += (char)mmu->read_memory(cp->pc);
    }
};

void op_31(Mmu* mmu, Cpu* cp) {
    // LD SP, NN
    cp->sp = mmu->read_memory(++cp->pc) | (mmu->read_memory(++cp->pc) << 8);
};

void op_32(Mmu* mmu, Cpu* cp) {
    // LDD (HL), A
    mmu->write_memory(cp->reg_HL--, cp->reg_A);
};

void op_33(Mmu* mmu, Cpu* cp) {
    // INC SP
    cp->sp++;
};

void op_34(Mmu* mmu, Cpu* cp) {
    // INC (HL)
    word hl = cp->reg_HL.get();
    byte value =  mmu->read_memory(hl) + 1;
    mmu->write_memory(hl, value);

    cp->set_n_flag(0);
    cp->set_z_flag(value == 0);
    cp->set_h_flag(!(value & 0xF));
};

void op_35(Mmu* mmu, Cpu* cp) {
    // DEC (HL)
    word hl = cp->reg_HL.get();
    byte value = mmu->read_memory(hl) - 1;
    mmu->write_memory(hl, value);
    
    cp->set_n_flag(1);
    cp->set_z_flag(value == 0);
    cp->set_h_flag((value & 0x0F) == 0x0F);
};

void op_36(Mmu* mmu, Cpu* cp) {
    // LD (HL), N
    mmu->write_memory(cp->reg_HL.get(), mmu->read_memory(++cp->pc));
};

void op_37(Mmu* mmu, Cpu* cp) {
    // SCF
    cp->set_n_flag(0);
    cp->set_h_flag(0);
    cp->set_c_flag(1);
};

void op_38(Mmu* mmu, Cpu* cp) {
    // JR C, NN
    cp->pc++;
    if (cp->get_c_flag()) {
        cp->last_clock += cycle_table[0x38].conditional_cycles;
        cp->pc += (char)mmu->read_memory(cp->pc);
    }
};

void op_39(Mmu* mmu, Cpu* cp) { 
    // ADD HL, SP
    cp->add16(&cp->reg_HL, cp->sp); 
};

void op_3A(Mmu* mmu, Cpu* cp) {
    // LDD A, (HL)
    cp->reg_A = mmu->read_memory(cp->reg_HL--);
};

void op_3B(Mmu* mmu, Cpu* cp) { 
    // DEC SP
    cp->sp--; 
};

void op_3C(Mmu* mmu, Cpu* cp) { 
    // INC A
    cp->inc8(&cp->reg_A); 
};

void op_3D(Mmu* mmu, Cpu* cp) { 
    // DEC A
    cp->dec8(&cp->reg_A); 
};

void op_3E(Mmu* mmu, Cpu* cp) {
    // LD A, N
    cp->reg_A = mmu->read_memory(++cp->pc);
};

void op_3F(Mmu* mmu, Cpu* cp) {
    // CCF
    cp->set_n_flag(0);
    cp->set_h_flag(0);
    cp->set_c_flag(!(cp->get_c_flag()));
};

void op_40(Mmu* mmu, Cpu* cp) { 
    // LD B, B
    cp->reg_B = cp->reg_B; 
};

void op_41(Mmu* mmu, Cpu* cp) {
    // LD B, C 
    cp->reg_B = cp->reg_C; 
};

void op_42(Mmu* mmu, Cpu* cp) { 
    // LD B, D
    cp->reg_B = cp->reg_D; 
};

void op_43(Mmu* mmu, Cpu* cp) { 
    // LD B, E
    cp->reg_B = cp->reg_E; 
};

void op_44(Mmu* mmu, Cpu* cp) { 
    // LD B, H
    cp->reg_B = cp->reg_H; 
};

void op_45(Mmu* mmu, Cpu* cp) { 
    // LD B, L
    cp->reg_B = cp->reg_L; 
};

void op_46(Mmu* mmu, Cpu* cp) {
    // LD B, (HL)
    cp->reg_B = mmu->read_memory(cp->reg_HL.get());
};

void op_47(Mmu* mmu, Cpu* cp) {
    // LD B, A 
    cp->reg_B = cp->reg_A; 
};

void op_48(Mmu* mmu, Cpu* cp) { 
    cp->reg_C = cp->reg_B; 
};

void op_49(Mmu* mmu, Cpu* cp) { 
    cp->reg_C = cp->reg_C; 
};

void op_4A(Mmu* mmu, Cpu* cp) { 
    cp->reg_C = cp->reg_D; 
};

void op_4B(Mmu* mmu, Cpu* cp) { 
    cp->reg_C = cp->reg_E; 
};

void op_4C(Mmu* mmu, Cpu* cp) { 
    cp->reg_C = cp->reg_H; 
};

void op_4D(Mmu* mmu, Cpu* cp) { 
    cp->reg_C = cp->reg_L; 
};

void op_4E(Mmu* mmu, Cpu* cp) {
    cp->reg_C = mmu->read_memory(cp->reg_HL.get());
};

void op_4F(Mmu* mmu, Cpu* cp) { 
    cp->reg_C = cp->reg_A; 
};

void op_50(Mmu* mmu, Cpu* cp) { 
    cp->reg_D = cp->reg_B; 
};

void op_51(Mmu* mmu, Cpu* cp) { 
    cp->reg_D = cp->reg_C; 
};

void op_52(Mmu* mmu, Cpu* cp) { 
    cp->reg_D = cp->reg_D; 
};

void op_53(Mmu* mmu, Cpu* cp) {
    cp->reg_D = cp->reg_E; 
};

void op_54(Mmu* mmu, Cpu* cp) { 
    cp->reg_D = cp->reg_H; 
};

void op_55(Mmu* mmu, Cpu* cp) { 
    cp->reg_D = cp->reg_L; 
};

void op_56(Mmu* mmu, Cpu* cp) {
    cp->reg_D = mmu->read_memory(cp->reg_HL.get());
};

void op_57(Mmu* mmu, Cpu* cp) { 
    cp->reg_D = cp->reg_A; 
};

void op_58(Mmu* mmu, Cpu* cp) { 
    cp->reg_E = cp->reg_B; 
};

void op_59(Mmu* mmu, Cpu* cp) { 
    cp->reg_E = cp->reg_C; 
};

void op_5A(Mmu* mmu, Cpu* cp) { 
    cp->reg_E = cp->reg_D; 
};

void op_5B(Mmu* mmu, Cpu* cp) { 
    cp->reg_E = cp->reg_E; 
};

void op_5C(Mmu* mmu, Cpu* cp) { 
    cp->reg_E = cp->reg_H; 
};

void op_5D(Mmu* mmu, Cpu* cp) { 
    cp->reg_E = cp->reg_L; 
};

void op_5E(Mmu* mmu, Cpu* cp) {
    cp->reg_E = mmu->read_memory(cp->reg_HL.get());
};

void op_5F(Mmu* mmu, Cpu* cp) { 
    cp->reg_E = cp->reg_A; 
};

void op_60(Mmu* mmu, Cpu* cp) { 
    cp->reg_H = cp->reg_B; 
};

void op_61(Mmu* mmu, Cpu* cp) { 
    cp->reg_H = cp->reg_C; 
};

void op_62(Mmu* mmu, Cpu* cp) { 
    cp->reg_H = cp->reg_D; 
};

void op_63(Mmu* mmu, Cpu* cp) { 
    cp->reg_H = cp->reg_E; 
};

void op_64(Mmu* mmu, Cpu* cp) { 
    cp->reg_H = cp->reg_H; 
};

void op_65(Mmu* mmu, Cpu* cp) { 
    cp->reg_H = cp->reg_L; 
};

void op_66(Mmu* mmu, Cpu* cp) {
    cp->reg_H = mmu->read_memory(cp->reg_HL.get());
};

void op_67(Mmu* mmu, Cpu* cp) { 
    cp->reg_H = cp->reg_A; 
};

void op_68(Mmu* mmu, Cpu* cp) { 
    cp->reg_L = cp->reg_B; 
};

void op_69(Mmu* mmu, Cpu* cp) { 
    cp->reg_L = cp->reg_C; 
};

void op_6A(Mmu* mmu, Cpu* cp) { 
    cp->reg_L = cp->reg_D; 
};

void op_6B(Mmu* mmu, Cpu* cp) { 
    cp->reg_L = cp->reg_E; 
};

void op_6C(Mmu* mmu, Cpu* cp) { 
    cp->reg_L = cp->reg_H; 
};

void op_6D(Mmu* mmu, Cpu* cp) { 
    cp->reg_L = cp->reg_L; 
};

void op_6E(Mmu* mmu, Cpu* cp) {
    cp->reg_L = mmu->read_memory(cp->reg_HL.get());
};

void op_6F(Mmu* mmu, Cpu* cp) { 
    cp->reg_L = cp->reg_A; 
};

void op_70(Mmu* mmu, Cpu* cp) {
    mmu->write_memory(cp->reg_HL.get(), cp->reg_B);
};

void op_71(Mmu* mmu, Cpu* cp) {
    mmu->write_memory(cp->reg_HL.get(), cp->reg_C);
};

void op_72(Mmu* mmu, Cpu* cp) {
    mmu->write_memory(cp->reg_HL.get(), cp->reg_D);
};

void op_73(Mmu* mmu, Cpu* cp) {
    mmu->write_memory(cp->reg_HL.get(), cp->reg_E);
};

void op_74(Mmu* mmu, Cpu* cp) {
    mmu->write_memory(cp->reg_HL.get(), cp->reg_H);
};

void op_75(Mmu* mmu, Cpu* cp) {
    mmu->write_memory(cp->reg_HL.get(), cp->reg_L);
};

void op_76(Mmu* mmu, Cpu* cp) {
    cp->halted = true;
};

void op_77(Mmu* mmu, Cpu* cp) {
    mmu->write_memory(cp->reg_HL.get(), cp->reg_A);
};

void op_78(Mmu* mmu, Cpu* cp) { 
    cp->reg_A = cp->reg_B; 
};

void op_79(Mmu* mmu, Cpu* cp) { 
    cp->reg_A = cp->reg_C; 
};

void op_7A(Mmu* mmu, Cpu* cp) { 
    cp->reg_A = cp->reg_D; 
};

void op_7B(Mmu* mmu, Cpu* cp) { 
    cp->reg_A = cp->reg_E; 
};

void op_7C(Mmu* mmu, Cpu* cp) { 
    cp->reg_A = cp->reg_H; 
};

void op_7D(Mmu* mmu, Cpu* cp) { 
    cp->reg_A = cp->reg_L; 
};

void op_7E(Mmu* mmu, Cpu* cp) {
    cp->reg_A = mmu->read_memory(cp->reg_HL.get());
};

void op_7F(Mmu* mmu, Cpu* cp) { 
    cp->reg_A = cp->reg_A;
};

void op_80(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, cp->reg_B);
};

void op_81(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, cp->reg_C);
};

void op_82(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, cp->reg_D);
};

void op_83(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, cp->reg_E);
};

void op_84(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, cp->reg_H);
};

void op_85(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, cp->reg_L);
};

void op_86(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, mmu->read_memory(cp->reg_HL.get()));
};

void op_87(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, cp->reg_A);
};

void op_88(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, cp->reg_B + cp->get_c_flag());
};

void op_89(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, cp->reg_C + cp->get_c_flag());
};

void op_8A(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, cp->reg_D + cp->get_c_flag());
};

void op_8B(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, cp->reg_E + cp->get_c_flag());
};

void op_8C(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, cp->reg_H + cp->get_c_flag());
};

void op_8D(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, cp->reg_L + cp->get_c_flag());
};

void op_8E(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, mmu->read_memory(cp->reg_HL.get()) + cp->get_c_flag());
};

void op_8F(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, cp->reg_A + cp->get_c_flag());
};

void op_90(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, cp->reg_B);
};

void op_91(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, cp->reg_C);
};

void op_92(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, cp->reg_D);
};

void op_93(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, cp->reg_E);
};

void op_94(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, cp->reg_H);
};

void op_95(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, cp->reg_L);
};

void op_96(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, mmu->read_memory(cp->reg_HL.get()));
};

void op_97(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, cp->reg_A);
};

void op_98(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, cp->reg_B + cp->get_c_flag());
};

void op_99(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, cp->reg_C + cp->get_c_flag());
};

void op_9A(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, cp->reg_D + cp->get_c_flag());
};

void op_9B(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, cp->reg_E + cp->get_c_flag());
};

void op_9C(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, cp->reg_H + cp->get_c_flag());
};

void op_9D(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, cp->reg_L + cp->get_c_flag());
};

void op_9E(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, mmu->read_memory(cp->reg_HL.get()) + cp->get_c_flag());
};

void op_9F(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, cp->reg_A + cp->get_c_flag());
};

void op_A0(Mmu* mmu, Cpu* cp) {
    cp->and8(&cp->reg_A, cp->reg_B);
};

void op_A1(Mmu* mmu, Cpu* cp) {
    cp->and8(&cp->reg_A, cp->reg_C);
};

void op_A2(Mmu* mmu, Cpu* cp) {
    cp->and8(&cp->reg_A, cp->reg_D);
};

void op_A3(Mmu* mmu, Cpu* cp) {
    cp->and8(&cp->reg_A, cp->reg_E);
};

void op_A4(Mmu* mmu, Cpu* cp) {
    cp->and8(&cp->reg_A, cp->reg_H);
};

void op_A5(Mmu* mmu, Cpu* cp) {
    cp->and8(&cp->reg_A, cp->reg_L);
};

void op_A6(Mmu* mmu, Cpu* cp) {
    cp->and8(&cp->reg_A, mmu->read_memory(cp->reg_HL.get()));
};

void op_A7(Mmu* mmu, Cpu* cp) {
    cp->and8(&cp->reg_A, cp->reg_A);
};

void op_A8(Mmu* mmu, Cpu* cp) {
    cp->xor8(&cp->reg_A, cp->reg_B);
};

void op_A9(Mmu* mmu, Cpu* cp) {
    cp->xor8(&cp->reg_A, cp->reg_C);
};

void op_AA(Mmu* mmu, Cpu* cp) {
    cp->xor8(&cp->reg_A, cp->reg_D);
};

void op_AB(Mmu* mmu, Cpu* cp) {
    cp->xor8(&cp->reg_A, cp->reg_E);
};

void op_AC(Mmu* mmu, Cpu* cp) {
    cp->xor8(&cp->reg_A, cp->reg_H);
};

void op_AD(Mmu* mmu, Cpu* cp) {
    cp->xor8(&cp->reg_A, cp->reg_L);
};

void op_AE(Mmu* mmu, Cpu* cp) {
    cp->xor8(&cp->reg_A, mmu->read_memory(cp->reg_HL.get()));
};

void op_AF(Mmu* mmu, Cpu* cp) {
    cp->xor8(&cp->reg_A, cp->reg_A);
};

void op_B0(Mmu* mmu, Cpu* cp) {
    cp->or8(&cp->reg_A, cp->reg_B);
};

void op_B1(Mmu* mmu, Cpu* cp) {
    cp->or8(&cp->reg_A, cp->reg_C);
};

void op_B2(Mmu* mmu, Cpu* cp) {
    cp->or8(&cp->reg_A, cp->reg_D);
};

void op_B3(Mmu* mmu, Cpu* cp) {
    cp->or8(&cp->reg_A, cp->reg_E);
};

void op_B4(Mmu* mmu, Cpu* cp) {
    cp->or8(&cp->reg_A, cp->reg_H);
};

void op_B5(Mmu* mmu, Cpu* cp) {
    cp->or8(&cp->reg_A, cp->reg_L);
};

void op_B6(Mmu* mmu, Cpu* cp) {
    cp->or8(&cp->reg_A, mmu->read_memory(cp->reg_HL.get()));
};

void op_B7(Mmu* mmu, Cpu* cp) {
    cp->or8(&cp->reg_A, cp->reg_A);
};

void op_B8(Mmu* mmu, Cpu* cp) {
    cp->cp8(&cp->reg_A, cp->reg_B);
};

void op_B9(Mmu* mmu, Cpu* cp) {
    cp->cp8(&cp->reg_A, cp->reg_C);
};

void op_BA(Mmu* mmu, Cpu* cp) {
    cp->cp8(&cp->reg_A, cp->reg_D);
};

void op_BB(Mmu* mmu, Cpu* cp) {
    cp->cp8(&cp->reg_A, cp->reg_E);
};

void op_BC(Mmu* mmu, Cpu* cp) {
    cp->cp8(&cp->reg_A, cp->reg_H);
};

void op_BD(Mmu* mmu, Cpu* cp) {
    cp->cp8(&cp->reg_A, cp->reg_L);
};

void op_BE(Mmu* mmu, Cpu* cp) {
    cp->cp8(&cp->reg_A, mmu->read_memory(cp->reg_HL.get()));
};

void op_BF(Mmu* mmu, Cpu* cp) {
    cp->cp8(&cp->reg_A, cp->reg_A);
};

void op_C0(Mmu* mmu, Cpu* cp) {
    // RET NZ
    if (!cp->get_z_flag()) {
        cp->last_clock += cycle_table[0xC0].conditional_cycles;
        cp->ret();
    }
};

void op_C1(Mmu* mmu, Cpu* cp) {
    cp->pop16(&cp->reg_BC);
};

void op_C2(Mmu* mmu, Cpu* cp) {
    word nn = mmu->read_memory(++cp->pc) | (mmu->read_memory(++cp->pc) << 8);
    if (!cp->get_z_flag()) {
        cp->last_clock += cycle_table[0xC2].conditional_cycles;
        cp->pc = nn - 1;
    }
};

void op_C3(Mmu* mmu, Cpu* cp) {
    cp->pc = (mmu->read_memory(++cp->pc) | (mmu->read_memory(++cp->pc) << 8)) - 1;
}

void op_C4(Mmu* mmu, Cpu* cp) {
    word nn = mmu->read_memory(++cp->pc) | (mmu->read_memory(++cp->pc) << 8);

    if (!cp->get_z_flag()) {
        cp->last_clock += cycle_table[0xC4].conditional_cycles;
        cp->store_pc_stack();
        cp->pc = nn - 1;
    }
};

void op_C5(Mmu* mmu, Cpu* cp) { 
    cp->push16(&cp->reg_BC); 
};

void op_C6(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, mmu->read_memory(++cp->pc));
};

void op_C7(Mmu* mmu, Cpu* cp) {
    cp->store_pc_stack();
    cp->pc = 0x00 - 1;
};

void op_C8(Mmu* mmu, Cpu* cp) {
    if (cp->get_z_flag()) {
        cp->last_clock += cycle_table[0xC8].conditional_cycles;
        cp->ret();
    }
};

void op_C9(Mmu* mmu, Cpu* cp) { 
    cp->ret(); 
};

void op_CA(Mmu* mmu, Cpu* cp) {
    word nn = mmu->read_memory(++cp->pc) | (mmu->read_memory(++cp->pc) << 8);

    if (cp->get_z_flag()) {
        cp->last_clock += cycle_table[0xCA].conditional_cycles;
        cp->pc = nn - 1;
    }
};

void op_CC(Mmu* mmu, Cpu* cp) {
    word nn = mmu->read_memory(++cp->pc) | (mmu->read_memory(++cp->pc) << 8);

    if (cp->get_z_flag()) {
        cp->last_clock += cycle_table[0xCC].conditional_cycles;
        cp->store_pc_stack();
        cp->pc = nn - 1;
    }
}

void op_CD(Mmu* mmu, Cpu* cp) {
    word nn = mmu->read_memory(++cp->pc) | (mmu->read_memory(++cp->pc) << 8);
    cp->store_pc_stack();
    cp->pc = nn - 1;
};

void op_CE(Mmu* mmu, Cpu* cp) {
    cp->add8(&cp->reg_A, mmu->read_memory(++cp->pc) + cp->get_c_flag());
}

void op_CF(Mmu* mmu, Cpu* cp) {
    cp->store_pc_stack();
    cp->pc = 0x08 - 1;
};

void op_D0(Mmu* mmu, Cpu* cp) {
    if (!cp->get_c_flag()) {
        cp->last_clock += cycle_table[0xD0].conditional_cycles;
        cp->ret();
    }
};

void op_D1(Mmu* mmu, Cpu* cp) { 
    cp->pop16(&cp->reg_DE); 
};

void op_D2(Mmu* mmu, Cpu* cp) {
    word nn = mmu->read_memory(++cp->pc) | (mmu->read_memory(++cp->pc) << 8);
    if (!cp->get_c_flag()) {
        cp->last_clock += cycle_table[0xD2].conditional_cycles;
        cp->pc = nn - 1;
    }
};

void op_D4(Mmu* mmu, Cpu* cp) {
    word nn = mmu->read_memory(++cp->pc) | (mmu->read_memory(++cp->pc) << 8);

    if (!cp->get_c_flag()) {
        cp->last_clock += cycle_table[0xD4].conditional_cycles;
        cp->store_pc_stack();
        cp->pc = nn - 1;
    }
};

void op_D5(Mmu* mmu, Cpu* cp) { 
    cp->push16(&cp->reg_DE); 
};

void op_D6(Mmu* mmu, Cpu* cp) {
    cp->sub8(&cp->reg_A, mmu->read_memory(++cp->pc));
};

void op_D7(Mmu* mmu, Cpu* cp) {
    cp->store_pc_stack();
    cp->pc = 0x10 - 1;
};

void op_D8(Mmu* mmu, Cpu* cp) {
    if (cp->get_c_flag()) {
        cp->last_clock += cycle_table[0xD8].conditional_cycles;
        cp->ret();
    }
};

void op_D9(Mmu* mmu, Cpu* cp) {
    cp->ret();
    cp->interrupt_master = true;
};

void op_DA(Mmu* mmu, Cpu* cp) {
    word nn = mmu->read_memory(++cp->pc) | (mmu->read_memory(++cp->pc) << 8);
    if (cp->get_c_flag()) {
        cp->last_clock += cycle_table[0xDA].conditional_cycles;
        cp->pc = nn - 1;
    }
};
    
void op_DC(Mmu* mmu, Cpu* cp) {
    word nn = mmu->read_memory(++cp->pc) | (mmu->read_memory(++cp->pc) << 8);

    if (cp->get_c_flag()) {
        cp->last_clock += cycle_table[0xDC].conditional_cycles;
        cp->store_pc_stack();
        cp->pc = nn - 1;
    }
};

void op_DE(Mmu* mmu, Cpu* cp) {
    // SBC N
    cp->sub8(&cp->reg_A, mmu->read_memory(++cp->pc) + cp->get_c_flag());
};

void op_DF(Mmu* mmu, Cpu* cp) {
    cp->store_pc_stack();
    cp->pc = 0x18 - 1;
};

void op_E0(Mmu* mmu, Cpu* cp) {
    mmu->write_memory(0xFF00 + mmu->read_memory(++cp->pc), cp->reg_A);
};

void op_E1(Mmu* mmu, Cpu* cp) { 
    cp->pop16(&cp->reg_HL); 
};

void op_E2(Mmu* mmu, Cpu* cp) {
    mmu->write_memory(0xFF00 + cp->reg_C, cp->reg_A);
};

void op_E5(Mmu* mmu, Cpu* cp) { 
    cp->push16(&cp->reg_HL); 
};

void op_E6(Mmu* mmu, Cpu* cp) {
    cp->and8(&cp->reg_A, mmu->read_memory(++cp->pc));
};

void op_E7(Mmu* mmu, Cpu* cp) {
    cp->store_pc_stack();
    cp->pc = 0x20 - 1;
};

void op_E8(Mmu* mmu, Cpu* cp) {
    char n = mmu->read_memory(++cp->pc);
    word spn = cp->sp + n;

    cp->set_z_flag(0);
    cp->set_n_flag(0);
    cp->set_h_flag((spn & 0xF) < (cp->sp & 0xF));
    cp->set_c_flag((spn & 0xFF) < (cp->sp & 0xFF));

    cp->sp = spn;
};

void op_E9(Mmu* mmu, Cpu* cp) {
    cp->pc = cp->reg_HL.get() - 1;
};

void op_EA(Mmu* mmu, Cpu* cp) {
    mmu->write_memory(mmu->read_memory(++cp->pc) | (mmu->read_memory(++cp->pc) << 8), cp->reg_A);
};

void op_EE(Mmu* mmu, Cpu* cp) {
    cp->xor8(&cp->reg_A, mmu->read_memory(++cp->pc));
};

void op_EF(Mmu* mmu, Cpu* cp) {
    cp->store_pc_stack();
    cp->pc = 0x28 - 1;
};

void op_F0(Mmu* mmu, Cpu* cp) {
    cp->reg_A = mmu->read_memory(0xFF00 + mmu->read_memory(++cp->pc));
};

void op_F1(Mmu* mmu, Cpu* cp) { 
    cp->pop16(&cp->reg_AF); 
    cp->reg_F &= 0xF0;  // F lowest nibble does not matter
};

void op_F2(Mmu* mmu, Cpu* cp) {
    cp->reg_A = mmu->read_memory(0xFF00 + cp->reg_C);
};

void op_F3(Mmu* mmu, Cpu* cp) { 
    cp->pending_interrupt_disabled = true; 
};

void op_F5(Mmu* mmu, Cpu* cp) { 
    cp->push16(&cp->reg_AF); 
};

void op_F6(Mmu* mmu, Cpu* cp) {
    cp->or8(&cp->reg_A, mmu->read_memory(++cp->pc));
};

void op_F7(Mmu* mmu, Cpu* cp) {
    cp->store_pc_stack();
    cp->pc = 0x30 - 1;
};

void op_F8(Mmu* mmu, Cpu* cp) {
    // https://stackoverflow.com/questions/57958631/game-boy-half-carry-flag-and-16-bit-instructions-especially-opcode-0xe8
    char n = mmu->read_memory(++cp->pc);
    word spn = cp->sp + n;
    cp->reg_HL.set(spn);

    cp->set_z_flag(0);
    cp->set_n_flag(0);
    cp->set_h_flag((spn & 0xF) < (cp->sp & 0xF));
    cp->set_c_flag((spn & 0xFF) < (cp->sp & 0xFF));
};

void op_F9(Mmu* mmu, Cpu* cp) {
    cp->sp = cp->reg_HL.get();
};

void op_FA(Mmu* mmu, Cpu* cp) {
    cp->reg_A = mmu->read_memory(mmu->read_memory(++cp->pc) | (mmu->read_memory(++cp->pc) << 8));
};

void op_FB(Mmu* mmu, Cpu* cp) { 
    cp->pending_interrupt_enabled = true; 
};

void op_FE(Mmu* mmu, Cpu* cp) {
    cp->cp8(&cp->reg_A, mmu->read_memory(++cp->pc));
};

void op_FF(Mmu* mmu, Cpu* cp) {
    cp->store_pc_stack();
    cp->pc = 0x38 - 1;
};

void op_CB(Mmu* mmu, Cpu* cp) {
    int opcode = mmu->address[++cp->pc];

    byte reg = opcode & 0x07;
    byte bit = (opcode & 0x38) >> 3;
    cp->last_clock = 3;		//CB takes 1 cycle and the others take 2 cycles
                            //unless it is a 16 bit operation in which the
                            // cycles are incremented in the functions
    byte *preg; 

    switch (reg) {
        case 0: preg = &cp->reg_B; break;
        case 1: preg = &cp->reg_C; break;
        case 2: preg = &cp->reg_D; break;
        case 3: preg = &cp->reg_E; break;
        case 4: preg = &cp->reg_H; break;
        case 5: preg = &cp->reg_L; break;
        default: preg = &cp->reg_A; break;
    }

    if (opcode >= 0xC0) {
        if (preg) cp->set(preg, bit); else cp->set(&cp->reg_HL, bit);
    } else if (opcode < 0xC0 && opcode >= 0x80) {
        if (preg) cp->res(preg, bit); else cp->res(&cp->reg_HL, bit);
    } else if (opcode < 0x80 && opcode >= 0x40) {
        if (preg) cp->bit(preg, bit); else cp->bit(&cp->reg_HL, bit);
    } else {
        (*optable_cb[opcode])(mmu, cp);
        cp->last_clock = cycle_table_cb[opcode].cycles + 1;
    }
};

void op_CB_00(Mmu* mmu, Cpu* cp) { 
    cp->rlc8(&cp->reg_B); 
};

void op_CB_01(Mmu* mmu, Cpu* cp) { 
    cp->rlc8(&cp->reg_C); 
};

void op_CB_02(Mmu* mmu, Cpu* cp) { 
    cp->rlc8(&cp->reg_D); 
};

void op_CB_03(Mmu* mmu, Cpu* cp) { 
    cp->rlc8(&cp->reg_E);
};

void op_CB_04(Mmu* mmu, Cpu* cp) { 
    cp->rlc8(&cp->reg_H);
};

void op_CB_05(Mmu* mmu, Cpu* cp) { 
    cp->rlc8(&cp->reg_L);
};

void op_CB_06(Mmu* mmu, Cpu* cp) { 
    cp->rlc16(&cp->reg_HL);
};

void op_CB_07(Mmu* mmu, Cpu* cp) { 
    cp->rlc8(&cp->reg_A);
};

void op_CB_08(Mmu* mmu, Cpu* cp) { 
    cp->rrc8(&cp->reg_B);
};

void op_CB_09(Mmu* mmu, Cpu* cp) { 
    cp->rrc8(&cp->reg_C);
};

void op_CB_0A(Mmu* mmu, Cpu* cp) { 
    cp->rrc8(&cp->reg_D);
};

void op_CB_0B(Mmu* mmu, Cpu* cp) { 
    cp->rrc8(&cp->reg_E);
};

void op_CB_0C(Mmu* mmu, Cpu* cp) { 
    cp->rrc8(&cp->reg_H);
};

void op_CB_0D(Mmu* mmu, Cpu* cp) { 
    cp->rrc8(&cp->reg_L);
};

void op_CB_0E(Mmu* mmu, Cpu* cp) { 
    cp->rrc16(&cp->reg_HL);
};

void op_CB_0F(Mmu* mmu, Cpu* cp) { 
    cp->rrc8(&cp->reg_A);
};

void op_CB_10(Mmu* mmu, Cpu* cp) { 
    cp->rl8(&cp->reg_B);
};

void op_CB_11(Mmu* mmu, Cpu* cp) { 
    cp->rl8(&cp->reg_C);
};

void op_CB_12(Mmu* mmu, Cpu* cp) { 
    cp->rl8(&cp->reg_D);
};

void op_CB_13(Mmu* mmu, Cpu* cp) { 
    cp->rl8(&cp->reg_E);
};

void op_CB_14(Mmu* mmu, Cpu* cp) { 
    cp->rl8(&cp->reg_H);
};

void op_CB_15(Mmu* mmu, Cpu* cp) { 
    cp->rl8(&cp->reg_L);
};

void op_CB_16(Mmu* mmu, Cpu* cp) { 
    cp->rl16(&cp->reg_HL);
};

void op_CB_17(Mmu* mmu, Cpu* cp) { 
    cp->rl8(&cp->reg_A);
};

void op_CB_18(Mmu* mmu, Cpu* cp) { 
    cp->rr8(&cp->reg_B);
};

void op_CB_19(Mmu* mmu, Cpu* cp) { 
    cp->rr8(&cp->reg_C);
};

void op_CB_1A(Mmu* mmu, Cpu* cp) { 
    cp->rr8(&cp->reg_D);
};

void op_CB_1B(Mmu* mmu, Cpu* cp) { 
    cp->rr8(&cp->reg_E);
};

void op_CB_1C(Mmu* mmu, Cpu* cp) { 
    cp->rr8(&cp->reg_H);
};

void op_CB_1D(Mmu* mmu, Cpu* cp) { 
    cp->rr8(&cp->reg_L);
};

void op_CB_1E(Mmu* mmu, Cpu* cp) { 
    cp->rr16(&cp->reg_HL);
};

void op_CB_1F(Mmu* mmu, Cpu* cp) { 
    cp->rr8(&cp->reg_A);
};

void op_CB_20(Mmu* mmu, Cpu* cp) { 
    cp->sla8(&cp->reg_B);
};

void op_CB_21(Mmu* mmu, Cpu* cp) { 
    cp->sla8(&cp->reg_C);
};

void op_CB_22(Mmu* mmu, Cpu* cp) { 
    cp->sla8(&cp->reg_D);
};

void op_CB_23(Mmu* mmu, Cpu* cp) { 
    cp->sla8(&cp->reg_E);
};

void op_CB_24(Mmu* mmu, Cpu* cp) { 
    cp->sla8(&cp->reg_H);
};

void op_CB_25(Mmu* mmu, Cpu* cp) { 
    cp->sla8(&cp->reg_L);
};

void op_CB_26(Mmu* mmu, Cpu* cp) { 
    cp->sla16(&cp->reg_HL);
};

void op_CB_27(Mmu* mmu, Cpu* cp) { 
    cp->sla8(&cp->reg_A);
};

void op_CB_28(Mmu* mmu, Cpu* cp) { 
    cp->sra8(&cp->reg_B);
};

void op_CB_29(Mmu* mmu, Cpu* cp) { 
    cp->sra8(&cp->reg_C);
};

void op_CB_2A(Mmu* mmu, Cpu* cp) { 
    cp->sra8(&cp->reg_D);
};

void op_CB_2B(Mmu* mmu, Cpu* cp) { 
    cp->sra8(&cp->reg_E);
};

void op_CB_2C(Mmu* mmu, Cpu* cp) { 
    cp->sra8(&cp->reg_H);
};

void op_CB_2D(Mmu* mmu, Cpu* cp) { 
    cp->sra8(&cp->reg_L);
};

void op_CB_2E(Mmu* mmu, Cpu* cp) { 
    cp->sra16(&cp->reg_HL);
};

void op_CB_2F(Mmu* mmu, Cpu* cp) { 
    cp->sra8(&cp->reg_A);
};

void op_CB_30(Mmu* mmu, Cpu* cp) { 
    cp->swap8(&cp->reg_B);
};

void op_CB_31(Mmu* mmu, Cpu* cp) { 
    cp->swap8(&cp->reg_C);
};

void op_CB_32(Mmu* mmu, Cpu* cp) { 
    cp->swap8(&cp->reg_D);
};

void op_CB_33(Mmu* mmu, Cpu* cp) { 
    cp->swap8(&cp->reg_E);
};

void op_CB_34(Mmu* mmu, Cpu* cp) { 
    cp->swap8(&cp->reg_H);
};

void op_CB_35(Mmu* mmu, Cpu* cp) { 
    cp->swap8(&cp->reg_L);
};

void op_CB_36(Mmu* mmu, Cpu* cp) { 
    cp->swap16(&cp->reg_HL);
};

void op_CB_37(Mmu* mmu, Cpu* cp) { 
    cp->swap8(&cp->reg_A);
};

void op_CB_38(Mmu* mmu, Cpu* cp) { 
    cp->srl8(&cp->reg_B);
};

void op_CB_39(Mmu* mmu, Cpu* cp) { 
    cp->srl8(&cp->reg_C);
};

void op_CB_3A(Mmu* mmu, Cpu* cp) { 
    cp->srl8(&cp->reg_D);
};

void op_CB_3B(Mmu* mmu, Cpu* cp) { 
    cp->srl8(&cp->reg_E);
};

void op_CB_3C(Mmu* mmu, Cpu* cp) { 
    cp->srl8(&cp->reg_H);
};

void op_CB_3D(Mmu* mmu, Cpu* cp) { 
    cp->srl8(&cp->reg_L);
};

void op_CB_3E(Mmu* mmu, Cpu* cp) { 
    cp->srl16(&cp->reg_HL);
};

void op_CB_3F(Mmu* mmu, Cpu* cp) { 
    cp->srl8(&cp->reg_A);
};
