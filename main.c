#include "map.h"

const unsigned char soldat_sprite[9 * 19] = {
    0,0,0,0,36,0,0,0,109,
    0,0,36,36,109,36,36,0,172,
    0,36,109,109,109,109,109,36,172,
    0,36,36,36,36,36,36,36,172,
    0,250,255,3,250,3,255,250,172,
    0,136,136,136,136,136,136,136,172,
    0,136,136,246,246,246,136,136,172,
    0,0,136,136,136,136,136,0,172,
    0,36,36,36,36,36,36,36,172,
    0,250,36,109,109,109,36,250,172,
    0,36,36,36,109,109,36,250,172,
    36,252,252,252,36,109,36,250,172,
    36,252,252,252,36,109,109,36,250,
    36,252,252,252,36,109,109,36,172,
    0,36,36,36,109,109,109,36,172,
    0,36,109,109,109,109,109,36,172,
    0,36,36,36,36,36,36,36,172,
    0,252,252,0,0,0,252,252,172,
    0,136,136,0,0,0,136,136,172
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

void draw_rect(int x, int y, int width, int height, int color)
{
    volatile unsigned char* VGA = (volatile unsigned char*)0x08000000;
    const int screen_width = 320;
    unsigned char c = (unsigned char)color;

    int x0 = x;
    int y0 = y;
    int x1 = x + width - 1;
    int y1 = y + height - 1;

    // Top border
    for (int xi = x0; xi <= x1; xi++)
        VGA[y0 * screen_width + xi] = c;

    // Bottom border
    if (y1 != y0)
    {
        for (int xi = x0; xi <= x1; xi++)
            VGA[y1 * screen_width + xi] = c;
    }

    // Left and right borders
    for (int yi = y0 + 1; yi <= y1 - 1; yi++)
    {
        VGA[yi * screen_width + x0] = c;
        if (x1 != x0)
            VGA[yi * screen_width + x1] = c;
    }
}

// Draw one start menu box (same size and color as old start_menu sprite)
void draw_filled_rect(int x, int y, int width, int height, int color)
{
    // Draw the outer border
    draw_rect(x, y, width, height, color);

    // Shrink rectangle for inner fill
    int inner_x = x + 1;
    int inner_y = y + 1;
    int inner_w = width - 2;
    int inner_h = height - 2;

    // Base case: stop when there is no room left for an inner rectangle
    if (inner_w < 2 || inner_h < 2)
    {
        // For very small inside (1 pixel wide or high), we can optionally
        // just fill the last line(s) manually if you vill ha det absolut 100% tätt,
        // men med draw_rect-logiken ovan är det redan täckt ganska bra.
        return;
    }

    // Recursive call to fill inner area
    draw_filled_rect(inner_x, inner_y, inner_w, inner_h, color);
}

void option_select(int x, int y, int width, int height, int background_color)
{
    static int prev_x = 0;
    static int prev_y = 0;
    static int prev_w = 0;
    static int prev_h = 0;
    static int has_prev = 0;

    // Remove previous selection border by drawing over it with background color
    if (has_prev)
    {
        draw_rect(prev_x, prev_y, prev_w, prev_h, background_color);
    }

    // Draw new selection border with constant color 216
    draw_rect(x, y, width, height, 216);

    // Remember this selection for next time
    prev_x = x;
    prev_y = y;
    prev_w = width;
    prev_h = height;
    has_prev = 1;
}

// ===== Random number generator =====

static unsigned int rng_state = 1;

void seed_rng(unsigned int seed)
{
    if (seed == 0) seed = 1;
    rng_state = seed;
}

// Simple LCG
unsigned int rand_u32(void)
{
    rng_state = rng_state * 1664525u + 1013904223u;
    return rng_state;
}

// Random integer in [0, max-1]
int rand_range(int max)
{
    if (max <= 0) return 0;
    return (int)(rand_u32() % (unsigned int)max);
}

// ===== Game start / setup =====

void start_game(int num_players, unsigned char player_colors[4],
    int player_countries[4][15], int player_country_counts[4])
{
    // TODO: implement actual game here
    draw_sprite(0, 0, game_map, 320, 240);
    while (1)
    {
    }
}

void setup_and_start_game(int num_players)
{
    // Seed RNG from timer (or any changing source)
    volatile unsigned int* TIMER = (volatile unsigned int*)0x4000020;
    seed_rng(*TIMER);

    const unsigned char AVAILABLE_COLORS[4] = { 252, 38, 180, 12 };

    unsigned char player_colors[4];
    int player_country_counts[4] = { 0, 0, 0, 0 };
    int player_countries[4][15];

    // ---- Randomize colors (Fisher-Yates shuffle) ----
    unsigned char colors[4];
    for (int i = 0; i < 4; i++)
        colors[i] = AVAILABLE_COLORS[i];

    for (int i = 3; i > 0; i--)
    {
        int j = rand_range(i + 1);
        unsigned char tmp = colors[i];
        colors[i] = colors[j];
        colors[j] = tmp;
    }

    for (int p = 0; p < num_players; p++)
        player_colors[p] = colors[p];

    // ---- Prepare list of countries 1..30 ----
    int all_countries[30];
    for (int i = 0; i < 30; i++)
        all_countries[i] = i + 1;

    // Shuffle countries
    for (int i = 29; i > 0; i--)
    {
        int j = rand_range(i + 1);
        int tmp = all_countries[i];
        all_countries[i] = all_countries[j];
        all_countries[j] = tmp;
    }

    // ---- Deal countries round-robin to players ----
    int current_player = 0;
    for (int i = 0; i < 30; i++)
    {
        int p = current_player % num_players;
        int idx = player_country_counts[p];
        if (idx < 15)
        {
            player_countries[p][idx] = all_countries[i];
            player_country_counts[p]++;
        }
        current_player++;
    }

    // ---- Start the actual game ----
    start_game(num_players, player_colors, player_countries, player_country_counts);
}

// ===== Updated start menu logic (switch + button) =====

void update_start_menu()
{
    static int current_index = 0;   // 0 -> 2 players, 1 -> 3, 2 -> 4
    static int prev_switch = 0;
    static int prev_button = 0;
    static int initialized = 0;

    volatile unsigned int* SWITCH = (volatile unsigned int*)0x4000010;
    volatile unsigned int* BUTTON = (volatile unsigned int*)0x40000d0;

    int sw = (*SWITCH) & 1;   // Least significant bit of switch bank
    int btn = (*BUTTON) & 1;  // Least significant bit of buttons

    // First call: draw initial selection
    if (!initialized)
    {
        initialized = 1;
        prev_switch = sw;
        prev_button = btn;
        option_select(60, 30, 200, 36, 36);  // start at "2 players"
        return;
    }

    // --- Handle switch toggle to move selection ---
    if (sw != prev_switch)
    {
        prev_switch = sw;

        current_index++;
        if (current_index >= 3)
            current_index = 0;

        if (current_index == 0)
            option_select(60, 30, 200, 36, 36);
        else if (current_index == 1)
            option_select(60, 102, 200, 36, 36);
        else
            option_select(60, 174, 200, 36, 36);
    }

    // --- Handle button press to confirm selection ---
    // Here we react on a rising edge (0 -> 1)
    if (btn == 1 && prev_button == 0)
    {
        int num_players;
        if (current_index == 0)      num_players = 2;
        else if (current_index == 1) num_players = 3;
        else                         num_players = 4;

        setup_and_start_game(num_players);
    }

    prev_button = btn;
}

int main()
{
    draw();
    
    draw_color_grid();
    draw_sprite(50, 100, soldat_sprite, 9, 19);
    draw_sprite(300, 100, soldat_sprite, 9, 19);
    draw_filled_rect(60, 30, 200, 36, 36);
    draw_filled_rect(60, 102, 200, 36, 36);
    draw_filled_rect(60, 174, 200, 36, 36);
    // Enter a forever loop
    while (1)
    {
        update_start_menu();
    }
}
