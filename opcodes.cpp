#include "opcodes.h"

void(*optable[0xFF])(mmu* memory, cpu* cp);
void(*optable_cb[0xBF])(mmu* memory, cpu* cp);
byte cycle_table[0xFF];
byte cycle_table_cb[0xBF];


void initialize_optable() {
    optable[0x00] = &op_00; cycle_table[0x00] = 4; 
    optable[0x01] = &op_01; cycle_table[0x01] = 12;
    optable[0x02] = &op_02; cycle_table[0x02] = 8;
    optable[0x03] = &op_03; cycle_table[0x03] = 8;
    optable[0x04] = &op_04; cycle_table[0x04] = 4;
    optable[0x05] = &op_05; cycle_table[0x05] = 4;
    optable[0x06] = &op_06; cycle_table[0x06] = 8;
    optable[0x07] = &op_07; cycle_table[0x07] = 4;
    optable[0x08] = &op_08; cycle_table[0x08] = 20;
    optable[0x09] = &op_09; cycle_table[0x09] = 8;
    optable[0x0A] = &op_0A; cycle_table[0x0A] = 8;
    optable[0x0B] = &op_0B; cycle_table[0x0B] = 8;
    optable[0x0C] = &op_0C; cycle_table[0x0C] = 4;
    optable[0x0D] = &op_0D; cycle_table[0x0D] = 4;
    optable[0x0E] = &op_0E; cycle_table[0x0E] = 8;
    optable[0x0F] = &op_0F; cycle_table[0x0F] = 4;

    optable[0x10] = &op_10; cycle_table[0x10] = 4;
    optable[0x11] = &op_11; cycle_table[0x11] = 12;
    optable[0x12] = &op_12; cycle_table[0x12] = 8;
    optable[0x13] = &op_13; cycle_table[0x13] = 8;
    optable[0x14] = &op_14; cycle_table[0x14] = 4;
    optable[0x15] = &op_15; cycle_table[0x15] = 4;
    optable[0x16] = &op_16; cycle_table[0x16] = 8;
    optable[0x17] = &op_17; cycle_table[0x17] = 4;
    optable[0x18] = &op_18; cycle_table[0x18] = 8;
    optable[0x19] = &op_19; cycle_table[0x19] = 8;
    optable[0x1A] = &op_1A; cycle_table[0x1A] = 8;
    optable[0x1B] = &op_1B; cycle_table[0x1B] = 8;
    optable[0x1C] = &op_1C; cycle_table[0x1C] = 4;
    optable[0x1D] = &op_1D; cycle_table[0x1D] = 4;
    optable[0x1E] = &op_1E; cycle_table[0x1E] = 8;
    optable[0x1F] = &op_1F; cycle_table[0x1F] = 4;

    optable[0x20] = &op_20; cycle_table[0x20] = 8;
    optable[0x21] = &op_21; cycle_table[0x21] = 12;
    optable[0x22] = &op_22; cycle_table[0x22] = 8;
    optable[0x23] = &op_23; cycle_table[0x23] = 8;
    optable[0x24] = &op_24; cycle_table[0x24] = 4;
    optable[0x25] = &op_25; cycle_table[0x25] = 4;
    optable[0x26] = &op_26; cycle_table[0x26] = 8;
    optable[0x27] = &op_27; cycle_table[0x27] = 4;
    optable[0x28] = &op_28; cycle_table[0x28] = 8;
    optable[0x29] = &op_29; cycle_table[0x29] = 8;
    optable[0x2A] = &op_2A; cycle_table[0x2A] = 8;
    optable[0x2B] = &op_2B; cycle_table[0x2B] = 8;
    optable[0x2C] = &op_2C; cycle_table[0x2C] = 4;
    optable[0x2D] = &op_2D; cycle_table[0x2D] = 4;
    optable[0x2E] = &op_2E; cycle_table[0x2E] = 8;
    optable[0x2F] = &op_2F; cycle_table[0x2F] = 4;

    optable[0x30] = &op_30; cycle_table[0x30] = 8;
    optable[0x31] = &op_31; cycle_table[0x31] = 12;
    optable[0x32] = &op_32; cycle_table[0x32] = 8;
    optable[0x33] = &op_33; cycle_table[0x33] = 8;
    optable[0x34] = &op_34; cycle_table[0x34] = 12;
    optable[0x35] = &op_35; cycle_table[0x35] = 12;
    optable[0x36] = &op_36; cycle_table[0x36] = 12;
    optable[0x37] = &op_37; cycle_table[0x37] = 4;
    optable[0x38] = &op_38; cycle_table[0x38] = 8;
    optable[0x39] = &op_39; cycle_table[0x39] = 8;
    optable[0x3A] = &op_3A; cycle_table[0x3A] = 8;
    optable[0x3B] = &op_3B; cycle_table[0x3B] = 8;
    optable[0x3C] = &op_3C; cycle_table[0x3C] = 4;
    optable[0x3D] = &op_3D; cycle_table[0x3D] = 4;
    optable[0x3E] = &op_3E; cycle_table[0x3E] = 8;
    optable[0x3F] = &op_3F; cycle_table[0x3F] = 4;

    optable[0x40] = &op_40; cycle_table[0x40] = 4;
    optable[0x41] = &op_41; cycle_table[0x41] = 4;
    optable[0x42] = &op_42; cycle_table[0x42] = 4;
    optable[0x43] = &op_43; cycle_table[0x43] = 4;
    optable[0x44] = &op_44; cycle_table[0x44] = 4;
    optable[0x45] = &op_45; cycle_table[0x45] = 4;
    optable[0x46] = &op_46; cycle_table[0x46] = 8;
    optable[0x47] = &op_47; cycle_table[0x47] = 4;
    optable[0x48] = &op_48; cycle_table[0x48] = 4;
    optable[0x49] = &op_49; cycle_table[0x49] = 4;
    optable[0x4A] = &op_4A; cycle_table[0x4A] = 4;
    optable[0x4B] = &op_4B; cycle_table[0x4B] = 4;
    optable[0x4C] = &op_4C; cycle_table[0x4C] = 4;
    optable[0x4D] = &op_4D; cycle_table[0x4D] = 4;
    optable[0x4E] = &op_4E; cycle_table[0x4E] = 8;
    optable[0x4F] = &op_4F; cycle_table[0x4F] = 4;

    optable[0x50] = &op_50; cycle_table[0x50] = 4;
    optable[0x51] = &op_51; cycle_table[0x51] = 4;
    optable[0x52] = &op_52; cycle_table[0x52] = 4;
    optable[0x53] = &op_53; cycle_table[0x53] = 4;
    optable[0x54] = &op_54; cycle_table[0x54] = 4;
    optable[0x55] = &op_55; cycle_table[0x55] = 4;
    optable[0x56] = &op_56; cycle_table[0x56] = 8;
    optable[0x57] = &op_57; cycle_table[0x57] = 4;
    optable[0x58] = &op_58; cycle_table[0x58] = 4;
    optable[0x59] = &op_59; cycle_table[0x59] = 4;
    optable[0x5A] = &op_5A; cycle_table[0x5A] = 4;
    optable[0x5B] = &op_5B; cycle_table[0x5B] = 4;
    optable[0x5C] = &op_5C; cycle_table[0x5C] = 4;
    optable[0x5D] = &op_5D; cycle_table[0x5D] = 4;
    optable[0x5E] = &op_5E; cycle_table[0x5E] = 8;
    optable[0x5F] = &op_5F; cycle_table[0x5F] = 4;

    optable[0x60] = &op_60; cycle_table[0x60] = 4;
    optable[0x61] = &op_61; cycle_table[0x61] = 4;
    optable[0x62] = &op_62; cycle_table[0x62] = 4;
    optable[0x63] = &op_63; cycle_table[0x63] = 4;
    optable[0x64] = &op_64; cycle_table[0x64] = 4;
    optable[0x65] = &op_65; cycle_table[0x65] = 4;
    optable[0x66] = &op_66; cycle_table[0x66] = 8;
    optable[0x67] = &op_67; cycle_table[0x67] = 4;
    optable[0x68] = &op_68; cycle_table[0x68] = 4;
    optable[0x69] = &op_69; cycle_table[0x69] = 4;
    optable[0x6A] = &op_6A; cycle_table[0x6A] = 4;
    optable[0x6B] = &op_6B; cycle_table[0x6B] = 4;
    optable[0x6C] = &op_6C; cycle_table[0x6C] = 4;
    optable[0x6D] = &op_6D; cycle_table[0x6D] = 4;
    optable[0x6E] = &op_6E; cycle_table[0x6E] = 8;
    optable[0x6F] = &op_6F; cycle_table[0x6F] = 4;

    optable[0x70] = &op_70; cycle_table[0x70] = 8;
    optable[0x71] = &op_71; cycle_table[0x71] = 8;
    optable[0x72] = &op_72; cycle_table[0x72] = 8;
    optable[0x73] = &op_73; cycle_table[0x73] = 8;
    optable[0x74] = &op_74; cycle_table[0x74] = 8;
    optable[0x75] = &op_75; cycle_table[0x75] = 8;
    optable[0x76] = &op_76; cycle_table[0x76] = 4;
    optable[0x77] = &op_77; cycle_table[0x77] = 8;
    optable[0x78] = &op_78; cycle_table[0x78] = 4;
    optable[0x79] = &op_79; cycle_table[0x79] = 4;
    optable[0x7A] = &op_7A; cycle_table[0x7A] = 4;
    optable[0x7B] = &op_7B; cycle_table[0x7B] = 4;
    optable[0x7C] = &op_7C; cycle_table[0x7C] = 4;
    optable[0x7D] = &op_7D; cycle_table[0x7D] = 4;
    optable[0x7E] = &op_7E; cycle_table[0x7E] = 8;
    optable[0x7F] = &op_7F; cycle_table[0x7F] = 4;

    optable[0x80] = &op_80; cycle_table[0x80] = 4;
    optable[0x81] = &op_81; cycle_table[0x81] = 4;
    optable[0x82] = &op_82; cycle_table[0x82] = 4;
    optable[0x83] = &op_83; cycle_table[0x83] = 4;
    optable[0x84] = &op_84; cycle_table[0x84] = 4;
    optable[0x85] = &op_85; cycle_table[0x85] = 4;
    optable[0x86] = &op_86; cycle_table[0x86] = 8;
    optable[0x87] = &op_87; cycle_table[0x87] = 4;
    optable[0x88] = &op_88; cycle_table[0x88] = 4;
    optable[0x89] = &op_89; cycle_table[0x89] = 4;
    optable[0x8A] = &op_8A; cycle_table[0x8A] = 4;
    optable[0x8B] = &op_8B; cycle_table[0x8B] = 4;
    optable[0x8C] = &op_8C; cycle_table[0x8C] = 4;
    optable[0x8D] = &op_8D; cycle_table[0x8D] = 4;
    optable[0x8E] = &op_8E; cycle_table[0x8E] = 8;
    optable[0x8F] = &op_8F; cycle_table[0x8F] = 4;

    optable[0x90] = &op_90; cycle_table[0x90] = 4;
    optable[0x91] = &op_91; cycle_table[0x91] = 4;
    optable[0x92] = &op_92; cycle_table[0x92] = 4;
    optable[0x93] = &op_93; cycle_table[0x93] = 4;
    optable[0x94] = &op_94; cycle_table[0x94] = 4;
    optable[0x95] = &op_95; cycle_table[0x95] = 4;
    optable[0x96] = &op_96; cycle_table[0x96] = 8;
    optable[0x97] = &op_97; cycle_table[0x97] = 4;
    optable[0x98] = &op_98; cycle_table[0x98] = 4;
    optable[0x99] = &op_99; cycle_table[0x99] = 4;
    optable[0x9A] = &op_9A; cycle_table[0x9A] = 4;
    optable[0x9B] = &op_9B; cycle_table[0x9B] = 4;
    optable[0x9C] = &op_9C; cycle_table[0x9C] = 4;
    optable[0x9D] = &op_9D; cycle_table[0x9D] = 4;
    optable[0x9E] = &op_9E; cycle_table[0x9E] = 8;
    optable[0x9F] = &op_9F; cycle_table[0x9F] = 4;

    optable[0xA0] = &op_A0; cycle_table[0xA0] = 4;
    optable[0xA1] = &op_A1; cycle_table[0xA1] = 4;
    optable[0xA2] = &op_A2; cycle_table[0xA2] = 4;
    optable[0xA3] = &op_A3; cycle_table[0xA3] = 4;
    optable[0xA4] = &op_A4; cycle_table[0xA4] = 4;
    optable[0xA5] = &op_A5; cycle_table[0xA5] = 4;
    optable[0xA6] = &op_A6; cycle_table[0xA6] = 8;
    optable[0xA7] = &op_A7; cycle_table[0xA7] = 4;
    optable[0xA8] = &op_A8; cycle_table[0xA8] = 4;
    optable[0xA9] = &op_A9; cycle_table[0xA9] = 4;
    optable[0xAA] = &op_AA; cycle_table[0xAA] = 4;
    optable[0xAB] = &op_AB; cycle_table[0xAB] = 4;
    optable[0xAC] = &op_AC; cycle_table[0xAC] = 4;
    optable[0xAD] = &op_AD; cycle_table[0xAD] = 4;
    optable[0xAE] = &op_AE; cycle_table[0xAE] = 8;
    optable[0xAF] = &op_AF; cycle_table[0xAF] = 4;

    optable[0xB0] = &op_B0; cycle_table[0xB0] = 4;
    optable[0xB1] = &op_B1; cycle_table[0xB1] = 4;
    optable[0xB2] = &op_B2; cycle_table[0xB2] = 4;
    optable[0xB3] = &op_B3; cycle_table[0xB3] = 4;
    optable[0xB4] = &op_B4; cycle_table[0xB4] = 4;
    optable[0xB5] = &op_B5; cycle_table[0xB5] = 4;
    optable[0xB6] = &op_B6; cycle_table[0xB6] = 8;
    optable[0xB7] = &op_B7; cycle_table[0xB7] = 4;
    optable[0xB8] = &op_B8; cycle_table[0xB8] = 4;
    optable[0xB9] = &op_B9; cycle_table[0xB9] = 4;
    optable[0xBA] = &op_BA; cycle_table[0xBA] = 4;
    optable[0xBB] = &op_BB; cycle_table[0xBB] = 4;
    optable[0xBC] = &op_BC; cycle_table[0xBC] = 4;
    optable[0xBD] = &op_BD; cycle_table[0xBD] = 4;
    optable[0xBE] = &op_BE; cycle_table[0xBE] = 8;
    optable[0xBF] = &op_BF; cycle_table[0xBF] = 4;

    optable[0xC0] = &op_C0; cycle_table[0xC0] = 8;
    optable[0xC1] = &op_C1; cycle_table[0xC1] = 12;
    optable[0xC2] = &op_C2; cycle_table[0xC2] = 12;
    optable[0xC3] = &op_C3; cycle_table[0xC3] = 12;
    optable[0xC4] = &op_C4; cycle_table[0xC4] = 12;
    optable[0xC5] = &op_C5; cycle_table[0xC5] = 16;
    optable[0xC6] = &op_C6; cycle_table[0xC6] = 8;
    optable[0xC7] = &op_C7; cycle_table[0xC7] = 32;
    optable[0xC8] = &op_C8; cycle_table[0xC8] = 8;
    optable[0xC9] = &op_C9; cycle_table[0xC9] = 8;
    optable[0xCA] = &op_CA; cycle_table[0xCA] = 12;
    optable[0xCC] = &op_CC; cycle_table[0xCC] = 12;
    optable[0xCD] = &op_CD; cycle_table[0xCD] = 12;
    optable[0xCE] = &op_CE; cycle_table[0xCE] = 8;
    optable[0xCF] = &op_CF; cycle_table[0xCF] = 32;

    optable[0xD0] = &op_D0; cycle_table[0xD0] = 8;
    optable[0xD1] = &op_D1; cycle_table[0xD1] = 12;
    optable[0xD2] = &op_D2; cycle_table[0xD2] = 12;
    optable[0xD4] = &op_D4; cycle_table[0xD4] = 12;
    optable[0xD5] = &op_D5; cycle_table[0xD5] = 16;
    optable[0xD6] = &op_D6; cycle_table[0xD6] = 8;
    optable[0xD7] = &op_D7; cycle_table[0xD7] = 32;
    optable[0xD8] = &op_D8; cycle_table[0xD8] = 8;
    optable[0xD9] = &op_D9; cycle_table[0xD9] = 8;
    optable[0xDA] = &op_DA; cycle_table[0xDA] = 12;
    optable[0xDC] = &op_DC; cycle_table[0xDC] = 12;
    optable[0xDF] = &op_DF; cycle_table[0xDF] = 32;

    optable[0xE0] = &op_E0; cycle_table[0xE0] = 12;
    optable[0xE1] = &op_E1; cycle_table[0xE1] = 12;
    optable[0xE2] = &op_E2; cycle_table[0xE2] = 8;
    optable[0xE5] = &op_E5; cycle_table[0xE5] = 16;
    optable[0xE6] = &op_E6; cycle_table[0xE6] = 8;
    optable[0xE7] = &op_E7; cycle_table[0xE7] = 32;
    optable[0xE8] = &op_E8; cycle_table[0xE8] = 16;
    optable[0xE9] = &op_E9; cycle_table[0xE9] = 4;
    optable[0xEA] = &op_EA; cycle_table[0xEA] = 16;
    optable[0xEE] = &op_EE; cycle_table[0xEE] = 8;
    optable[0xEF] = &op_EF; cycle_table[0xEF] = 32;

    optable[0xF0] = &op_F0; cycle_table[0xF0] = 12;
    optable[0xF1] = &op_F1; cycle_table[0xF1] = 12;
    optable[0xF2] = &op_F2; cycle_table[0xF2] = 8;
    optable[0xF3] = &op_F3; cycle_table[0xF3] = 4;
    optable[0xF5] = &op_F5; cycle_table[0xF5] = 16;
    optable[0xF6] = &op_F6; cycle_table[0xF6] = 8;
    optable[0xF7] = &op_F7; cycle_table[0xF7] = 32;
    optable[0xF8] = &op_F8; cycle_table[0xF8] = 12;
    optable[0xF9] = &op_F9; cycle_table[0xF9] = 8;
    optable[0xFA] = &op_FA; cycle_table[0xFA] = 16;
    optable[0xFB] = &op_FB; cycle_table[0xFB] = 4;
    optable[0xFE] = &op_FE; cycle_table[0xFE] = 8;
    optable[0xFF] = &op_FF; cycle_table[0xFF] = 32;

    initialize_optable_cb();
    optable[0xCB] = &op_CB;


}

