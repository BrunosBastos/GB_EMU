#include "mmu.h"
#include <cstring>

void mmu::load_rom(cartridge *c) {
    memcpy(address, c->rom, c->size);
}



