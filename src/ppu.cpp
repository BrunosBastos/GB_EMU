#include "ppu.h"


Ppu::Ppu(Mmu* mmu) {

    this->mmu = mmu;

    lcd_control = &mmu->address[mmu->ppu];
    lcd_status  = &mmu->address[mmu->ppu + 0x01];
    scroll_y    = &mmu->address[mmu->ppu + 0x02];
    scroll_x    = &mmu->address[mmu->ppu + 0x03];
    line        = &mmu->address[mmu->ppu + 0x04];

    windpos_y = &mmu->address[mmu->ppu + 0x0A];
    windpos_x = &mmu->address[mmu->ppu + 0x0B];

    pallets[0] = &mmu->address[0xFF47];
    pallets[1] = &mmu->address[0xFF48];
    pallets[2] = &mmu->address[0xFF49];
};

void Ppu::render_line() {
    
    /*
        LCDC register controls whether the tiles or sprites are drawn 
    */

    if (get_bg_display()) {
        render_tiles();
    }
    if (get_obj_display_enable()) {
        render_sprites();
    }
};

void Ppu::update_bg_scanline(byte curr_line) {
    /*
        Tile map is either stored starting from 0x9C00 or 0x9800.
        Each pixel points to a tile in the tile set.

        Iterate the current line and for each pixel, find the 
        corresponding tile and give that pixel the color
        according to the tile information stored in the tileset.
    */

    word tile_map = get_bg_tile_map_select() ? TILE_MAP_ONE_ADDRESS : TILE_MAP_ZERO_ADDRESS;
    byte tile_y = *scroll_y + curr_line;

    for (int pixel = 0; pixel < 160 && curr_line < 144; pixel++) {
        byte tile_x = pixel + *scroll_x;
        word map_addr = tile_map + (tile_y / 8) * 32 + (tile_x / 8);

        update_bg_tile(pixel, curr_line, tile_x % 8, tile_y % 8, map_addr);
    }
};

void Ppu::update_bg_tile(int pixel, int curr_line, int offset_x, int offset_y, word tile_addr) {

    word tile_location = get_bg_wnd_tile_data_select() ? TILE_SET_ZERO_ADDRESS : TILE_SET_ONE_ADDRESS;
    if (tile_location == TILE_SET_ZERO_ADDRESS)
        tile_location += (byte)mmu->read_memory(tile_addr) * 16;
    else
        tile_location += ((char)mmu->read_memory(tile_addr) + 128) * 16;

    // each tile has 2 bytes
    byte data1 = mmu->read_memory(tile_location + offset_y *2);
    byte data2 = mmu->read_memory(tile_location + offset_y *2 + 1);
    
    // bit 0 is the right most bit in a byte, so the first pixel needs to point to 0
    int color_bit = -(offset_x - 7);

    int color_num = (data2 & (1 << color_bit)) >> (color_bit - 1) | 
                    (data1 & (1 << color_bit)) >> (color_bit);  // combine 2 bytes to give a value 0-3
    int color = (*pallets[0] & (1 << (2 * color_num + 1))) >> (2 * color_num) | 
                (*pallets[0] & (1 << (2 * color_num))) >> (2 * color_num);  // pick 1 of the 4 colors in the pallet

    bg_buffer[pixel + curr_line * PPU_BUFFER_WIDTH] = get_color(color);
};

void Ppu::update_window_scanline(byte curr_line) {

    word tile_map = get_wnd_tile_map_select() ? TILE_MAP_ONE_ADDRESS : TILE_MAP_ZERO_ADDRESS;
    byte tile_y = curr_line - *windpos_x;

    for (int pixel = 0; pixel < 160 && curr_line < 144; pixel++) {
        byte tile_x = (pixel >= *windpos_x - 7) ?
            pixel + *scroll_x : pixel - *windpos_x - 7;
        word tile_addr = tile_map + (tile_y / 8) * 32 + (tile_x / 8);

        update_window_tile(pixel, curr_line, tile_x % 8, tile_y % 8, tile_addr);
    }
};


void Ppu::update_window_tile(int pixel, int curr_line, int offset_x, int offset_y, word tile_addr) {

    word tile_location = get_bg_wnd_tile_data_select() ? TILE_SET_ZERO_ADDRESS : TILE_SET_ONE_ADDRESS;
    if (tile_location == TILE_SET_ZERO_ADDRESS)
        tile_location += (byte)mmu->read_memory(tile_addr) * 16;
    else
        tile_location += ((char)mmu->read_memory(tile_addr) + 128) * 16;

    // each tile has 2 bytes
    byte data1 = mmu->read_memory(tile_location + 2 * offset_y);
    byte data2 = mmu->read_memory(tile_location + 2 * offset_y + 1);

    int color_bit = -(offset_x - 7);
    int color_num = (data2 & (1 << color_bit)) >> (color_bit - 1) | 
                    (data1 & (1 << color_bit)) >> (color_bit);  // combine 2 bytes to give a value 0-3
    int color = (*pallets[0] & (1 << (2 * color_num + 1))) >> (2 * color_num) | 
                (*pallets[0] & (1 << (2 * color_num))) >> (2 * color_num);  // pick 1 of the 4 colors in the pallet

    // if the color num is 0 then the tile is transparent, same for sprites
    window_buffer[pixel + curr_line * PPU_BUFFER_WIDTH] = color_num == 0 ? 0x00000000 : get_color(color);
};

