#include "ppu.h"

// http://www.codeslinger.co.uk/pages/projects/gameboy/lcd.html
// http://www.codeslinger.co.uk/pages/projects/gameboy/graphics.html
// http://www.codeslinger.co.uk/pages/projects/gameboy/interupts.html


Ppu::Ppu(Mmu* mmu) {

    this->mmu = mmu;
    clock_count = 456;

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
    
    if (get_bg_display()) {
        render_tiles();
    }
    if (get_obj_display_enable()) {
        render_sprites();
    }
};


void Ppu::update_bg_scanline(byte curr_line) {
    
    word tile_map = get_bg_tile_map_select() ? 0x9C00 : 0x9800;
    byte tile_y = *scroll_y + curr_line;

    for (int pixel = 0; pixel < 160 && curr_line < 144; pixel++) {
        byte tile_x = pixel + *scroll_x;
        word tile_addr = tile_map + (tile_y / 8) * 32 + (tile_x / 8);

        update_bg_tile(pixel, curr_line, tile_x % 8, tile_y % 8, tile_addr);
    }
};

void Ppu::update_window_scanline(byte curr_line) {

    word tile_map = get_wnd_tile_map_select() ? 0x9C00 : 0x9800;
    byte tile_y = curr_line - *windpos_x;

    for (int pixel = 0; pixel < 160 && curr_line < 144; pixel++) {
        byte tile_x = (pixel >= *windpos_x - 7) ? 
            pixel + *scroll_x : pixel - *windpos_x - 7;
        word tile_addr = tile_map + (tile_y / 8) * 32 + (tile_x / 8);

        update_window_tile(pixel, curr_line, tile_x % 8, tile_y % 8, tile_addr);
    }
};

void Ppu::update_bg_tile(int pixel, int curr_line, int offset_x, int offset_y, word tile_addr) {
    word tile_data = get_bg_wnd_tile_data_select() ? 0x8000 : 0x8800;

    word tile_location = tile_data;
    if (tile_data == 0x8000)
        tile_location += (byte)mmu->read_memory(tile_addr) * 16;
    else
        tile_location += ((char)mmu->read_memory(tile_addr) + 128) * 16;

    // each tile has 2 bytes
    byte data1 = mmu->read_memory(tile_location + offset_y *2);
    byte data2 = mmu->read_memory(tile_location + offset_y *2 + 1);

    int color_bit = -(offset_x - 7);
    int color_num = (data2 & (1 << color_bit)) << 1 | (data1 & (1 << color_bit));  // combine 2 bytes to give a value 0-3
    int color = (*pallets[0] & (1 << (2 * color_num + 1))) << 1 | (*pallets[0] & (1 << (2 * color_num)));  // pick 1 of the 4 colors in the pallet

    bg_buffer[pixel + curr_line * PPU_BUFFER_WIDTH] = get_color(color);
};


void Ppu::update_window_tile(int pixel, int curr_line, int offset_x, int offset_y, word tile_addr) {
    word tile_data = get_bg_wnd_tile_data_select() ? 0x8000 : 0x8800;

    word tile_location = tile_data;
    if (tile_data == 0x8000)
        tile_location += (byte)mmu->read_memory(tile_addr) * 16;
    else
        tile_location += ((char)mmu->read_memory(tile_addr) + 128) * 16;

    // each tile has 2 bytes
    byte data1 = mmu->read_memory(tile_location + 2 * offset_y);
    byte data2 = mmu->read_memory(tile_location + 2 * offset_y + 1);

    int color_bit = -(offset_x - 7);
    int color_num = (data2 & (1 << color_bit)) << 1 | (data1 & (1 << color_bit));   // combine 2 bytes
    int color = (*pallets[0] & (1 << (2 * color_num + 1))) << 1 | (*pallets[0] & (1 << (2 * color_num)));

    // if the color num is 0 then the tile is transparent, same for sprites
    window_buffer[pixel + curr_line * PPU_BUFFER_WIDTH] = color_num == 0 ? 0x00000000 : get_color(color);
};

