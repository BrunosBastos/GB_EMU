#include <vector>
#include <stdio.h>

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

		PairRegister operator ++ ();
		PairRegister operator -- ();
};


class MemoryRegister {

	private:
		byte *data;

	public:
		MemoryRegister(byte *addr);
		byte get();
		void set(byte value);
		void set_bit(byte bit, bool value);
		bool get_bit(byte bit);
};

/*
void set_bit(byte* target, byte bit, bool value) {
	*target = (*target & ~(1 << bit)) | (value << bit);
}
bool get_bit(byte* target, byte bit) {
	return *target & (1 << bit);
}
*/
