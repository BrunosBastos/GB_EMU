#include "mmu.h"
#include <cstring>

void mmu::load_rom(cartridge *c) { 
    printf("in load");
    cart = c;
    memcpy(address, c->rom, 0x8000);
	current_rom_bank = 1;
    printf("out load");
};