void Ppu::render_tiles() {

    byte curr_line = mmu->LY.get();

    if(curr_line > 143) {
        return;
    }

    if(get_wnd_display_enable() && *windpos_y <= curr_line) {
        update_window_scanline(curr_line);
    }
    if(get_bg_display()) {
        update_bg_scanline(curr_line);
    }
};

void Ppu::render_sprites() {

    byte curr_line = mmu->LY.get();

    if(curr_line > 143) {
        return;
    }

    // each sprite takes 4 bytes in the oam
    for (int sprite = 0; sprite < 40 * 4; sprite += 4) {

        byte py = mmu->read_memory(mmu->oam + sprite) - 16;
        byte px = mmu->read_memory(mmu->oam + sprite + 1) - 8;
        byte sprite_location = mmu->read_memory(mmu->oam + sprite + 2);
        byte attributes = mmu->read_memory(mmu->oam + sprite + 3);

        int ysize = get_obj_size() ? 16 : 8;

        // draw only the sprites in the curr line
        if ((curr_line >= py) && (curr_line < (py + ysize))) {
            int curry = curr_line - py;

            // check if invert y axis
            if (attributes & (1 << 6)) {
                curry = -(curry - ysize);
            }
            curry *= 2;

            word data_addr = (mmu->vram + (sprite_location * 16)) + curry;
            byte data1 = mmu->read_memory(data_addr);
            byte data2 = mmu->read_memory(data_addr + 1);

            for (int sprite_pixel = 0; sprite_pixel < 8; sprite_pixel++) {
                int color_bit = sprite_pixel;
                int pixel = px + 7 - sprite_pixel;

                // check if invert x axis
                if (attributes & (1 << 5)) {
                    color_bit = -(color_bit - 7);
                }

                int color_num = (data2 & (1 << color_bit)) << 1 | (data1 & (1 << color_bit));  
                byte p = attributes & (1 << 4) ? 2 : 1;     // choose the pallet
                int color = (*pallets[p] & (1 << (2 * color_num + 1))) << 1 | (*pallets[p] & (1 << (2 * color_num)));

                sprites_buffer[pixel + curr_line * PPU_BUFFER_WIDTH] = color_num == 0 ? 0x00000000 : get_color(color);
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
};

void Ppu::set_mode(int mode) { *lcd_status = ((*lcd_status & 252) | mode); };

byte Ppu::get_mode() { return *lcd_status & 3; };

void Ppu::set_lcd_display_enable(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 7)) | (status << 7);
};
void Ppu::set_wnd_tile_map_select(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 6)) | (status << 6);
};
void Ppu::set_wnd_display_enable(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 5)) | (status << 5);
};
void Ppu::set_bg_wnd_tile_data_select(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 4)) | (status << 4);
};
void Ppu::set_bg_tile_map_select(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 3)) | (status << 3);
};
void Ppu::set_obj_size(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 2)) | (status << 2);
};
void Ppu::set_obj_display_enable(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 1)) | (status << 1);
};
void Ppu::set_bg_display(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 0)) | (status << 0);
};

bool Ppu::get_lcd_display_enable() { return *lcd_control & 0x80; };
bool Ppu::get_wnd_tile_map_select() { return *lcd_control & 0x40; };
bool Ppu::get_wnd_display_enable() { return *lcd_control & 0x20; };
bool Ppu::get_bg_wnd_tile_data_select() { return *lcd_control & 0x10; };
bool Ppu::get_bg_tile_map_select() { return *lcd_control & 0x08; };
bool Ppu::get_obj_size() { return *lcd_control & 0x04; };
bool Ppu::get_obj_display_enable() { return *lcd_control & 0x02; };
bool Ppu::get_bg_display() { return *lcd_control & 0x01; };
