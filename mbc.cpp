#include "mbc.h"

MemoryController::MemoryController(Cartridge *cart) {
    this->cart = cart;
}

std::vector<byte*> MemoryController::get_ram() {
    return ram_banks;
}

void MemoryController::set_ram(std::vector<byte*> data) {
    ram_banks = data;
}

/*
void MemoryController::save_state(ofstream &file) {
    cout << "did nothing" << endl;
}
void MemoryController::load_state(ifstream &file) {
    cout << "did nothing" << endl;
}
*/

/*
	MC0 represents games that use exactly 32kB of space
	and don't have memory controllers
*/
byte MemoryController0::read(word addr) {

    if (addr >= 0 && addr <= 0x7FFF) 
        return cart->rom[addr];
    // read value from current ram bank
    else if (addr >= 0xA000 && addr <= 0xBFFF)
        return ram_banks.at(curr_ram_bank)[addr & 0x1FFF];
   
    return 0;
};

void MemoryController0::write(word addr, byte data) {
    if (addr >= 0xA000 && addr <= 0xBFFF)
        ram_banks.at(curr_ram_bank)[addr & 0x1FFF] = data;
};

/*
	Memory Controller 1
*/
byte MemoryController1::read(word addr) {
    
    if (addr >= 0x0000 && addr <= 0x3FFF) {
        return cart->rom[addr];
    }
    else if (addr >= 0x4000 && addr <= 0x7FFF) {
        int newaddr = ((curr_rom_bank - 1) * 0x4000) + addr;
        return cart->rom[newaddr];
    }    
    else if (addr >= 0xA000 && addr <= 0xBFFF) {
        if (!enable_ram_access)
            return 0xFF;

        // ram bank 0 is the only that can be used when ram is not enable
        return ram_banks.at(enable_ram_bank ? curr_ram_bank : 0)[addr - 0xA000];
    }
};

void MemoryController1::write(word addr, byte data) {
    
    // Enable RAM
    if (addr >= 0x0000 && addr <= 0x1FFF) {
        // 0x0A to enable and the rest to disable
        enable_ram_access = (data & 0xF) == 0xA;
    }
    // ROM bank id low bits select (write only)
    else if (addr >= 0x2000 && addr <= 0x3FFF) {

        // values of 0 and 1 point to rom bank 1
        if (data == 0x00) data++;

        data &= 0x1F; 

        // clear the lower 5 bits
        curr_rom_bank &= 0xE0;

        // change curr_bank
        curr_rom_bank |= data & 0x1F;
    }
    // RAM bank id, or upper bits of ROM bank id
    else if (addr >= 0x4000 && addr <= 0x5FFF) {

        if (model16_8) {
            // current_ram_bank = 0; FIXME: this is prob incorrect

            // sets 2 most significant bits of rom bank
            curr_rom_bank &= 0x1F;

            // 0s and 1s are equivalent
            if (curr_rom_bank == 0) {
                curr_rom_bank++;
            }

            curr_rom_bank |= (data & 3) << 5;
        }
        else {
            curr_ram_bank = data & 0x03;
        }
    }
    // Bank selector
    else if (addr >= 0x6000 && addr <= 0x7FFF) {
        model16_8 = !get_bit(&data, 0);
        // if (!model16_8) current_ram_bank = 0; FIXME: this is prob incorrect
    }
    
    // writing to RAM
    else if (addr >= 0xA000 && addr <= 0xBFFF) {
        if (enable_ram_access) {
            ram_banks.at(curr_ram_bank)[addr - 0xA000] = data;
        }
    }
};

