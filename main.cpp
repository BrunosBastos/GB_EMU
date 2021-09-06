#include "mmu.h"
#include "cartridge.h"
#include "cpu.h"

int main() {

    cartridge *c = new cartridge();
    c->cartridge_load("./tetris.gb");
    //c.print(0x104, 1000);
    mmu *m = new mmu();
    m->load_rom(c);
    
    cpu *cp = new cpu();
    cp->initialize(m);
    for(int i=0; i< 100; i++)
        cp->emulate_cycle();

    return 0;
}