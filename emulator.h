#ifndef EMULATOR_H
#define EMULATOR_H

#include "types.h"
#include "cpu.h"
#include "mmu.h"
#include "ppu.h"


class Emulator {

    public:
		Emulator(char *filename);
		void run();
		Cpu *cpu;
		Mmu *mmu;
		Ppu *ppu;


		void key_pressed(int key);
		void key_released(int key);
	
    private:

		// float framerate = 60;
		int clock_count = 456;

		// -------- EVENTS ------- //
		// void handle_events();

		// -------- JOYPAD ------- //
		// int get_key_id(Key key);
		int joypad_state;

		// -------- SAVESTATES ------- //
		// void save_state(int id);
		// void load_state(int id);

		// --------- DIVIDER --------- //
		int divider_counter = 0;
		// int divider_frequency = 16384; // 16384 Hz or every 256 CPU clock cycles
		// void update_divider(int cycles);

		// ----------TIMERS ---------- //
		int time_counter = 0;
		// byte timer_frequency = 0;
		void update_timers();
		// bool timer_enabled();
		// byte get_timer_frequency();
		// void set_timer_frequency();

		// ------- INTERRUPTS ------- //
		bool interrupt_master = false;
        void request_interrupt(int id);
        void execute_interrupts();
        void service_interrupt(int id);

		// ------ LCD Display ------ //
		// int scanline_counter = 456; // Clock cycles per scanline draw

    

		void set_lcd_status();
		void update_graphics();
};

#endif
