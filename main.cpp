#include <SDL2/SDL.h>

#include "cartridge.h"
#include "cpu.h"
#include "mmu.h"
#include "opcodes.h"
#include "ppu.h"
#include "emulator.h"

#include <iostream>
#include <iomanip>
#include <fstream>

SDL_Renderer *renderer;
SDL_Texture *bg_texture;
SDL_Texture *window_texture;
SDL_Texture *sprites_texture;

void sdl_init() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window =
        SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         500, 500, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);
    bg_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, PPU_BUFFER_WIDTH, PPU_BUFFER_HEIGHT);
    window_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, PPU_BUFFER_WIDTH, PPU_BUFFER_HEIGHT);
    sprites_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, PPU_BUFFER_WIDTH, PPU_BUFFER_HEIGHT);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(bg_texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(window_texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(sprites_texture, SDL_BLENDMODE_BLEND);

};

void draw_sprites(Ppu *p) {
    SDL_UpdateTexture(sprites_texture, nullptr, p->sprites_buffer, PPU_BUFFER_WIDTH * sizeof(int));
    SDL_RenderCopy(renderer, sprites_texture, nullptr, nullptr);
    
};

void draw_bg(Ppu *p) {

    std::ofstream myfile;
    myfile.open("example.txt");
    for(int i=0; i < PPU_BUFFER_WIDTH; i++) {
        for(int j=0; j < PPU_BUFFER_HEIGHT; j++) {
            myfile << std::setw(8) << std::hex << p->bg_buffer[i + j*PPU_BUFFER_WIDTH] << ' ';
        }
        myfile << std::endl;
    }
    myfile.close();

    SDL_UpdateTexture(bg_texture, nullptr, p->bg_buffer, PPU_BUFFER_WIDTH * sizeof(int));
    SDL_RenderCopy(renderer, bg_texture, nullptr, nullptr);
};

void draw_window(Ppu *p) {
    
    SDL_UpdateTexture(window_texture, nullptr, p->window_buffer, PPU_BUFFER_WIDTH * sizeof(int));
    SDL_RenderCopy(renderer, window_texture, nullptr, nullptr);
   
};

void update_screen(Ppu *p) {
   
    SDL_RenderClear(renderer);

    draw_bg(p);
    //draw_window(p);
    //draw_sprites(p);
    
    SDL_RenderPresent(renderer);
};

void handle_input(Emulator* emu, SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
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

        int framerate = 60;
        float cycles_per_frame = emu->clock_speed / framerate;
		float time_between_frames = 1000 / framerate;
        int current_cycle = 0;


        while (SDL_PollEvent(&event)) { 
            handle_input(emu, event);
            if (event.type == SDL_QUIT) {
                running = false;
                exit(0);
            }
        }

        while (current_cycle < cycles_per_frame && running) {
            emu->run();
            current_cycle += emu->cpu->last_clock;        
        }

        update_screen(emu->ppu);

        int endMs = SDL_GetTicks();
        printf("fps=%d\n", time_between_frames - endMs + startMs);
        int delay = time_between_frames - (endMs - startMs);
        if(delay > 0) {
            SDL_Delay(delay);
        }
    }
    return 0;
};
