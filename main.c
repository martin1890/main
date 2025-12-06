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

const int region_positions[30][16] = {
{0, 150, 9, 170, 18, 221, 58, 221, 20, 180, 12, 194, 44, 194, 43, 232},
{78, 205, 114, 221, 104, 221, 161, 221, 128, 230, 143, 230, 149, 218, 87, 231},
{175, 187, 209, 197, 193, 221, 240, 221, 214, 225, 207, 231, 229, 218, 221, 206},
{156, 151, 188, 191, 197, 169, 173, 202, 172, 166, 182, 176, 163, 174, 170, 187},
{166, 108, 223, 118, 204, 145, 222, 144, 199, 116, 212, 116, 193, 125, 209, 131},
{211, 147, 233, 180, 243, 194, 223, 172, 247, 176, 262, 173, 255, 192, 245, 158},
{265, 126, 298, 172, 285, 172, 310, 172, 296, 154, 305, 141, 287, 136, 273, 150},
{236, 80, 274, 109, 242, 126, 261, 128, 257, 114, 253, 121, 261, 103, 265, 90},
{284, 58, 300, 70, 311, 65, 310, 106, 305, 90, 303, 96, 290, 99, 298, 111},
{277, 27, 289, 51, 288, 31, 311, 30, 299, 58, 303, 48, 299, 35, 281, 54},
{274, 0, 291, 0, 301, 0, 311, 0, 279, 2, 301, 20, 290, 21, 311, 20},
{253, 0, 265, 24, 256, 17, 274, 25, 268, 18, 260, 9, 270, 9, 257, 0},
{224, 32, 240, 53, 262, 45, 250, 39, 245, 81, 251, 59, 255, 70, 232, 79},
{195, 55, 200, 78, 211, 59, 201, 59, 210, 90, 211, 80, 221, 71, 223, 62},
{192, 17, 208, 20, 238, 25, 199, 35, 209, 41, 213, 47, 220, 23, 228, 49},
{195, 0, 224, 0, 234, 0, 244, 2, 212, 10, 206, 0, 201, 7, 216, 0},
{138, 67, 162, 70, 172, 71, 185, 71, 179, 98, 171, 90, 145, 92, 163, 96},
{157, 30, 171, 37, 181, 42, 161, 32, 184, 62, 172, 59, 163, 52, 190, 53},
{157, 0, 176, 1, 166, 6, 186, 0, 176, 21, 189, 25, 195, 17, 182, 31},
{49, 155, 79, 167, 89, 161, 68, 159, 55, 162, 66, 179, 66, 189, 79, 158},
{62, 114, 89, 137, 66, 137, 98, 138, 78, 150, 124, 156, 89, 128, 76, 119},
{85, 81, 120, 96, 93, 92, 102, 112, 107, 104, 106, 92, 115, 117, 91, 113},
{36, 91, 54, 96, 44, 113, 48, 136, 65, 109, 54, 116, 65, 100, 77, 102},
{0, 86, 11, 96, 0, 112, 0, 92, 27, 111, 33, 101, 23, 99, 12, 116},
{15, 45, 49, 59, 36, 51, 25, 72, 37, 73, 37, 79, 50, 82, 60, 76},
{66, 40, 84, 69, 102, 45, 74, 77, 99, 76, 102, 66, 93, 57, 94, 43},
{50, 14, 77, 39, 66, 27, 55, 21, 70, 62, 56, 41, 66, 50, 75, 30},
{61, 0, 72, 1, 93, 19, 117, 3, 88, 4, 84, 12, 103, 6, 108, 23},
{0, 17, 13, 39, 1, 25, 6, 67, 2, 59, 2, 46, 14, 59, 10, 30},
{7, 0, 22, 10, 40, 24, 36, 0, 28, 31, 13, 13, 26, 1, 48, 2}
};

// ===== Random number generator =====

static unsigned int rng_state = 1;
static unsigned int entropy_counter = 1;

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

// Draw a faction sprite at position (x, y)
void draw_faction_sprite(int x, int y, const unsigned char* sprite, int sprite_width, int sprite_height, int faction_color)
{
    volatile unsigned char* VGA = (volatile unsigned char*)0x08000000;
    const int screen_width = 320;
    const int screen_height = 240;
    unsigned char fc = (unsigned char)faction_color;

    for (int j = 0; j < sprite_height; j++)
    {
        for (int i = 0; i < sprite_width; i++)
        {
            unsigned char color = sprite[j * sprite_width + i];

            if (color == 0)
                continue;
            if (color == 252)
                color = fc;

            int px = x + i;
            int py = y + j;

            if (px < 0 || px >= screen_width || py < 0 || py >= screen_height)
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

// ===== Game start / setup =====

void start_game(int num_players, unsigned char player_colors[4],
    int player_countries[4][15], int player_country_counts[4])
{
    draw_sprite(0, 0, game_map, 320, 240);

    for (int i = 0; i < num_players; i++) {
        for (int n = 0; n < player_country_counts[i]; n++) {
            int region_id = player_countries[i][n];   // 1..30
            int idx = region_id - 1;                  // 0..29

            int region_x = region_positions[idx][2];  // välj vilken punkt du vill
            int region_y = region_positions[idx][3];

            draw_faction_sprite(region_x, region_y, soldat_sprite, 9, 19, player_colors[i]);
        }
    }

    while (1) {
    }
}


void setup_and_start_game(int num_players)
{
    // Seed RNG from timer (or any changing source)
    volatile unsigned int* TIMER = (volatile unsigned int*)0x4000020;
    seed_rng(*TIMER);

    const unsigned char AVAILABLE_COLORS[4] = { 252, 38, 200, 12 };

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

    entropy_counter = entropy_counter * 1664525u + 1013904223u;

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
