#ifndef MBC_H
#define MBC_H

#include "cartridge.h"
#include "types.h"

class MemoryController {
   protected:
    Cartridge* cart;
    std::vector<byte*> ram_banks;

    byte curr_rom_bank = 1;
    byte curr_ram_bank = 0;

    bool enable_ram_bank = false;
    bool enable_ram_access = false;

    // Mode selector
    byte mode = 0;
    const byte MODE_ROM = 0;
    const byte MODE_RAM = 1;

   public:
    MemoryController(Cartridge *cart);
    virtual byte read(word location) = 0;
    virtual void write(word location, byte data) = 0;

    // Save states
    std::vector<byte*> get_ram();
    void set_ram(std::vector<byte*> data);
    // virtual void save_state(ofstream &file);
    // virtual void load_state(ifstream &file);
};

// This class represents games that only use the exact 32kB of cartridge space
class MemoryController0 : public MemoryController {

    byte read(word location);
    void write(word location, byte data);
    
    public:
        MemoryController0(Cartridge *cart);
};

// MBC1 (max 2Mbyte ROM and/or 32Kbyte RAM)
class MemoryController1 : public MemoryController {

    bool model16_8 = true;
    byte read(word location);
    void write(word location, byte data);
    //void save_state(ofstream &file);
    //void load_state(ifstream &file);
    public:
        MemoryController1(Cartridge *cart);
};

// MBC2 (max 256Kbyte ROM and 512x4 bits RAM)
class MemoryController2 : public MemoryController {
    byte read(word location);
    void write(word location, byte data);

    public:
        MemoryController2(Cartridge *cart);
};

// MBC3(max 2Mbyte ROM and / or 32Kbyte RAM and Timer)
class MemoryController3 : public MemoryController {
    bool RTC_enabled = false;

    byte read(word locatison);
    void write(word location, byte data);
    //void save_state(ofstream &file);
    //void load_state(ifstream &file);

    public:
        MemoryController3(Cartridge *cart);
};

#endif
