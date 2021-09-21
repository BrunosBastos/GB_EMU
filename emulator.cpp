#include "emulator.h"


Emulator::Emulator(char *filename) {

    Cartridge *c = new Cartridge(filename);
    Mmu *mmu = new Mmu(c);
    Cpu *cpu = new Cpu(mmu);
    Ppu *ppu = new Ppu(mmu);

}

void Emulator::request_interrupt(int id) {
    mmu->write_memory(0xFF0F, mmu->read_memory(0xFF0F) | (1 << id));
};

void Emulator::execute_interrupts() {
    if (interrupt_master) {
        byte req = mmu->read_memory(0xFF0F);
        byte enabled = mmu->read_memory(0xFFFF);

        if (req & 0xFF) {
            // check if any of the bits is 1
            for (int i = 0; i <= 4; i++) {
                // check if the bit is set and if so check if it is
                // enabled in the other flag
                if ((req & (1 << i)) && (enabled & (1 << i))) {
                    // FIXME: does this need a break?
                    service_interrupt(i);
                }
            }
        }
    }
};

void Emulator::service_interrupt(int id) {
    // master interrupt and the bit of the current interrupt are reset
    interrupt_master = false;
    mmu->write_memory(0xFF0F, mmu->read_memory(0xFF0F) & ~(1 << id));

    cpu->store_pc_stack();

    switch (id) {
        case INTERRUPT_VBLANK:
            cpu->pc = 0x40;
            break;
        case INTERRUPT_LCDC:
            cpu->pc = 0x48;
            break;
        case INTERRUPT_TIMER:
            cpu->pc = 0x50;
            break;
        case INTERRUPT_JOYPAD:
            cpu->pc = 0x60;
            break;
    }
};

/* Joypad */

void Emulator::key_pressed(int key) {
    bool previously_unset = false;

    if (!(joypad_state & (1 << key))) {
        previously_unset = true;
    }

    joypad_state &= ~(1 << key);

    byte res = mmu->read_memory(0xFF00);
    bool req_interrupt = false;

    // standard buttons
    if (key > 3 && !(res & (1 << 5))) {
        req_interrupt = true;
    }
    // directional buttons
    else if (key <= 3 && !(res & (1 << 4))) {
        req_interrupt = true;
    }

    if (req_interrupt && !previously_unset) {
        request_interrupt(INTERRUPT_JOYPAD);
    }
};

void Emulator::key_released(int key) {
    joypad_state |= (1 << key);
};


/* Graphics */

void Emulator::update_graphics() {
    set_lcd_status();

    if (!ppu->get_lcd_display_enable()) {
        return;
    }
 
    clock_count -= cpu->last_clock;

    if (clock_count <= 0) {
        byte curr_line = ++(*line);
        printf("curr_line : %d\n", curr_line);

        clock_count = 456;

        if (curr_line == 144) {
            request_interrupt(INTERRUPT_VBLANK);
        } else if (curr_line > 153) {
            // V-BLANK area
            *line = 0;
        } else if (curr_line < 144) {
            ppu->render_line();
        }
    }
};

void Emulator::set_lcd_status() {
    if (!ppu->get_lcd_display_enable()) {
        // set the mode to 1 during lcd disabled and reset scanline
        clock_count = 456;
        *line = 0;
        *lcd_status &= 252;
        ppu->set_mode(1);
        return;
    }
    byte curr_line = *line;
    byte last_mode = ppu->get_mode();

    bool req_interrupt = false;

    if (curr_line >= 144) {
        // V-BLANK area
        ppu->set_mode(1);
        req_interrupt = *lcd_status & 0x10;
    } else {
        int mode2bounds = 456 - 80;
        int mode3bounds = mode2bounds - 172;

        if (clock_count >= mode2bounds) {
            ppu->set_mode(2);
            req_interrupt = *lcd_status & 0x20;
        }
        else if (clock_count >= mode3bounds) {
            ppu->set_mode(3);
        }
        else {
            ppu->set_mode(0);
            req_interrupt = *lcd_status & 0x08;
        }
    }

    // request interrupt if mode is different
    if (req_interrupt && (ppu->get_mode() != last_mode)) {
        request_interrupt(INTERRUPT_LCDC);
    }
    
    if (curr_line == mmu->read_memory(0xFF45)) {
        *lcd_status |= 0x04;
        if (*lcd_status & 0x40) {
            // bit 6
            request_interrupt(INTERRUPT_LCDC);
        }
    } else {
        *lcd_status &= ~0x04;
    }
};


/* Timers */


void Emulator::update_timers() {
    
    divider_counter += cpu->last_clock;

    if (divider_counter >= 256) {
        divider_counter = 0;
        mmu->address[0xFF04]++;
    }

    // check if clock enabled
    if (mmu->read_memory(0xFF07) & (1 << 2)) {
        time_counter -= cpu->last_clock;

        // enough Cpu clock cycles have happened to update the timer
        if (time_counter <= 0) {
            switch (mmu->read_memory(0xFF07) & 0x3) {
                case 0:
                    time_counter = 1024;
                    break;  // freq 4096
                case 1:
                    time_counter = 16;
                    break;  // freq 262144
                case 2:
                    time_counter = 64;
                    break;  // freq 65536
                case 3:
                    time_counter = 256;
                    break;  // freq 16382
            }

            mmu->address[0xFF05]++;

            // overflow
            if (mmu->address[0xFF05] == 0) {
                mmu->address[0xFF05] = mmu->read_memory(0xFF06);
                request_interrupt(INTERRUPT_TIMER);
            }
        }
    }
};
