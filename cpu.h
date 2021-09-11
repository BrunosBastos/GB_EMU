#ifndef _CPU_H_
#define _CPU_H_

#include "mmu.h"


#define A 0
#define F 1
#define B 2
#define C 3
#define D 4
#define E 5
#define H 6
#define L 7



class cpu {

    public:

        void initialize(mmu* mmu);
        void emulate_cycle();
        void execute_opcode();

        void cpu_init_table();
        void cpu_init_table_cb();

        void op_00();
        void op_01();
        void op_02();
        void op_03();
        void op_04();
        void op_05();
        void op_06();
        void op_07();
        void op_08();
        void op_09();
        void op_0A();
        void op_0B();
        void op_0C();
        void op_0D();
        void op_0E();
        void op_0F();
        
        void op_10();
        void op_11();
        void op_12();
        void op_13();
        void op_14();
        void op_15();
        void op_16();
        void op_17();
        void op_18();
        void op_19();
        void op_1A();
        void op_1B();
        void op_1C();
        void op_1D();
        void op_1E();
        void op_1F();

        void op_20();
        void op_21();
        void op_22();
        void op_23();
        void op_24();
        void op_25();
        void op_26();
        void op_27();
        void op_28();
        void op_29();
        void op_2A();
        void op_2B();
        void op_2C();
        void op_2D();
        void op_2E();
        void op_2F();

        void op_30();
        void op_31();
        void op_32();
        void op_33();
        void op_34();
        void op_35();
        void op_36();
        void op_37();
        void op_38();
        void op_39();
        void op_3A();
        void op_3B();
        void op_3C();
        void op_3D();
        void op_3E();
        void op_3F();

        void op_40();
        void op_41();
        void op_42();
        void op_43();
        void op_44();
        void op_45();
        void op_46();
        void op_47();
        void op_48();
        void op_49();
        void op_4A();
        void op_4B();
        void op_4C();
        void op_4D();
        void op_4E();
        void op_4F();

        void op_50();
        void op_51();
        void op_52();
        void op_53();
        void op_54();
        void op_55();
        void op_56();
        void op_57();
        void op_58();
        void op_59();
        void op_5A();
        void op_5B();
        void op_5C();
        void op_5D();
        void op_5E();
        void op_5F();

        void op_60();
        void op_61();
        void op_62();
        void op_63();
        void op_64();
        void op_65();
        void op_66();
        void op_67();
        void op_68();
        void op_69();
        void op_6A();
        void op_6B();
        void op_6C();
        void op_6D();
        void op_6E();
        void op_6F();

        void op_70();
        void op_71();
        void op_72();
        void op_73();
        void op_74();
        void op_75();
        void op_76();
        void op_77();
        void op_78();
        void op_79();
        void op_7A();
        void op_7B();
        void op_7C();
        void op_7D();
        void op_7E();
        void op_7F();

        void op_80();
        void op_81();
        void op_82();
        void op_83();
        void op_84();
        void op_85();
        void op_86();
        void op_87();
        void op_88();
        void op_89();
        void op_8A();
        void op_8B();
        void op_8C();
        void op_8D();
        void op_8E();
        void op_8F();

        void op_90();
        void op_91();
        void op_92();
        void op_93();
        void op_94();
        void op_95();
        void op_96();
        void op_97();
        void op_98();
        void op_99();
        void op_9A();
        void op_9B();
        void op_9C();
        void op_9D();
        void op_9E();
        void op_9F();

        void op_A0();
        void op_A1();
        void op_A2();
        void op_A3();
        void op_A4();
        void op_A5();
        void op_A6();
        void op_A7();
        void op_A8();
        void op_A9();
        void op_AA();
        void op_AB();
        void op_AC();
        void op_AD();
        void op_AE();
        void op_AF();

        void op_B0();
        void op_B1();
        void op_B2();
        void op_B3();
        void op_B4();
        void op_B5();
        void op_B6();
        void op_B7();
        void op_B8();
        void op_B9();
        void op_BA();
        void op_BB();
        void op_BC();
        void op_BD();
        void op_BE();
        void op_BF();

        void op_C0();
        void op_C1();
        void op_C2();
        void op_C3();
        void op_C4();
        void op_C5();
        void op_C6();
        void op_C7();
        void op_C8();
        void op_C9();
        void op_CA();
        void op_CB();
        void op_CC();
        void op_CD();
        void op_CE();
        void op_CF();

        void op_D0();
        void op_D1();
        void op_D2();
        void op_D3();
        void op_D4();
        void op_D5();
        void op_D6();
        void op_D7();
        void op_D8();
        void op_D9();
        void op_DA();
        void op_DB();
        void op_DC();
        void op_DD();
        void op_DE();
        void op_DF();

        void op_E0();
        void op_E1();
        void op_E2();
        void op_E3();
        void op_E4();
        void op_E5();
        void op_E6();
        void op_E7();
        void op_E8();
        void op_E9();
        void op_EA();
        void op_EB();
        void op_EC();
        void op_ED();
        void op_EE();
        void op_EF();

