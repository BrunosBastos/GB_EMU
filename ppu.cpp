#include "ppu.h"

// http://www.codeslinger.co.uk/pages/projects/gameboy/lcd.html
// http://www.codeslinger.co.uk/pages/projects/gameboy/graphics.html
// http://www.codeslinger.co.uk/pages/projects/gameboy/interupts.html

void ppu::initialize(mmu* memory, cpu* cp) {
    this->memory = memory;
    this->cp = cp;

    clock_count = 0;

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

    if (get_lcd_display_enable()) {
        clock_count -= cp->last_clock;
    } else {
        return;
    }

    if (clock_count <= 0) {
        (*line)++;  // increase the current line value

        clock_count = 456;

        if (*line == 144) {
            // request interrupt? idk what this is
        } else if (*line > 153) {
            // line values are between 0 and 153
            *line = 0;
        } else if (*line < 144) {
            // display only has 144 lines, lines between 144-153 serve otherpurposes
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

    byte currentmode = get_mode();

    byte mode = 0;
    bool request_interrupt = false;

    // in vblank so set mode to 1
    if (*line >= 144) {
        mode = 1;
        set_mode(1);
        request_interrupt = *lcd_status & 0x10;
    } else {
        int mode2bounds = 456 - 80;
        int mode3bounds = mode2bounds - 172;

        // mode 2
        if (clock_count >= mode2bounds) {
            mode = 2;
            set_mode(2);
            request_interrupt = *lcd_status & 0x20;
        }
        // mode 3
        else if (clock_count >= mode3bounds) {
            mode = 3;
            set_mode(3);
        }
        // mode 0
        else {
            mode = 0;
            set_mode(0);
            request_interrupt = *lcd_status & 0x08;
        }
    }

    // just entered a new mode so request interupt
    if (request_interrupt && (mode != currentmode))
        ;  // TODO: RequestInterupt(1)

    // check the coincidence flag
    if (*line == memory->address[0xFF45]) {
        *lcd_status |= 0x04;
        if (*lcd_status & 0x40)  // bit 6
            ;                    // TODO: RequestInterupt(1)
    } else {
        *lcd_status &= ~0x04;
    }
};


void ppu::render_tiles() {
    word tile_data = 0;
    word background_memory = 0;
    bool unsig = true;

    byte windpos_x2 = *windpos_x - 7;

    // is the window enabled?
    bool using_window = (get_wnd_display_enable() && *windpos_y <= *line);

    // which tile data are we using?
    if (get_bg_wnd_tile_data_select()) {
        tile_data = 0x8000;
    } else {
        tile_data = 0x8800;
        unsig = false;
    }

    // which background mem?
    if (!using_window) {
        background_memory = get_bg_tile_map_select() ? 0x9C00 : 0x9800;
    // which window memory?
    } else {
        background_memory = get_wnd_tile_map_select() ? 0x9C00 : 0x9800;
    }

    byte yPos = !using_window ? *scroll_y + *line : *line - *windpos_y;

    // which of the 8 vertical pixels of the current
    // tile is the scanline on?
    word tile_row = (((byte)(yPos / 8)) * 32);

    // time to start drawing the 160 horizontal pixels
    // for this scanline
    for (int pixel = 0; pixel < 160; pixel++) {

        if ((*line < 0) || (*line > 143) || (pixel < 0) || (pixel > 159)) {
            continue;
        }

        byte xPos = pixel + *scroll_x;

        // translate the current x pos to window space if necessary
        if (using_window) {
            if (pixel >= windpos_x2) {
                xPos = pixel - windpos_x2;
            }
        }
        // which of the 32 horizontal tiles does this xPos fall within?
        word tile_col = (xPos / 8);
        short tile_num; 

        // get the tile identity number. Remember it can be signed
        // or unsigned
        word tile_addr = background_memory + tile_row + tile_col;
        if (unsig)
            tile_num = (byte)memory->address[tile_addr];
        else
            tile_num = (char)memory->address[tile_addr];

        // deduce where this tile identifier is in memory. Remember i
        // shown this algorithm earlier
        word tile_location = tile_data;

        if (unsig)
            tile_location += (tile_num * 16);
        else
            tile_location += ((tile_num + 128) * 16);

        byte line_ = (yPos % 8)*2;   // each vertical line_ takes up two bytes of memory
        byte data1 = memory->address[tile_location + line_];
        byte data2 = memory->address[tile_location + line_ + 1];

        int colour_bit = -((xPos % 8) - 7);

        // combine data 2 and data 1 to get the colour id for this pixel
        int colour_num = (data2 & (1 << colour_bit)) << 1 | (data1 & (1 << colour_bit));  

        // get colour from pallete 0xFF47
        int colour = (*pallets[0] & (1 << (2 * colour_num + 1))) << 1 | (*pallets[0] & (1 << (2 * colour_num)));

        buffer[pixel][*line] = colour;
    }
}

void ppu::render_sprites() {
    bool use8x16 = false;
    if (get_obj_size()) {
        use8x16 = true;
    }

    for (int sprite = 0; sprite < 40; sprite++) {
        // sprite occupies 4 bytes in the sprite attributes table
        byte index = sprite * 4;
        byte yPos = memory->address[memory->oam + index] - 16;
        byte xPos = memory->address[memory->oam + index + 1] - 8;
        byte tile_location = memory->address[memory->oam + index + 2];
        byte attributes = memory->address[memory->oam + index + 3];

        bool yFlip = attributes & (1 << 6);
        bool xFlip = attributes & (1 << 5);

        int ysize = 8;
        if (use8x16) ysize = 16;

        // does this sprite intercept with the scanline?
        if ((*line >= yPos) && (*line < (yPos + ysize))) {
            int line_ = *line - yPos;

            // read the sprite in backwards in the y axis
            if (yFlip) {
                line_ = -(line_ - ysize);
            }
            line_ *= 2;  // same as for tiles

            word data_addr = (memory->vram + (tile_location * 16)) + line_;
            byte data1 = memory->address[data_addr];
            byte data2 = memory->address[data_addr + 1];

            // its easier to read in from right to left as pixel 0 is
            // bit 7 in the colour data, pixel 1 is bit 6 etc...
            for (int tile_pixel = 7; tile_pixel >= 0; tile_pixel--) {
                int colour_bit = tile_pixel;

                int xPix = 0 - tile_pixel;
                xPix += 7;

                int pixel = xPos + xPix;

                // sanity check
                if ((*line < 0) || (*line > 143) || (pixel < 0) ||
                    (pixel > 159)) {
                    continue;
                }

                // read the sprite in backwards for the x axis
                if (xFlip) {
                    colour_bit -= 7;
                    colour_bit *= -1;
                }

                // the rest is the same as for tiles
                int colour_num = (data2 & (1 << colour_bit)) << 1 | (data1 & (1 << colour_bit));  

                byte p = attributes & (1 << 4) ? 2 : 1;
                int colour = (*pallets[p] & (1 << (2 * colour_num + 1))) << 1 | (*pallets[p] & (1 << (2 * colour_num)));

                // white is transparent for sprites.
                if (colour == WHITE) continue;

                buffer[pixel][*line] = colour;
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
