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
        mmu *memory;                // pointer to the memory object
        word pc;
        word opcode;

        int last_clock;         // keeps track of the number of cycles from the last opcode
        int total_clock;        // keeps track of the number of cycles since the beginning
        int time_counter;
        int divider_counter;
        int current_clock_speed;
        
        byte joypad_state;

        byte registers[8];          // A-F B-C D-E H-L

        word sp;

        byte current_rom_bank;
        byte current_ram_bank;
        bool mbc1;
        bool mbc2;
        bool mbc3;
        bool enable_ram_bank;
        bool using16_8_model;


        bool interrupt_master;
        bool pending_interrupt_disabled;
        bool pending_interrupt_enabled;

        void emulate_cycle();
        void execute_opcode();

        void cpu_init_table();
        void cpu_init_table_cb();

        byte read_memory(word addr);
        void write_memory(word address, byte data);

        void debug();
        void request_interrupt(int id);
        void execute_interrupts();
        void service_interrupt(int id);

        void update_timers();

        void key_released(int key);
        void key_pressed(int key);
        byte get_joypad_state();


        void ld_nn_n(byte reg);
        void ld_r1_r2(byte r1, byte r2);
        //void ld_hl_r2(byte r2);
        //void ld_r1_hl(byte r1);
        void ld_hl_n();
        void ld_a_nn();
        void ld_a_pc();
        void ld_r1_r16(byte r1, byte r16);         // loads 16 bit register into 8bit 
        void ld_nn_a();
        void ld_r16_r2(byte r16, byte r2);

        
        void ld_a_C();
        void ld_C_a();
        void ldd_a_hl();
        void ldd_hl_a();
        void ldi_a_hl();
        void ldi_hl_a();
        void ldh_n_a();
        void ldh_a_n();

        // 16 bit loads

        void ld_r16_nn(byte r16);
        void ld_sp_nn();
        void ld_sp_hl();
        void ldhl_sp_n();
        void ld_nn_sp();

        void push_nn(byte r16);
        void pop_nn(byte r16);

        void add_a_r1(byte r1);
        void add_a_hl();
        void add_a_pc();
        void addc_a_r1(byte r1);
        void addc_a_hl();
        void addc_a_pc();
        void sub_a_r1(byte r1);
        void sub_a_hl();
        void sub_a_pc();
        void subc_a_r1(byte r1);
        void subc_a_hl();
        void subc_a_pc();
        void and_a_r1(byte r1);
        void and_a_hl();
        void and_a_pc();
        void or_a_r1(byte r1);
        void or_a_hl();
        void or_a_pc();
        void xor_a_r1(byte r1);
        void xor_a_hl();
        void xor_a_pc();
        void cp_a_r1(byte r1);
        void cp_a_hl();
        void cp_a_pc();
        void inc_r1(byte r1);
        void dec_r1(byte r1);


        void add_hl_r16(byte r16);
        void add_hl_sp();
        void add_sp_pc();
        void inc_r16(byte r16);
        void dec_r16(byte r16);

        void swap_r1(byte r1);
        void swap_r16(byte r16);
        void cpl_a();
        void ccf();
        void scf();
        
        void rlc_r1(byte r1);
        void rl_r1(byte r1);
        void rrc_r1(byte r1);
        void rr_r1(byte r1);
        void sla_r1(byte r1);
        void sra_r1(byte r1);
        void srl_r1(byte r1);
        
        void bit_r1(byte r1, byte bit);
        void set_r1(byte r1, byte bit);
        void res_r1(byte r1, byte bit);

        void jp_nn();
        void jp_cc_nn(byte cc);
        void jp_hl();
        void jr_n();        // n is a 8 bit immediate signed value
        void jr_cc_n(byte cc);

        void call_nn();
        void call_cc_nn(byte cc);

        void rst_n(byte n);

        void ret();
        void store_pc_stack();
        void push16(byte r1);
        void pop16(byte r1); 

        void ret_cc(byte cc);
        void reti();

        byte add8(byte op1, byte op2);
        byte sub8(byte op1, byte op2);
        byte and8(byte op1, byte op2);
        byte or8(byte op1, byte op2);
        byte xor8(byte op1, byte op2);
        void cp(byte op1, byte op2);
        void inc8(byte op1);
        void dec8(byte op1);

        word add16(word op1, word op2);
        word inc16(word op1);
        word dec16(word op1);


        void set_z_flag(byte value);
        void set_n_flag(byte value);
        void set_h_flag(byte value);
        void set_c_flag(byte value);

        bool get_z_flag();
        bool get_n_flag();
        bool get_h_flag();
        bool get_c_flag();

};

#endif
