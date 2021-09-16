#include "cartridge.h"
#include <string.h>

void cartridge::cartridge_load(const char* filename) {
    printf("in cartridge\n");
    
    FILE *file = NULL;
    file = fopen(filename, "rb");
    
    if(file) {
        fseek(file, 0, SEEK_END);
        uint32_t total = ftell(file);
        fseek(file, 0, SEEK_SET);
        if(total > 0) {
            rom = (uint8_t*)malloc(sizeof(uint8_t) * total);
            size = total;
            if(fread(rom, 1, total, file) != total) {
                free(rom);
                fclose(file);
            }
            title = strdup(filename);
        }
        fclose(file);
    } 
};

void cartridge::cartridge_free() {
    free(title);
    free(rom);
    free(this);
};

void cartridge::print(int s, int e) {

    for(int i=0; i < e-s; i++) {
        printf("%02x ", rom[s + i]);
    }
    printf("\n");    
};
