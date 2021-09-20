#include <SDL2/SDL.h>

#include "cartridge.h"
#include "cpu.h"
#include "mmu.h"
#include "opcodes.h"
#include "ppu.h"

SDL_Renderer *renderer;

#define debug 0

void sdl_init() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window =
        SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         800, 600, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);
};

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
};

void update_screen(ppu *p) {
    for (int x = 0; x < PPU_BUFFER_WIDTH; x++) {
        for (int y = 0; y < PPU_BUFFER_HEIGHT; y++) {
            change_color(p->buffer[x][y]);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
};

void handle_input(cpu* cp, SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        printf("Input \n");
        int key = -1;
        switch (event.key.keysym.sym) {
            case SDLK_a:
                key = 4;
                break;
            case SDLK_s:
                key = 5;
                break;
            case SDLK_RETURN:
                key = 7;
                break;
            case SDLK_SPACE:
                key = 6;
                break;
            case SDLK_RIGHT:
                key = 0;
                break;
            case SDLK_LEFT:
                key = 1;
                break;
            case SDLK_UP:
                key = 2;
                break;
            case SDLK_DOWN:
                key = 3;
                break;
        }
        if (key != -1) {
            cp->key_pressed(key);
        }
    }
    // If a key was released
    else if (event.type == SDL_KEYUP) {
        int key = -1;
        switch (event.key.keysym.sym) {
            case SDLK_a:
                key = 4;
                break;
            case SDLK_s:
                key = 5;
                break;
            case SDLK_RETURN:
                key = 7;
                break;
            case SDLK_SPACE:
                key = 6;
                break;
            case SDLK_RIGHT:
                key = 0;
                break;
            case SDLK_LEFT:
                key = 1;
                break;
            case SDLK_UP:
                key = 2;
                break;
            case SDLK_DOWN:
                key = 3;
                break;
        }
        if (key != -1) {
            cp->key_released(key);
        }
    }
};

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
        // for(int i=0; i < 200; i++) {
        // printf("--------- %i ---------\n", i);
        cp->emulate_cycle();
        p->update_graphics();
        update_screen(p);
        cp->execute_interrupts();
        int startMs = SDL_GetTicks();

        char str[7];
        while (debug) {
            scanf("%s", str);
            if (strcmp("c", str) == 0) {
                break;
            } else if (strcmp("e", str) == 0) {
                exit(0);
            } else {
                printf("[%04s]: %02x\n", str,
                       m->address[strtol(str, NULL, 16)]);
            }
        }

        while (SDL_PollEvent(&event)) { 
            handle_input(cp, event);
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        int endMs = SDL_GetTicks();
        SDL_Delay(60 - (endMs - startMs));
    }
    return 0;
};
