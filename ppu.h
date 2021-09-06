#include "types.h"
#include "mmu.h"
#include "cpu.h"


#define PPU_BUFFER_WIDTH    160
#define PPU_BUFFER_HEIGHT   144

#define MODE_HB   0
#define MODE_VB   1
#define MODE_OAM  2
#define MODE_VRAM 3



class ppu {


    public:

        byte *lcd_control; 
        byte *lcd_status; 
        byte *scroll_x;
        byte *scroll_y;
        byte *windpos_x;
        byte *windpos_y;

        byte *line;

        int clock_count;

        int buffer[PPU_BUFFER_WIDTH][PPU_BUFFER_HEIGHT];

        byte *pallets[3];

        mmu* memory;
        cpu* cp;

        void initialize(mmu* memory, cpu* cp);
        void update_graphics();
        void render_line();


        void set_ldc_display_enable(bool status);
        void set_wnd_tile_map_select(bool status);
        void set_wnd_display_enable(bool status);
        void set_bg_wnd_tile_data_select(bool status);
        void set_bg_tile_map_select(bool status);
        void set_obj_size(bool status);
        void set_obj_display_enable(bool status);
        void set_bg_display(bool status);

        bool get_ldc_display_enable();
        bool get_wnd_tile_map_select();
        bool get_wnd_display_enable();
        bool get_bg_wnd_tile_data_select();
        bool get_bg_tile_map_select();
        bool get_obj_size();
        bool get_obj_display_enable();
        bool get_bg_display();


        // ldc display enable(0=OFF, 1=ON)
        // Window Tile Map Display Select(0=9800-9BFF, 1=9C00-9FFF)
        // Window display enable(0=OFF, 1=ON)
        // BG & Window Tile Data Select(0=8800-97FF, 1=8000-8FFF)
        // BG Tile Map Display Select(0=9800-9BFF, 1=9C000-9FFF)
        // OBJ Size(0=8x8, 1=8x16)
        // OBJ Display Enable(0=OFF, 1=ON)
        // Bg Display(0=OFF, 1=ON)


};