        void op_F0();
        void op_F1();
        void op_F2();
        void op_F3();
        void op_F4();
        void op_F5();
        void op_F6();
        void op_F7();
        void op_F8();
        void op_F9();
        void op_FA();
        void op_FB();
        void op_FC();
        void op_FD();
        void op_FE();
        void op_FF();

        
        void op_CB_00();
        void op_CB_01();
        void op_CB_02();
        void op_CB_03();
        void op_CB_04();
        void op_CB_05();
        void op_CB_06();
        void op_CB_07();
        void op_CB_08();
        void op_CB_09();
        void op_CB_0A();
        void op_CB_0B();
        void op_CB_0C();
        void op_CB_0D();
        void op_CB_0E();
        void op_CB_0F();

        void op_CB_10();
        void op_CB_11();
        void op_CB_12();
        void op_CB_13();
        void op_CB_14();
        void op_CB_15();
        void op_CB_16();
        void op_CB_17();
        void op_CB_18();
        void op_CB_19();
        void op_CB_1A();
        void op_CB_1B();
        void op_CB_1C();
        void op_CB_1D();
        void op_CB_1E();
        void op_CB_1F();

        void op_CB_20();
        void op_CB_21();
        void op_CB_22();
        void op_CB_23();
        void op_CB_24();
        void op_CB_25();
        void op_CB_26();
        void op_CB_27();
        void op_CB_28();
        void op_CB_29();
        void op_CB_2A();
        void op_CB_2B();
        void op_CB_2C();
        void op_CB_2D();
        void op_CB_2E();
        void op_CB_2F();

        void op_CB_30();
        void op_CB_31();
        void op_CB_32();
        void op_CB_33();
        void op_CB_34();
        void op_CB_35();
        void op_CB_36();
        void op_CB_37();
        void op_CB_38();
        void op_CB_39();
        void op_CB_3A();
        void op_CB_3B();
        void op_CB_3C();
        void op_CB_3D();
        void op_CB_3E();
        void op_CB_3F();

        void op_CB_40();
        void op_CB_41();
        void op_CB_42();
        void op_CB_43();
        void op_CB_44();
        void op_CB_45();
        void op_CB_46();
        void op_CB_47();
        void op_CB_48();
        void op_CB_49();
        void op_CB_4A();
        void op_CB_4B();
        void op_CB_4C();
        void op_CB_4D();
        void op_CB_4E();
        void op_CB_4F();

        void op_CB_50();
        void op_CB_51();
        void op_CB_52();
        void op_CB_53();
        void op_CB_54();
        void op_CB_55();
        void op_CB_56();
        void op_CB_57();
        void op_CB_58();
        void op_CB_59();
        void op_CB_5A();
        void op_CB_5B();
        void op_CB_5C();
        void op_CB_5D();
        void op_CB_5E();
        void op_CB_5F();

        void op_CB_60();
        void op_CB_61();
        void op_CB_62();
        void op_CB_63();
        void op_CB_64();
        void op_CB_65();
        void op_CB_66();
        void op_CB_67();
        void op_CB_68();
        void op_CB_69();
        void op_CB_6A();
        void op_CB_6B();
        void op_CB_6C();
        void op_CB_6D();
        void op_CB_6E();
        void op_CB_6F();

        void op_CB_70();
        void op_CB_71();
        void op_CB_72();
        void op_CB_73();
        void op_CB_74();
        void op_CB_75();
        void op_CB_76();
        void op_CB_77();
        void op_CB_78();
        void op_CB_79();
        void op_CB_7A();
        void op_CB_7B();
        void op_CB_7C();
        void op_CB_7D();
        void op_CB_7E();
        void op_CB_7F();

        void op_CB_80();
        void op_CB_81();
        void op_CB_82();
        void op_CB_83();
        void op_CB_84();
        void op_CB_85();
        void op_CB_86();
        void op_CB_87();
        void op_CB_88();
        void op_CB_89();
        void op_CB_8A();
        void op_CB_8B();
        void op_CB_8C();
        void op_CB_8D();
        void op_CB_8E();
        void op_CB_8F();

        void op_CB_90();
        void op_CB_91();
        void op_CB_92();
        void op_CB_93();
        void op_CB_94();
        void op_CB_95();
        void op_CB_96();
        void op_CB_97();
        void op_CB_98();
        void op_CB_99();
        void op_CB_9A();
        void op_CB_9B();
        void op_CB_9C();
        void op_CB_9D();
        void op_CB_9E();
        void op_CB_9F();

        void op_CB_A0();
        void op_CB_A1();
        void op_CB_A2();
        void op_CB_A3();
        void op_CB_A4();
        void op_CB_A5();
        void op_CB_A6();
        void op_CB_A7();
        void op_CB_A8();
        void op_CB_A9();
        void op_CB_AA();
        void op_CB_AB();
        void op_CB_AC();
        void op_CB_AD();
        void op_CB_AE();
        void op_CB_AF();

