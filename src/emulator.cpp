#include "emulator.h"

Emulator::Emulator(std::string *filename) {
    reset(filename);
};

void Emulator::reset(std::string *filename) {
    Cartridge *c = new Cartridge(*filename);
    mmu = new Mmu(c);
    cpu = new Cpu(mmu);
    ppu = new Ppu(mmu);
}

void Emulator::run() {
    cpu->emulate_cycle();
    update_timers();
    update_graphics();
    execute_interrupts();
};

void Emulator::request_interrupt(int id) {
    mmu->write_memory(mmu->IF.address(), mmu->read_memory(mmu->IF.address()) | (1 << id));
};

void Emulator::execute_interrupts() {
    byte req = mmu->IF.get();
    byte enabled = mmu->IE.get();

    /*
    if interrupt_master is enabled when halt is called 
    the cpu leaves halt state when an interrupt occurs

    if interrupt_master is disabled there are 2 possibilities
        if not interrupt is pending when halt is called
        the cpu leaves halt normally when an interrupt occurs
        but it does not service that interrupt because interrupt_master is disabled

        if an interrupt is already pending the halt leaves immediatly
        but triggers the "halt bug"

    */
    
    if (cpu->halted) {
        if (req & enabled & 0x1F) {
            cpu->halted = false;
        }
    }
    
    if (cpu->interrupt_master) {

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
    mmu->write_memory(mmu->IF.address(), mmu->read_memory(mmu->IF.address()) & ~(1 << id));

    /* 
    store_pc_stack is made so that it increases the pc for you,
    however, in this case, the pc was already incremented in the cpu
    so in order for the return of the interrupt to be correct
    it needs to be decrease here
    */

    cpu->pc--;
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

    if (!(mmu->joypad_state & (1 << key))) {
        previously_unset = true;
    }

    mmu->joypad_state &= ~(1 << key);

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
    mmu->joypad_state |= (1 << key);
};

/* Graphics */

// https://gbdev.io/pandocs/LCDC.html

void Emulator::update_graphics() {
    set_lcd_status();

    if (!ppu->get_lcd_display_enable()) {
        return;
    }

    clock_count -= cpu->last_clock;

    if (clock_count <= 0) {
        byte curr_line = ++mmu->LY;
        clock_count += 114;

        if (curr_line == 144) {
            request_interrupt(INTERRUPT_VBLANK);
        } else if (curr_line > 153) {
            // V-BLANK area
            mmu->LY.set(0);
        } else if (curr_line < 144) {
            ppu->render_line();
        }
    }
};

void Emulator::set_lcd_status() {
    if (!ppu->get_lcd_display_enable()) {
        // set the mode to 1 during lcd disabled and reset scanline
        clock_count = 114;
        mmu->LY.set(0);
        ppu->set_mode(1);
        return;
    }
    const byte last_mode = ppu->get_mode();

    bool req_interrupt = false;

    if (mmu->LY.get() >= 144) {
        // V-BLANK area
        ppu->set_mode(1);
        req_interrupt = mmu->STAT.get() & 0x10;
    } else {
        constexpr int mode2bounds = 114 - 20;
        constexpr int mode3bounds = mode2bounds - 43;

        if (clock_count >= mode2bounds) {
            ppu->set_mode(2);
            req_interrupt = mmu->STAT.get() & 0x20;
        } else if (clock_count >= mode3bounds) {
            ppu->set_mode(3);
        } else {
            ppu->set_mode(0);
            req_interrupt = mmu->STAT.get() & 0x08;
        }
    }

    // request interrupt
    if (req_interrupt && (ppu->get_mode() != last_mode)) {
        request_interrupt(INTERRUPT_LCDC);
    }

    if (mmu->LY.get() == mmu->LYC.get()) {
        mmu->STAT |= 0x04;  // set bit 2 if the LY == LYC
        if (mmu->STAT.get() & 0x40) {
            request_interrupt(INTERRUPT_LCDC);
        }
    } else {
        mmu->STAT &= ~0x04;  // reset bit 2 if LY != LYC
    }
};

/* Timers */

/*

// NB: This is the source of a very common bug in timer implementations.
//
// Here, we need to increment the timer's internal counter relative to the tick size. The
// counter may have to be incremented multiple times for a given tick. While this
// technically could happen for the div internal counter, in practice it doesn't: no
// instruction takes longer to execute than it takes to increment DIV once. However, it
// _is_ possible to have the timer internal counter increment multiple times during a given
// instruction.
//
// Notably, getting this wrong will cause blargg's instr_timing test ROM to fail with
// the cryptic "Failure #255" message.

while self.timer_counter >= threshold {
    self.timer_counter -= threshold;

    let (counter, overflow) = match self.reg.counter.checked_add(1) {
        Some(counter) => (counter, false),
        None => (self.reg.modulo, true),
    };

    self.reg.counter = counter;

    if overflow {
        *interrupt_requested = true;
    }
}

*/

// https://github.com/feo-boy/feo-boy/blob/master/src/bus/timer.rs#L56-L81
void Emulator::update_timers() {
    divider_counter += cpu->last_clock * 4;

    if (divider_counter >= 256) {
        divider_counter = 0;
        mmu->DIV++;
    }

    // check if clock enabled
    if (mmu->TAC.get() & (1 << 2)) {
        time_counter -= cpu->last_clock * 4;

        // enough Cpu clock cycles have happened to update the timer
        if (time_counter <= 0) {
            switch (mmu->TAC.get() & 0x3) {
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

            mmu->TIMA++;

            // overflow
            if (mmu->TIMA.get() == 0) {
                mmu->TIMA.set(mmu->TMA.get());
                request_interrupt(INTERRUPT_TIMER);
            }
        }
    }
};
