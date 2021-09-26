#ifndef TYPES_H
#define TYPES_H

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <vector>

typedef unsigned char byte;
typedef unsigned short word;

#define INTERRUPT_VBLANK 0
#define INTERRUPT_LCDC	 1
#define INTERRUPT_TIMER	 2
#define INTERRUPT_SERIAL 3
#define INTERRUPT_JOYPAD 4


void set_bit(byte *data, byte bit, bool value);
bool get_bit(byte *data, byte bit);


class PairRegister {

	private:
		byte *hi;
		byte *lo;

	public:
		PairRegister(byte *hi, byte *lo);
		byte high();
		byte low();
		void high(byte value);
		void low(byte value);
		void set(word value);
		void set(byte hi, byte lo);
		word get();

		word operator ++ ();
		word operator -- ();
		word operator ++ (int);
		word operator -- (int);
};


class MemoryRegister {

	private:
		byte *data;
		word addr;

	public:
		MemoryRegister();
		MemoryRegister(byte *p, word addr);
		byte get();
		void set(byte value);
		void set_bit(byte bit, bool value);
		bool get_bit(byte bit);
		word address();

		byte operator ++ ();
		byte operator -- ();
		byte operator ++ (int);
		byte operator -- (int);
		void operator &= (byte value);
		void operator |= (byte value);
};

/*
void set_bit(byte* target, byte bit, bool value) {
	*target = (*target & ~(1 << bit)) | (value << bit);
}
bool get_bit(byte* target, byte bit) {
	return *target & (1 << bit);
}
*/

#endif
