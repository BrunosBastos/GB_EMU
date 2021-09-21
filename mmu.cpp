#include "mmu.h"
#include <cstring>

Mmu::Mmu(Cartridge *c) { 
    memcpy(address, c->rom, 0x8000);
    joypad_state = 0xFF;

	// Assign memory controller based on cartridge specification
	switch (address[0x0147])
	{
		case 0x01:
		case 0x02:
		case 0x03:
			mbc = new MemoryController1();
			break;
		case 0x05:
		case 0x06:
			mbc = new MemoryController2();
			break;
		case 0x0F:
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
			mbc = new MemoryController3();
			break;
		default:
			mbc = new MemoryController0();
			break;
	}

};

byte Mmu::read_memory(word addr) {
    // reading from rom bank
    if (addr >= 0x4000 && addr <= 0x7FFF) {
        unsigned int new_Address = addr;
        new_Address += ((current_rom_bank - 1) * 0x4000);
        return cart->rom[new_Address];
    }
    // reading from RAM Bank
    else if (addr >= 0xA000 && addr <= 0xBFFF) {
        // WORD new_Address = addr - 0xA000;
        // return m_RamBank.at(current_ram_bank)[new_Address];
    }
    // trying to read joypad state
    else if (addr == 0xFF00)
        return get_joypad_state();

    return address[addr];
};

byte Mmu::get_joypad_state() {
    byte res = address[0xFF00] ^ 0xFF;

    // standard buttons
    if (!(res & (1 << 4))) {
        res &= ((joypad_state >> 4) | 0xF0);
    }
    // directional buttons
    else if (!(res & (1 << 5))) {
        res &= ((joypad_state & 0xF) | 0xF0);
    }
    return res;
}


void Mmu::write_memory(word addr, byte data) {
    // writing to memory addr 0x0 to 0x1FFF this disables writing to the ram
    // bank. 0 disables, 0xA enables
    if (addr <= 0x1FFF) {
        if (mbc1) {
            if ((data & 0xF) == 0xA)
                enable_ram_bank = true;
            else if (data == 0x0)
                enable_ram_bank = false;
        } else if (mbc2) {
            // bit 0 of upper byte must be 0
            if (!(addr & 0x10)) {
                if ((data & 0xF) == 0xA)
                    enable_ram_bank = true;
                else if (data == 0x0)
                    enable_ram_bank = false;
            }
        }
    }

    // if writing to a memory addr between 2000 and 3FFF then we need to
    // change rom bank
    else if ((addr >= 0x2000) && (addr <= 0x3FFF)) {
        if (mbc1) {
            if (data == 0x00) data++;

            data &= 31;

            // Turn off the lower 5-bits.
            current_rom_bank &= 224;

            // Combine the written data with the register.
            current_rom_bank |= data;

            printf("Changing Rom Bank to %d", current_rom_bank);
        } else if (mbc2) {
            data &= 0xF;
            current_rom_bank = data;
        }
    }

    // writing to addr 0x4000 to 0x5FFF switches ram banks (if enabled of
    // course)
    else if ((addr >= 0x4000) && (addr <= 0x5FFF)) {
        if (mbc1) {
            // are we using memory model 16/8
            if (using16_8_model) {
                // in this mode we can only use Ram Bank 0
                current_ram_bank = 0;

                data &= 3;
                data <<= 5;

                if ((current_rom_bank & 31) == 0) {
                    data++;
                }

                // Turn off bits 5 and 6, and 7 if it somehow got turned on.
                current_rom_bank &= 31;

                // Combine the written data with the register.
                current_rom_bank |= data;

                printf("Changing Rom Bank to %d", current_rom_bank);
            } else {
                current_ram_bank = data & 0x3;
                printf("=====Changing Ram Bank to %d=====", current_ram_bank);
            }
        }
    }

    // writing to addr 0x6000 to 0x7FFF switches memory model
    else if ((addr >= 0x6000) && (addr <= 0x7FFF)) {
        if (mbc1) {
            // we're only interested in the first bit
            data &= 1;
            if (data == 1) {
                current_ram_bank = 0;
                using16_8_model = false;
            } else
                using16_8_model = true;
        }
    }

    // from now on we're writing to RAM

    else if ((addr >= 0xA000) && (addr <= 0xBFFF)) {
        if (enable_ram_bank) {
            if (mbc1) {
                word new_addr = addr - 0xA000;
                memory->ram_banks.at(current_ram_bank)[new_addr] = data;
            }
        } else if (mbc2 && (addr < 0xA200)) {
            word new_addr = addr - 0xA000;
            memory->ram_banks.at(current_ram_bank)[new_addr] = data;
        }

    }

    // we're right to internal RAM, remember that it needs to echo it
    else if ((addr >= 0xC000) && (addr <= 0xDFFF)) {
        address[addr] = data;
    }

    // echo memory. Writes here and into the internal ram. Same as above
    else if ((addr >= 0xE000) && (addr <= 0xFDFF)) {
        address[addr] = data;
        address[addr - 0x2000] = data;  // echo data into ram addr
    }

    // This area is restricted.
    else if ((addr >= 0xFEA0) && (addr <= 0xFEFF)) {
    }

    // reset the divider register
    else if (addr == 0xFF04) {
        address[0xFF04] = 0;
        divider_counter = 0;
    }

    // not sure if this is correct
    else if (addr == 0xFF07) {
        address[addr] = data;

        int timerVal = data & 0x03;

        int clockSpeed = 0;

        switch (timerVal) {
            case 0:
                clockSpeed = 1024;
                break;
            case 1:
                clockSpeed = 16;
                break;
            case 2:
                clockSpeed = 64;
                break;
            case 3:
                clockSpeed = 256;
                break;  // 256
            default:
                assert(false);
                break;  // weird timer val
        }

        if (clockSpeed != current_clock_speed) {
            time_counter = 0;
            current_clock_speed = clockSpeed;
        }
    }

    // line
    else if (addr == 0xFF44) {
        address[0xFF44] = 0;
    }

    else if (addr == 0xFF45) {
        address[addr] = data;
    }
    // DMA transfer
    else if (addr == 0xFF46) {
        word new_addr = (data << 8);
        for (int i = 0; i < 0xA0; i++) {
            address[0xFE00 + i] = read_memory(new_addr + i);
        }
    }

    // This area is restricted.
    else if ((addr >= 0xFF4C) && (addr <= 0xFF7F)) {
    }

    else {
        address[addr] = data;
    }
};
