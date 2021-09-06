#ifndef _CARTRIDGE_H_
#define _CARTRIDGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "types.h"

class cartridge {
    
    public:
        char* title;
        byte* rom;
        uint32_t size;    

        void cartridge_load(const char* filename);
        void cartridge_free();
        void print(int s, int e);
};

#endif