/*
void MemoryController1::save_state(ofstream &file) {
    file.write((char *)&curr_rom_bank, sizeof(curr_rom_bank));
    file.write((char *)&curr_ram_bank, sizeof(curr_ram_bank));
    file.write((char *)&enable_ram_bank, sizeof(enable_ram_bank));
    file.write((char *)&enable_ram_access, sizeof(enable_ram_access));
    file.write((char *)&mode, sizeof(mode));

    cout << "wrote registers" << endl;
};

void MemoryController1::load_state(ifstream &file) {
    file.read((char *)&curr_rom_bank, sizeof(curr_rom_bank));
    file.read((char *)&curr_ram_bank, sizeof(curr_ram_bank));
    file.read((char *)&enable_ram_bank, sizeof(enable_ram_bank));
    file.read((char *)&enable_ram_access, sizeof(enable_ram_access));
    file.read((char *)&mode, sizeof(mode));
    cout << "read registers" << endl;
};
*/

/*
	Memory Controller 2
*/
byte MemoryController2::read(word addr) { return 0; };
void MemoryController2::write(word addr, byte data) {};

/*
	Memory Controller 3
*/
byte MemoryController3::read(word addr) {
    // ROM bank 0 (read only)
    if (addr >= 0x0000 && addr <= 0x3FFF) {
        return cart->rom[addr];
    }
    // ROM banks 01-7F (read only)
    else if (addr >= 0x4000 && addr <= 0x7FFF) {
        int newaddr = ((curr_rom_bank - 1) * 0x4000) + addr;
        return cart->rom[newaddr];
    }
    // RAM banks 00 - 03, if any (read/write)
    else if (addr >= 0xA000 && addr <= 0xBFFF) {
        if (RTC_enabled)
            return 0x00;

        if (!enable_ram_access)
            return 0xFF;

        return ram_banks.at(curr_ram_bank)[addr - 0xA000];
    }
};

void MemoryController3::write(word addr, byte data) {
    
    // https://gbdev.gg8.se/wiki/articles/MBC3

    if (addr >= 0x0000 && addr <= 0x1FFF) {
        enable_ram_access = (data & 0xF) == 0xA;
        RTC_enabled = enable_ram_access;
    } 
    else if (addr >= 0x2000 && addr <= 0x3FFF) {
        curr_rom_bank = data & 0x7F;

        if (curr_rom_bank == 0)
            curr_rom_bank++;
    } 
    else if (addr >= 0x4000 && addr <= 0x5FFF) {
        // RAM bank
        if (data <= 0x3) {
            RTC_enabled = false;
            curr_ram_bank = data;
        }
        // RTC mapped
        else if (data >= 0x08 && data <= 0x0C) {
            RTC_enabled = true;
        }
    } else if (addr >= 0x6000 && addr <= 0x7FFF) {
        // TODO: Latch clock data
    } else if (addr >= 0xA000 && addr <= 0xBFFF) {
        // writing to RAM
        if (!RTC_enabled) {
            if (!enable_ram_access)
                return;

            ram_banks.at(curr_ram_bank)[addr - 0xA000] = data;
        } else {
            // TODO: RTC writing
        }
    }
};
/*
void MemoryController3::save_state(ofstream &file) {
    file.write((char *)&curr_rom_bank, sizeof(curr_rom_bank));
    file.write((char *)&curr_ram_bank, sizeof(curr_ram_bank));
    file.write((char *)&enable_ram_bank, sizeof(enable_ram_bank));
    file.write((char *)&enable_ram_access, sizeof(enable_ram_access));
    file.write((char *)&mode, sizeof(mode));
    file.write((char *)&RTC_enabled, sizeof(RTC_enabled));
    cout << "wrote registers" << endl;
};

void MemoryController3::load_state(ifstream &file) {
    file.read((char *)&curr_rom_bank, sizeof(curr_rom_bank));
    file.read((char *)&curr_ram_bank, sizeof(curr_ram_bank));
    file.read((char *)&enable_ram_bank, sizeof(enable_ram_bank));
    file.read((char *)&enable_ram_access, sizeof(enable_ram_access));
    file.read((char *)&mode, sizeof(mode));
    file.read((char *)&RTC_enabled, sizeof(RTC_enabled));
    cout << "read registers" << endl;
};
*/
