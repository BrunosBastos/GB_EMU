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

    int tile_number = 0;
    //unsigned short tile = (get_lcd_4() ? 0x8000 : 0x8800) + (tile_number + 128) * 16;
     
};


void ppu::update_graphics() {

    set_lcd_status();

    if(get_lcd_display_enable()) {
        clock_count -= cp->last_clock;
    }
    else {
        return;
    }

    if(clock_count <= 0) {
        (*line)++;      // increase the current line value

        clock_count = 456;

        if(*line == 144) {
            // request interrupt? idk what this is 
        }
        else if(*line > 153) {
            // line values are between 0 and 153
            *line = 0;
        }
        else if(*line < 144) {
            // display only has 144 lines, lines between 144-153 serve other purposes
            render_line();
        }

    }


};


void ppu::set_lcd_status() {

    if(!get_lcd_display_enable()) {
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
    if(*line >= 144) {
        mode = 1;
        set_mode(1);
        request_interrupt = *lcd_status & 0x10;
    } 
    else {
        int mode2bounds = 456-80;
        int mode3bounds = mode2bounds - 172;

        // mode 2
        if(clock_count >= mode2bounds) {
            mode = 2;
            set_mode(2);
            request_interrupt = *lcd_status & 0x20;
        }
        // mode 3
        else if(clock_count >= mode3bounds) {
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
        ; // TODO: RequestInterupt(1)

    // check the coincidence flag
    if (*line == memory->address[0xFF45]) {
        *lcd_status |= 0x04;
        if(*lcd_status & 0x40) // bit 6
            ; // TODO: RequestInterupt(1)
    }
    else {
        *lcd_status &= ~0x04;
    }
};




void ppu::set_mode(int mode) {
    *lcd_status = ((*lcd_status & 252) | mode);
};

byte ppu::get_mode() {
    return *lcd_status & 3;
};

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


bool ppu::get_lcd_display_enable() {
    return *lcd_control & 0x80;
};
bool ppu::get_wnd_tile_map_select() {
    return *lcd_control & 0x40;
};
bool ppu::get_wnd_display_enable() {
    return *lcd_control & 0x20;
};
bool ppu::get_bg_wnd_tile_data_select() {
    return *lcd_control & 0x10;
};
bool ppu::get_bg_tile_map_select() {
    return *lcd_control & 0x08;
};
bool ppu::get_obj_size() {
    return *lcd_control & 0x04;
};
bool ppu::get_obj_display_enable() {
    return *lcd_control & 0x02;
};
bool ppu::get_bg_display() {
    return *lcd_control & 0x01;
};
