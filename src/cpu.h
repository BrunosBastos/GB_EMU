#ifndef CPU_H
#define CPU_H

#include "mmu.h"




class Cpu {

    public:

        Cpu(Mmu* mmu);
        Mmu *mmu;               // pointer to the memory object
        word pc = 0x100;		// program counter
        word opcode;			// current operation code
        word sp = 0xFFFE;		// stack pointer

        int n_op = 0;

        int last_clock;         // keeps track of the number of cycles from the last opcode
        int total_clock;        // keeps track of the number of cycles since the beginning
        int time_counter;
        int divider_counter;
        int current_clock_speed;
        
        byte reg_A, reg_F, 		// registers 
            reg_B, reg_C, 
            reg_D, reg_E, 
            reg_H, reg_L;

        PairRegister reg_AF = PairRegister(&reg_A, &reg_F);		// register pairs
        PairRegister reg_BC = PairRegister(&reg_B, &reg_C);
        PairRegister reg_DE = PairRegister(&reg_D, &reg_E);
        PairRegister reg_HL = PairRegister(&reg_H, &reg_L);

        bool interrupt_master;
        bool pending_interrupt_disabled;
        bool pending_interrupt_enabled;

        void emulate_cycle();
        void execute_opcode();

        void debug();
        void debug_tile_addr();
        void debug_map_addr();
        void debug_dump_memory();

        void swap8(byte *r8);
        void swap16(PairRegister *r16);
        
        void rlc8(byte *r8);
        void rl8(byte *r8);
        void rrc8(byte *r8);
        void rr8(byte *r8);
        void sla8(byte *r8);
        void sra8(byte *r8);
        void srl8(byte *r8);
        void rl16(PairRegister *r16);
        void rr16(PairRegister *r16);
        void rlc16(PairRegister *r16);
        void rrc16(PairRegister *r16);
        void sra16(PairRegister *r16);
        void sla16(PairRegister *r16);
        void srl16(PairRegister *r16);
        
        void bit(byte *r8, byte bit);
        void bit(PairRegister *r16, byte bit);
        void set(byte *r8, byte bit);
        void set(PairRegister *r16, byte bit);
        void res(byte *r8, byte bit);
        void res(PairRegister *r16, byte bit);
        
        void ret();
        void store_pc_stack();
        
        void add8(byte *op1, byte op2);
        void sub8(byte *op1, byte op2);
        void and8(byte *op1, byte op2);
        void or8(byte *op1, byte op2);
        void xor8(byte *op1, byte op2);
        void cp8(byte *op1, byte op2);
        void inc8(byte *op1);
        void dec8(byte *op1);

        void add16(PairRegister *op1, word op2);
        void push16(PairRegister *r16);
        void pop16(PairRegister *r16); 

        void set_z_flag(bool value);
        void set_n_flag(bool value);
        void set_h_flag(bool value);
        void set_c_flag(bool value);

        bool get_z_flag();
        bool get_n_flag();
        bool get_h_flag();
        bool get_c_flag();
};

#endif