void initialize_optable_cb() {
    optable_cb[0x00] = &op_CB_00; cycle_table_cb[0x00] = 8;
    optable_cb[0x01] = &op_CB_01; cycle_table_cb[0x01] = 8;
    optable_cb[0x02] = &op_CB_02; cycle_table_cb[0x02] = 8;
    optable_cb[0x03] = &op_CB_03; cycle_table_cb[0x03] = 8;
    optable_cb[0x04] = &op_CB_04; cycle_table_cb[0x04] = 8;
    optable_cb[0x05] = &op_CB_05; cycle_table_cb[0x05] = 8;
    optable_cb[0x06] = &op_CB_06; cycle_table_cb[0x06] = 16;
    optable_cb[0x07] = &op_CB_07; cycle_table_cb[0x07] = 8;
    optable_cb[0x08] = &op_CB_08; cycle_table_cb[0x08] = 8;
    optable_cb[0x09] = &op_CB_09; cycle_table_cb[0x09] = 8;
    optable_cb[0x0a] = &op_CB_0A; cycle_table_cb[0x0a] = 8;
    optable_cb[0x0b] = &op_CB_0B; cycle_table_cb[0x0b] = 8;
    optable_cb[0x0c] = &op_CB_0C; cycle_table_cb[0x0c] = 8;
    optable_cb[0x0d] = &op_CB_0D; cycle_table_cb[0x0d] = 8;
    optable_cb[0x0e] = &op_CB_0E; cycle_table_cb[0x0e] = 16;
    optable_cb[0x0f] = &op_CB_0F; cycle_table_cb[0x0f] = 8;

    optable_cb[0x10] = &op_CB_10; cycle_table_cb[0x10] = 8;
    optable_cb[0x11] = &op_CB_11; cycle_table_cb[0x11] = 8;
    optable_cb[0x12] = &op_CB_12; cycle_table_cb[0x12] = 8;
    optable_cb[0x13] = &op_CB_13; cycle_table_cb[0x13] = 8;
    optable_cb[0x14] = &op_CB_14; cycle_table_cb[0x14] = 8;
    optable_cb[0x15] = &op_CB_15; cycle_table_cb[0x15] = 8;
    optable_cb[0x16] = &op_CB_16; cycle_table_cb[0x16] = 16;
    optable_cb[0x17] = &op_CB_17; cycle_table_cb[0x17] = 8;
    optable_cb[0x18] = &op_CB_18; cycle_table_cb[0x18] = 8;
    optable_cb[0x19] = &op_CB_19; cycle_table_cb[0x19] = 8;
    optable_cb[0x1A] = &op_CB_1A; cycle_table_cb[0x1A] = 8;
    optable_cb[0x1B] = &op_CB_1B; cycle_table_cb[0x1B] = 8;
    optable_cb[0x1C] = &op_CB_1C; cycle_table_cb[0x1C] = 8;
    optable_cb[0x1D] = &op_CB_1D; cycle_table_cb[0x1D] = 8;
    optable_cb[0x1E] = &op_CB_1E; cycle_table_cb[0x1E] = 16;
    optable_cb[0x1F] = &op_CB_1F; cycle_table_cb[0x1F] = 8;

    optable_cb[0x20] = &op_CB_20; cycle_table_cb[0x20] = 8;
    optable_cb[0x21] = &op_CB_21; cycle_table_cb[0x21] = 8;
    optable_cb[0x22] = &op_CB_22; cycle_table_cb[0x22] = 8;
    optable_cb[0x23] = &op_CB_23; cycle_table_cb[0x23] = 8;
    optable_cb[0x24] = &op_CB_24; cycle_table_cb[0x24] = 8;
    optable_cb[0x25] = &op_CB_25; cycle_table_cb[0x25] = 8;
    optable_cb[0x26] = &op_CB_26; cycle_table_cb[0x26] = 16;
    optable_cb[0x27] = &op_CB_27; cycle_table_cb[0x27] = 8;
    optable_cb[0x28] = &op_CB_28; cycle_table_cb[0x28] = 8;
    optable_cb[0x29] = &op_CB_29; cycle_table_cb[0x29] = 8;
    optable_cb[0x2A] = &op_CB_2A; cycle_table_cb[0x2A] = 8;
    optable_cb[0x2B] = &op_CB_2B; cycle_table_cb[0x2B] = 8;
    optable_cb[0x2C] = &op_CB_2C; cycle_table_cb[0x2C] = 8;
    optable_cb[0x2D] = &op_CB_2D; cycle_table_cb[0x2D] = 8;
    optable_cb[0x2E] = &op_CB_2E; cycle_table_cb[0x2E] = 16;
    optable_cb[0x2F] = &op_CB_2F; cycle_table_cb[0x2F] = 8;

    optable_cb[0x30] = &op_CB_30; cycle_table_cb[0x30] = 4;
    optable_cb[0x31] = &op_CB_31; cycle_table_cb[0x31] = 4;
    optable_cb[0x32] = &op_CB_32; cycle_table_cb[0x32] = 4;
    optable_cb[0x33] = &op_CB_33; cycle_table_cb[0x33] = 4;
    optable_cb[0x34] = &op_CB_34; cycle_table_cb[0x34] = 4;
    optable_cb[0x35] = &op_CB_35; cycle_table_cb[0x35] = 4;
    optable_cb[0x36] = &op_CB_36; cycle_table_cb[0x36] = 16;
    optable_cb[0x37] = &op_CB_37; cycle_table_cb[0x37] = 4;
    optable_cb[0x38] = &op_CB_38; cycle_table_cb[0x38] = 8;
    optable_cb[0x39] = &op_CB_39; cycle_table_cb[0x39] = 8;
    optable_cb[0x3A] = &op_CB_3A; cycle_table_cb[0x3A] = 8;
    optable_cb[0x3B] = &op_CB_3B; cycle_table_cb[0x3B] = 8;
    optable_cb[0x3C] = &op_CB_3C; cycle_table_cb[0x3C] = 8;
    optable_cb[0x3D] = &op_CB_3D; cycle_table_cb[0x3D] = 8;
    optable_cb[0x3E] = &op_CB_3E; cycle_table_cb[0x3E] = 16;
    optable_cb[0x3F] = &op_CB_3F; cycle_table_cb[0x3F] = 8;
}