        void op_CB_B0();
        void op_CB_B1();
        void op_CB_B2();
        void op_CB_B3();
        void op_CB_B4();
        void op_CB_B5();
        void op_CB_B6();
        void op_CB_B7();
        void op_CB_B8();
        void op_CB_B9();
        void op_CB_BA();
        void op_CB_BB();
        void op_CB_BC();
        void op_CB_BD();
        void op_CB_BE();
        void op_CB_BF();


        void op_ld_nn_n(byte reg);
        void op_ld_r1_r2(byte r1, byte r2);
        //void op_ld_hl_r2(byte r2);
        //void op_ld_r1_hl(byte r1);
        void op_ld_hl_n();
        void op_ld_a_nn();
        void op_ld_a_pc();
        void op_ld_r1_r16(byte r1, byte r16);         // loads 16 bit register into 8bit 
        void op_ld_nn_a();
        void op_ld_r16_r2(byte r16, byte r2);

        
        void op_ld_a_C();
        void op_ld_C_a();
        void op_ldd_a_hl();
        void op_ldd_hl_a();
        void op_ldi_a_hl();
        void op_ldi_hl_a();
        void op_ldh_n_a();
        void op_ldh_a_n();

        // 16 bit loads

        void op_ld_r16_nn(byte r16);
        void op_ld_sp_nn();
        void op_ld_sp_hl();
        void op_ldhl_sp_n();
        void op_ld_nn_sp();

        void op_push_nn(byte r16);
        void op_pop_nn(byte r16);

        void op_add_a_r1(byte r1);
        void op_add_a_hl();
        void op_add_a_pc();
        void op_addc_a_r1(byte r1);
        void op_addc_a_hl();
        void op_addc_a_pc();
        void op_sub_a_r1(byte r1);
        void op_sub_a_hl();
        void op_sub_a_pc();
        void op_subc_a_r1(byte r1);
        void op_subc_a_hl();
        void op_subc_a_pc();
        void op_and_a_r1(byte r1);
        void op_and_a_hl();
        void op_and_a_pc();
        void op_or_a_r1(byte r1);
        void op_or_a_hl();
        void op_or_a_pc();
        void op_xor_a_r1(byte r1);
        void op_xor_a_hl();
        void op_xor_a_pc();
        void op_cp_a_r1(byte r1);
        void op_cp_a_hl();
        void op_cp_a_pc();
        void op_inc_r1(byte r1);
        void op_dec_r1(byte r1);


        void op_add_hl_r16(byte r16);
        void op_add_hl_sp();
        void op_add_sp_pc();
        void op_inc_r16(byte r16);
        void op_dec_r16(byte r16);

        void op_swap_r1(byte r1);
        void op_swap_r16(byte r16);
        void op_cpl_a();
        void op_ccf();
        void op_scf();
        
        void op_rlc_r1(byte r1);
        void op_rl_r1(byte r1);
        void op_rrc_r1(byte r1);
        void op_rr_r1(byte r1);
        void op_sla_r1(byte r1);
        void op_sra_r1(byte r1);
        void op_srl_r1(byte r1);
        
        void op_bit_r1(byte r1, byte bit);
        void op_set_r1(byte r1, byte bit);
        void op_res_r1(byte r1, byte bit);

        void op_jp_nn();
        void op_jp_cc_nn(byte cc);
        void op_jp_hl();
        void op_jr_n();        // n is a 8 bit immediate signed value
        void op_jr_cc_n(byte cc);

        void op_call_nn();
        void op_call_cc_nn(byte cc);

        void op_rst_n(byte n);

        void op_ret();
        void op_ret_cc(byte cc);
        void op_reti();

        byte add8(byte op1, byte op2);
        byte sub8(byte op1, byte op2);
        byte and8(byte op1, byte op2);
        byte or8(byte op1, byte op2);
        byte xor8(byte op1, byte op2);
        void cp(byte op1, byte op2);
        byte inc8(byte op1);
        byte dec8(byte op1);

        unsigned short add16(unsigned short op1, unsigned short op2);
        unsigned short inc16(unsigned short op1);
        unsigned short dec16(unsigned short op1);


        void set_z_flag();
        void set_n_flag();
        void set_h_flag();
        void set_c_flag();

        void reset_z_flag();
        void reset_n_flag();
        void reset_h_flag();
        void reset_c_flag();

        byte get_z_flag();
        byte get_n_flag();
        byte get_h_flag();
        byte get_c_flag();


        void(cpu:: *optable[0xFF])();
        void(cpu:: *optable_cb[0xBF])();
        mmu *memory;                // pointer to the memory object
        unsigned short pc;
        unsigned short opcode;

        int last_clock;         // keeps track of the number of cycles from the last opcode
        int total_clock;        // keeps track of the number of cycles since the beginning

        byte registers[8];          // A-F B-C D-E H-L

        unsigned short sp;
        unsigned short stack[16];   // TODO: check if the size of the stack is correct


};

#endif
