#include "mmu.h"
#include <cstring>


Mmu::Mmu(Cartridge *c) { 

    joypad_state = 0xFF;

    address = c->rom;
	// Assign memory controller based on cartridge specification
	switch (address[0x0147]) {
		case 0x01:
		case 0x02:
		case 0x03:
			mbc = new MemoryController1(c);
			break;
		case 0x05:
		case 0x06:
			mbc = new MemoryController2(c);
			break;
		case 0x0F:
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
			mbc = new MemoryController3(c);
			break;
		default:
			mbc = new MemoryController0(c);
			break;
	}

    address[0xFF05] = 0x00;  // TIMA
    address[0xFF06] = 0x00;  // TMA
    address[0xFF07] = 0x00;  // TAC
    //address[0xFF0F] = 0xE1;  // FIXME: IF
    address[0xFF10] = 0x80;  // NR10
    address[0xFF11] = 0xBF;  // NR11
    address[0xFF12] = 0xF3;  // NR12
    address[0xFF14] = 0xBF;  // NR14
    address[0xFF16] = 0x3F;  // NR21
    address[0xFF17] = 0x00;  // NR22
    address[0xFF19] = 0xBF;  // NR24
    address[0xFF1A] = 0x7F;  // NR30
    address[0xFF1B] = 0xFF;  // NR31
    address[0xFF1C] = 0x9F;  // NR32
    address[0xFF1E] = 0xBF;  // NR33
    address[0xFF20] = 0xFF;  // NR41
    address[0xFF21] = 0x00;  // NR42
    address[0xFF22] = 0x00;  // NR43
    address[0xFF23] = 0xBF;  // NR30
    address[0xFF24] = 0x77;  // NR50
    address[0xFF25] = 0xF3;  // NR51
    address[0xFF26] = 0xF1;  // GB
    address[0xFF40] = 0x91;  // LCDC
    address[0xFF42] = 0x00;  // SCY
    address[0xFF43] = 0x00;  // SCX
    address[0xFF45] = 0x00;  // LYC
    address[0xFF47] = 0xFC;  // BGP
    address[0xFF48] = 0xFF;  // OBP0
    address[0xFF49] = 0xFF;  // OBP1
    address[0xFF4A] = 0x00;  // WY
    address[0xFF4B] = 0x00;  // WX
    address[0xFFFF] = 0x00;  // IE


    P1   = MemoryRegister(&address[0xFF00], 0xFF00);
	DIV  = MemoryRegister(&address[0xFF04], 0xFF04);
	TIMA = MemoryRegister(&address[0xFF05], 0xFF05);
	TMA  = MemoryRegister(&address[0xFF06], 0xFF06);
	TAC  = MemoryRegister(&address[0xFF07], 0xFF07);
	LCDC = MemoryRegister(&address[0xFF40], 0xFF40);
	STAT = MemoryRegister(&address[0xFF41], 0xFF41);
	SCY  = MemoryRegister(&address[0xFF42], 0xFF42);
	SCX  = MemoryRegister(&address[0xFF43], 0xFF43);
	LY   = MemoryRegister(&address[0xFF44], 0xFF44);
	LYC  = MemoryRegister(&address[0xFF45], 0xFF45);
	DMA  = MemoryRegister(&address[0xFF46], 0xFF46);
	BGP  = MemoryRegister(&address[0xFF47], 0xFF47);
	OBP0 = MemoryRegister(&address[0xFF48], 0xFF48);
	OBP1 = MemoryRegister(&address[0xFF49], 0xFF49);
	WY   = MemoryRegister(&address[0xFF4A], 0xFF4A);
	WX   = MemoryRegister(&address[0xFF4B], 0xFF4B);
	IF   = MemoryRegister(&address[0xFF0F], 0xFF0F);
	IE   = MemoryRegister(&address[0xFFFF], 0xFFFF);

};

byte Mmu::read_memory(word addr) {
    // reading from rom bank
    if (addr >= 0x4000 && addr <= 0x7FFF) {
        //return mbc->read(addr);
        return address[addr];
    }

    // reading from RAM Bank
    else if (addr >= 0xA000 && addr <= 0xBFFF) {
        return mbc->read(addr);
    }

    // joypad state
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
};

void Mmu::write_memory(word addr, byte data) {
    
    if (addr >= 0x0000 && addr <= 0xBFFF) {
        mbc->write(addr, data);
    }
    // internal ram
    else if ((addr >= 0xC000) && (addr <= 0xDE00)) {
        address[addr] = data;
        address[addr + 0x2000] = data;
    }
    else if ((addr > 0xDE00) && (addr <= 0xDFFF)) {
        address[addr] = data;       // does not echo to echo ram
    }
    // echo ram
    else if ((addr >= 0xE000) && (addr <= 0xFDFF)) {
        address[addr] = data;
        address[addr - 0x2000] = data;  // echo data into ram addr
    }

    // This area is restricted.
    else if ((addr >= 0xFEA0) && (addr <= 0xFEFF)) {
    }

    // reset the divider register
    else if (addr == 0xFF04) {
        DIV.set(0);
        // address[0xFF04] = 0;
    }

    else if (addr == 0xFF07) {

        if (TAC.get() != data & 0x03) {
            TIMA.set(0);
        }
        TAC.set(data);
    }

    // line
    else if (addr == 0xFF44) {
        LY.set(0);
    }

    else if (addr == 0xFF45) {
        LYC.set(data);
    }
    // DMA transfer
    else if (addr == 0xFF46) {
        DMA.set(data);
        word new_addr = (data << 8);
        for (int i = 0; i < 0xA0; i++) {
            write_memory(0xFE00 + i, read_memory(new_addr + i));
        }
    }

    // This area is restricted.
    else if ((addr >= 0xFF4C) && (addr <= 0xFF7F)) {
    }

    else {
        address[addr] = data;
    }
};
