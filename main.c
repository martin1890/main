// Empty interrupt handler
void handle_interrupt(unsigned _irq)
{
}


#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240
#define TRANSPARENT_COLOR 254






void draw_sprite(volatile char* VGA, int x, int y, const unsigned char* sprite, int sprite_width, int sprite_height)
{
    for (int row = 0; row < sprite_height; row++) {
        for (int col = 0; col < sprite_width; col++) {
            unsigned char color = sprite[row * sprite_width + col];

            // Skip transparent pixels
            if (color == TRANSPARENT_COLOR)
                continue;

            int screen_x = x + col;
            int screen_y = y + row;

            // Clip sprite to screen bounds
            if (screen_x < 0 || screen_x >= SCREEN_WIDTH ||
                screen_y < 0 || screen_y >= SCREEN_HEIGHT)
                continue;

            VGA[screen_y * SCREEN_WIDTH + screen_x] = color;
        }
    }
}




void draw() {
    // Create a pointer called VGA that points to the drawing area
    volatile char* VGA = (volatile char*)0x08000000;

    // Clear the entire VGA buffer area by writing the value 0 (=black)
    for (int i = 0; i < 320 * 480; i++) {
        VGA[i] = 0;
    }

    int p = 0;
    // Draw five rows of white pixels (remember that screen is 320 pixels wide and the color 255 is white)
    for (int i = 0; i < 320 * 5; i++) {

        p++;
        if (p == 256) {
            p = 0;
        }
        VGA[320 * 118 + i] = p;
    }
}

int main()
{
    const unsigned char smiley_sprite[4 * 4] = {
    0, 255, 255, 0,
    255, 0,   0, 255,
    255, 255, 255, 255,
    0,   255, 255, 0
    };


    draw();

    draw_sprite(VGA, 50, 50, smiley_sprite, 4, 4);

    // Enter a forever loop
    while (1)
    {
    }
}
