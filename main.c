const unsigned char plus_sprite[8 * 8] = {
    0,0,0,255,255,0,0,0,
    0,100,0,255,255,0,50,0,
    0,0,0,255,255,0,0,0,
    255,255,255,255,255,255,255,255,
    255,255,255,255,255,255,255,255,
    0,0,0,255,255,0,0,0,
    0,70,0,255,255,0,150,0,
    0,0,0,255,255,0,0,0
};


// Empty interrupt handler
void handle_interrupt(unsigned _irq)
{
}

// Draw a sprite at position (x, y)
void draw_sprite(int x, int y, const unsigned char* sprite, int sprite_width, int sprite_height)
{
    volatile char* VGA = (volatile char*)0x08000000; // Base address of VGA memory
    int screen_width = 320;

    for (int j = 0; j < sprite_height; j++)
    {
        for (int i = 0; i < sprite_width; i++)
        {
            // Read pixel from sprite
            unsigned char color = sprite[j * sprite_width + i];

            // Example: treat color 0 as transparent
            if (color == 0)
                continue;

            int px = x + i;
            int py = y + j;

            // Bounds check so we do not write outside the screen
            if (px < 0 || px >= screen_width || py < 0 || py >= 240)
                continue;

            VGA[py * screen_width + px] = color;
        }
    }
}

void draw_color_grid()
{
    volatile unsigned char* VGA = (volatile unsigned char*)0x08000000;
    int screen_width = 320;
    int screen_height = 240;
    int tile_size = 16;              // 16x16 blocks
    int tiles_per_row = screen_width / tile_size; // 20

    for (int y = 0; y < screen_height; y++)
    {
        int tile_y = y / tile_size;
        for (int x = 0; x < screen_width; x++)
        {
            int tile_x = x / tile_size;
            int color_index = tile_y * tiles_per_row + tile_x; // 0..299

            if (color_index > 255)
                color_index = 0;      // Extra tiles become color 0

            VGA[y * screen_width + x] = (unsigned char)color_index;
        }
    }
}



void draw() {
    // Create a pointer called VGA that points to the drawing area
    volatile char* VGA = (volatile char*)0x08000000;

    // Clear the entire VGA buffer area by writing the value 0 (=black)
    for (int i = 0; i < 320 * 480; i++)
        VGA[i] = 0;

    // Draw five rows of white pixels (remember that screen is 320 pixels wide and the color 255 is white)
    for (int i = 0; i < 320 * 5; i++)
        VGA[320 * 118 + i] = 255;
}

int main()
{
    draw();
    draw_sprite(50, 100, plus_sprite, 8, 8);
    draw_color_grid();

    // Enter a forever loop
    while (1)
    {
    }
}
