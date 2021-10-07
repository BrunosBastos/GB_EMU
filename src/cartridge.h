#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "types.h"

class Cartridge {
    
    public:
        char* title;
        byte* rom;
        uint32_t size;    

        Cartridge(const char *filename);

        void cartridge_free();
        void print(int s, int e);
};

#endif
