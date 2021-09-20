#include <vector>
#include <stdio.h>

typedef unsigned char byte;
typedef unsigned short word;

#define INTERRUPT_VBLANK 0
#define INTERRUPT_LCDC	 1
#define INTERRUPT_TIMER	 2
#define INTERRUPT_SERIAL 3
#define INTERRUPT_JOYPAD 4

/*
void set_bit(byte* target, byte bit, bool value) {
	*target = (*target & ~(1 << bit)) | (value << bit);
}
bool get_bit(byte* target, byte bit) {
	return *target & (1 << bit);
}
*/
