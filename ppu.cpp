#include "ppu.h"

// http://www.codeslinger.co.uk/pages/projects/gameboy/lcd.html
// http://www.codeslinger.co.uk/pages/projects/gameboy/graphics.html
// http://www.codeslinger.co.uk/pages/projects/gameboy/interupts.html


void ppu::initialize(mmu* memory, cpu* cp) {

    this->memory = memory;
    this->cp = cp;

    clock_count = 456;

    lcd_control = &memory->address[memory->ppu];
    lcd_status = &memory->address[memory->ppu + 0x01];
    scroll_y = &memory->address[memory->ppu + 0x02];
    scroll_x = &memory->address[memory->ppu + 0x03];
    line = &memory->address[memory->ppu + 0x04];

    windpos_y = &memory->address[memory->ppu + 0x0A];
    windpos_x = &memory->address[memory->ppu + 0x0B];

    pallets[0] = &memory->address[0xFF47];
    pallets[1] = &memory->address[0xFF48];
    pallets[2] = &memory->address[0xFF49];
};

void ppu::render_line() {
    
    if (get_bg_display()) {
        render_tiles();
    }
    if (get_obj_display_enable()) {
        render_sprites();
    }
};

void ppu::update_graphics() {
    set_lcd_status();

    if (!get_lcd_display_enable()) {
        return;
    }
 
    clock_count -= cp->last_clock;

    if (clock_count <= 0) {
        byte curr_line = ++(*line);
        printf("curr_line : %d\n", curr_line);

        clock_count = 456;

        if (curr_line == 144) {
            cp->request_interrupt(INTERRUPT_VBLANK);
        } else if (curr_line > 153) {
            // V-BLANK area
            *line = 0;
        } else if (curr_line < 144) {
            render_line();
        }
    }
};

void ppu::set_lcd_status() {
    if (!get_lcd_display_enable()) {
        // set the mode to 1 during lcd disabled and reset scanline
        clock_count = 456;
        *line = 0;
        *lcd_status &= 252;
        set_mode(1);
        return;
    }
    byte curr_line = *line;
    byte last_mode = get_mode();

    bool req_interrupt = false;

    if (curr_line >= 144) {
        // V-BLANK area
        set_mode(1);
        req_interrupt = *lcd_status & 0x10;
    } else {
        int mode2bounds = 456 - 80;
        int mode3bounds = mode2bounds - 172;

        if (clock_count >= mode2bounds) {
            set_mode(2);
            req_interrupt = *lcd_status & 0x20;
        }
        else if (clock_count >= mode3bounds) {
            set_mode(3);
        }
        else {
            set_mode(0);
            req_interrupt = *lcd_status & 0x08;
        }
    }

    // request interrupt if mode is different
    if (req_interrupt && (get_mode() != last_mode)) {
        cp->request_interrupt(INTERRUPT_LCDC);
    }
    
    if (curr_line == cp->read_memory(0xFF45)) {
        *lcd_status |= 0x04;
        if (*lcd_status & 0x40) {
            // bit 6
            cp->request_interrupt(INTERRUPT_LCDC);
        }
    } else {
        *lcd_status &= ~0x04;
    }
};

void ppu::update_bg_scanline(byte curr_line) {
    
    word tile_map = get_bg_tile_map_select() ? 0x9C00 : 0x9800;
    byte tile_y = *scroll_y + curr_line;

    for (int pixel = 0; pixel < 160 && curr_line < 143; pixel++) {
        byte tile_x = pixel + *scroll_x;
        word tile_addr = tile_map + (tile_y / 8) * 32 + (tile_x / 8);

        update_bg_tile(pixel, curr_line, tile_x % 8, tile_y % 8, tile_addr);
    }
};

void ppu::update_window_scanline(byte curr_line) {

    word tile_map = get_wnd_tile_map_select() ? 0x9C00 : 0x9800;
    byte tile_y = curr_line - *windpos_x;

    for (int pixel = 0; pixel < 160 && curr_line < 143; pixel++) {
        byte tile_x = (pixel >= *windpos_x - 7) ? 
            pixel + *scroll_x : pixel - *windpos_x - 7;
        word tile_addr = tile_map + (tile_y / 8) * 32 + (tile_x / 8);

        update_window_tile(pixel, curr_line, tile_x % 8, tile_y % 8, tile_addr);
    }
};

