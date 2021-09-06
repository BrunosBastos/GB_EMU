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

    if(get_ldc_display_enable()) {
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








void ppu::set_ldc_display_enable(bool status) {
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


bool ppu::get_ldc_display_enable() {
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
