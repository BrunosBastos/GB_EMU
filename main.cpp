#include <SDL2/SDL.h>

#include "cartridge.h"
#include "cpu.h"
#include "mmu.h"
#include "opcodes.h"
#include "ppu.h"
#include "emulator.h"

SDL_Renderer *renderer;


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

void update_screen(Ppu *p) {
    for (int x = 0; x < PPU_BUFFER_WIDTH; x++) {
        for (int y = 0; y < PPU_BUFFER_HEIGHT; y++) {
            change_color(p->buffer[x][y]);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
};

void handle_input(Emulator* emu, SDL_Event event) {
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
            emu->key_pressed(key);
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
            emu->key_released(key);
        }
    }
};

int main() {
    sdl_init();
    SDL_Event event;

    initialize_optable();

    Emulator *emu = new Emulator("./roms/tetris.gb");
   
    bool running = true;
    while (running) {

        int startMs = SDL_GetTicks();
        emu->run();
        update_screen(emu->ppu);

        while (SDL_PollEvent(&event)) { 
            handle_input(emu, event);
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
        }

        int endMs = SDL_GetTicks();
        SDL_Delay(16 - (endMs - startMs));
        printf("fps=%d\n", (int)(1000/(SDL_GetTicks()-startMs)));
    }
    return 0;
};