void Ppu::render_tiles() {

    byte curr_line = mmu->LY.get();

    if (curr_line > 143) {
        return;
    }

    if (get_wnd_display_enable() && *windpos_y <= curr_line) {
        update_window_scanline(curr_line);
    }
    if (get_bg_display()) {
        update_bg_scanline(curr_line);
    }
};

void Ppu::render_sprites() {

    byte curr_line = mmu->LY.get();

    if (curr_line > 143) {
        return;
    }

    // line is cleared before the sprites are written
    // otherwise they will stay there forever
    for(int i=0; i < PPU_BUFFER_WIDTH; i++) {
        sprites_buffer[i + curr_line * PPU_BUFFER_WIDTH] = 0;
    }

    // each sprite takes 4 bytes in the oam
    for (int sprite = 0; sprite < 40 * 4; sprite += 4) {
        byte py = mmu->read_memory(mmu->oam + sprite) - 16;
        byte px = mmu->read_memory(mmu->oam + sprite + 1) - 8;
        byte sprite_location = mmu->read_memory(mmu->oam + sprite + 2);
        byte attributes = mmu->read_memory(mmu->oam + sprite + 3);

        /* 
            attributes -> 1byte
                bit 7 - priority
                bit 6 - Y flip
                bit 5 - X flip
                bit 4 - palette number
        */

        int ysize = get_obj_size() ? 16 : 8;      // bit 2 of LCDC

        // draw only the sprites in the curr line
        if ((curr_line >= py) && (curr_line < (py + ysize))) {
            int pixel_y = curr_line - py;

            // check if y flip
            if (attributes & (1 << 6)) {
                pixel_y = -(pixel_y - ysize);
            }

            word data_addr = (mmu->vram + (sprite_location * 16)) + pixel_y * 2;
            byte data1 = mmu->read_memory(data_addr);
            byte data2 = mmu->read_memory(data_addr + 1);

            for (int sprite_pixel = 0; sprite_pixel < 8; sprite_pixel++) {
                int color_bit = sprite_pixel;
                int pixel = px + 7 - sprite_pixel;

                // check if invert x axis
                if (attributes & (1 << 5)) {
                    color_bit = -(color_bit - 7);
                }

                int color_num = (data2 & (1 << color_bit)) >> (color_bit - 1) | 
                                (data1 & (1 << color_bit)) >> (color_bit);  // combine 2 bytes to give a value 0-3
                byte p = attributes & (1 << 4) ? 2 : 1;     // choose the pallet
                int color = (*pallets[p] & (1 << (2 * color_num + 1))) >> (2 * color_num) | 
                            (*pallets[p] & (1 << (2 * color_num))) >> (2 * color_num);  // pick 1 of the 4 colors in the pallet

                sprites_buffer[pixel + curr_line * PPU_BUFFER_WIDTH] = color_num == 0 ? 0x00000000 : get_color(color);

                /*
                    FIXME: 
                    if priority flag is set to 0, the sprite is rendered a above windown and background
                    however, if the value is set to 1, then it is only visible if both background and window
                    are White. 
                */

            }
        }
    }
};

int Ppu::get_color(byte color) {
    // values in the format ABGR
    if (color == WHITE) return 0xFFFFFFFF;
    if (color == L_GRAY) return 0xFF6c6c6c;
    if (color == D_GRAY) return 0xFFf7f7f7;
    if (color == BLACK) return 0xFF000000;
    assert(false);
};

void Ppu::set_mode(int mode) { *lcd_status = ((*lcd_status & 252) | mode); };

byte Ppu::get_mode() { return *lcd_status & 3; };

bool Ppu::get_lcd_display_enable() { return *lcd_control & 0x80; };
bool Ppu::get_wnd_tile_map_select() { return *lcd_control & 0x40; };
bool Ppu::get_wnd_display_enable() { return *lcd_control & 0x20; };
bool Ppu::get_bg_wnd_tile_data_select() { return *lcd_control & 0x10; };
bool Ppu::get_bg_tile_map_select() { return *lcd_control & 0x08; };
bool Ppu::get_obj_size() { return *lcd_control & 0x04; };
bool Ppu::get_obj_display_enable() { return *lcd_control & 0x02; };
bool Ppu::get_bg_display() { return *lcd_control & 0x01; };
