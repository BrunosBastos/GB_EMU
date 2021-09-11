#include <SDL2/SDL.h>

#include "cartridge.h"
#include "cpu.h"
#include "mmu.h"
#include "ppu.h"
#include "opcodes.h"

SDL_Renderer *renderer;

void sdl_init() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window =
        SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         800, 600, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);
}

void change_color(int color) {
    if (color == WHITE) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    } else if (color == L_GRAY) {
        SDL_SetRenderDrawColor(renderer, 0xCC, 0xCC, 0xCC, 255);
    } else if (color == D_GRAY) {
        SDL_SetRenderDrawColor(renderer, 0x77, 0x77, 0x77, 255);
    } else if (color == BLACK) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
}

void update_screen(ppu *p) {
    for (int x = 0; x < PPU_BUFFER_WIDTH; x++) {
        for (int y = 0; y < PPU_BUFFER_HEIGHT; y++) {
            change_color(p->buffer[x][y]);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

int main() {
    sdl_init();
    SDL_Event event;

    initialize_optable();

    cartridge *c = new cartridge();
    c->cartridge_load("./roms/tetris.gb");
    mmu *m = new mmu();
    m->load_rom(c);

    cpu *cp = new cpu();
    cp->initialize(m);
    ppu *p = new ppu();
    p->initialize(m, cp);

    bool running = true;
    while (running) {
        cp->emulate_cycle();
        p->update_graphics();
        update_screen(p);
        int startMs = SDL_GetTicks();

        // if(draw && myChip8.drawFlag) {
        //    drawGraphics();
        //}

        while (SDL_PollEvent(&event)) {  // poll until all events are handled!
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        int endMs = SDL_GetTicks();
        SDL_Delay(10 - (endMs - startMs));
    }

    return 0;
}