void ppu::update_bg_tile(int pixel, int curr_line, int offset_x, int offset_y, word tile_addr) {
    word tile_data = get_bg_wnd_tile_data_select() ? 0x8000 : 0x8800;

    word tile_location = tile_data;
    if (tile_data == 0x8000)
        tile_location += (byte)cp->read_memory(tile_addr) * 16;
    else
        tile_location += ((char)cp->read_memory(tile_addr) + 128) * 16;

    // each tile has 2 bytes
    byte data1 = cp->read_memory(tile_location + offset_y *2);
    byte data2 = cp->read_memory(tile_location + offset_y *2 + 1);

    int color_bit = -(offset_x - 7);
    int color_num = (data2 & (1 << color_bit)) << 1 | (data1 & (1 << color_bit));  // combine 2 bytes
    int color = (*pallets[0] & (1 << (2 * color_num + 1))) << 1 | (*pallets[0] & (1 << (2 * color_num)));

    buffer[pixel][curr_line] = color;
};

void ppu::update_window_tile(int pixel, int curr_line, int offset_x, int offset_y, word tile_addr) {
    word tile_data = get_bg_wnd_tile_data_select() ? 0x8000 : 0x8800;

    word tile_location = tile_data;
    if (tile_data == 0x8000)
        tile_location += (byte)cp->read_memory(tile_addr) * 16;
    else
        tile_location += ((char)cp->read_memory(tile_addr) + 128) * 16;

    // each tile has 2 bytes
    byte data1 = cp->read_memory(tile_location + 2 * offset_y);
    byte data2 = cp->read_memory(tile_location + 2 * offset_y + 1);

    int color_bit = -(offset_x - 7);
    int color_num = (data2 & (1 << color_bit)) << 1 | (data1 & (1 << color_bit));   // combine 2 bytes
    int color = (*pallets[0] & (1 << (2 * color_num + 1))) << 1 | (*pallets[0] & (1 << (2 * color_num)));

    buffer[pixel][curr_line] = color;
};

void ppu::render_tiles() {

    byte curr_line = *line;

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

void ppu::render_sprites() {

    byte curr_line = *line;

    if(curr_line > 143) {
        return;
    }

    // each sprite takes 4 bytes in the oam
    for (int sprite = 0; sprite < 40 * 4; sprite += 4) {

        byte py = cp->read_memory(memory->oam + sprite) - 16;
        byte px = cp->read_memory(memory->oam + sprite + 1) - 8;
        byte sprite_location = cp->read_memory(memory->oam + sprite + 2);
        byte attributes = cp->read_memory(memory->oam + sprite + 3);

        int ysize = get_obj_size() ? 16 : 8;

        // draw only the sprites in the curr line
        if ((curr_line >= py) && (curr_line < (py + ysize))) {
            int curry = curr_line - py;

            // check if invert y axis
            if (attributes & (1 << 6)) {
                curry = -(curry - ysize);
            }
            curry *= 2;

            word data_addr = (memory->vram + (sprite_location * 16)) + curry;
            byte data1 = cp->read_memory(data_addr);
            byte data2 = cp->read_memory(data_addr + 1);

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

                // white is transparent
                if (color == WHITE) continue;

                buffer[pixel][curr_line] = color;
            }
        }
    }
};

void ppu::set_mode(int mode) { *lcd_status = ((*lcd_status & 252) | mode); };

byte ppu::get_mode() { return *lcd_status & 3; };

void ppu::set_lcd_display_enable(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 7)) | (status << 7);
};
void ppu::set_wnd_tile_map_select(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 6)) | (status << 6);
};
void ppu::set_wnd_display_enable(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 5)) | (status << 5);
};
void ppu::set_bg_wnd_tile_data_select(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 4)) | (status << 4);
};
void ppu::set_bg_tile_map_select(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 3)) | (status << 3);
};
void ppu::set_obj_size(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 2)) | (status << 2);
};
void ppu::set_obj_display_enable(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 1)) | (status << 1);
};
void ppu::set_bg_display(bool status) {
    *lcd_control = (*lcd_control & ~(1UL << 0)) | (status << 0);
};

bool ppu::get_lcd_display_enable() { return *lcd_control & 0x80; };
bool ppu::get_wnd_tile_map_select() { return *lcd_control & 0x40; };
bool ppu::get_wnd_display_enable() { return *lcd_control & 0x20; };
bool ppu::get_bg_wnd_tile_data_select() { return *lcd_control & 0x10; };
bool ppu::get_bg_tile_map_select() { return *lcd_control & 0x08; };
bool ppu::get_obj_size() { return *lcd_control & 0x04; };
bool ppu::get_obj_display_enable() { return *lcd_control & 0x02; };
bool ppu::get_bg_display() { return *lcd_control & 0x01; };
