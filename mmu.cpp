#include "mmu.h"
#include <cstring>

void mmu::load_rom(cartridge *c) {
    memcpy(address, c->rom, c->size);
};

byte mmu::read_memory(int addr) {
    return address[addr];
};

void mmu::write_memory(int addr, byte value) {
    address[addr] = value;
};