void op_00(mmu* memory, cpu* cp) {
    ;
};

void op_01(mmu* memory, cpu* cp) {
    cp->registers[B] = memory->address[++cp->pc];
    cp->registers[C] = memory->address[++cp->pc];
};

void op_02(mmu* memory, cpu* cp) {
    // FIXME: not sure, seems fine, o gajo deve ter diferente
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

void op_10(mmu* memory, cpu* cp) {
    // TODO: STOP
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
    cp->pc++;
    if(!cp->get_z_flag()) { 
        cp->pc += memory->address[cp->pc] - 1;    // FIXME: no idea
    }
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
    cp->registers[A] = memory->address[++cp->pc];
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
    cp->pc = (memory->address[++cp->pc] | (memory->address[++cp->pc] << 8)) - 1;
};

void op_C4(mmu* memory, cpu* cp) {
    // FIXME: pode ser para saltar o address ou para o valor nn
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

    unsigned short nn = memory->address[++cp->pc] | (memory->address[++cp->pc] << 8);
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
    cp->add_sp_pc();
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
    cp->cp(cp->registers[A], memory->address[++cp->pc]);
};

void op_FF(mmu* memory, cpu* cp) {
    cp->stack[--(cp->sp)] = cp->pc;
    cp->pc = 0x38;
};

void op_CB(mmu* memory, cpu* cp) {
    // TODO:
    int opcode = memory->address[++(cp->pc)];
    printf("cb::: %02x\n", opcode);

    if(opcode >= 0xC0) {
        // FIXME: does not work for r16
        cp->set_r1(opcode & 0x07, opcode & 0x38);
    }
    else if(opcode < 0xC0 && opcode >= 0x80) {
        cp->res_r1(opcode & 0x07, opcode & 0x38);
    }
    else if(opcode < 0x80 && opcode >= 0x40) {
        cp->bit_r1(opcode & 0x07, opcode & 0x38);
    }
    else {
        printf("fdofjo\n");
        (*optable_cb[opcode])(memory, cp);
    }

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
