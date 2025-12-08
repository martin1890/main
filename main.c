#include "map.h"
#include "borders.h"
#include "menus.h"


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
    0,0,252,252,0,252,252,0,172,
    0,0,136,136,0,136,136,0,172
};

const unsigned char house_sprite[9 * 8] = {
    0, 0, 0, 0, 36, 0, 0, 0, 0,
    0, 0, 0, 36, 252, 36, 0, 0, 0,
    0, 0, 36, 252, 252, 252, 36, 0, 0,
    0, 36, 252, 252, 252, 252, 252, 36, 0,
    36, 36, 36, 36, 36, 36, 36, 36, 36,
    0, 36, 136, 136, 136, 136, 136, 36, 0,
    0, 36, 136, 136, 136, 136, 136, 36, 0,
    0, 36, 36, 36, 36, 36, 36, 36, 0
};

const unsigned char castle_sprite[11 * 5] = {
    36, 36, 36, 0, 36, 36, 36, 0, 36, 36, 36,
    36, 109, 36, 36, 36, 109, 36, 36, 36, 109, 36,
    36, 109, 109, 109, 109, 109, 109, 109, 109, 109, 36,
    36, 109, 109, 109, 36, 36, 36, 109, 109, 109,36,
    36, 109, 109, 109, 36, 136, 36, 109, 109, 109, 36
};


const int region_positions[30][16] = {
{0, 150, 9, 170, 18, 221, 58, 221, 20, 180, 12, 194, 44, 194, 43, 232},
{78, 205, 114, 221, 104, 221, 161, 221, 128, 230, 143, 230, 149, 218, 87, 231},
{175, 187, 209, 197, 193, 221, 236, 221, 214, 225, 207, 231, 225, 218, 221, 206},
{156, 151, 188, 191, 197, 169, 173, 202, 172, 166, 182, 176, 163, 174, 170, 187},
{166, 108, 223, 118, 204, 145, 222, 144, 199, 116, 212, 116, 193, 125, 209, 131},
{211, 147, 233, 180, 246, 167, 223, 172, 233, 170, 260, 179, 258, 162, 245, 158},
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

const int move_targets[30][7] = {
{2, 20, 0, 0, 0, 0, 0},
{1, 3, 4, 0, 0, 0, 0},
{2, 4, 6, 0, 0, 0, 0},
{2, 3, 6, 5, 0, 0, 0},
{4, 6, 8, 0, 0, 0, 0},
{7, 8, 5, 4, 3, 0, 0},
{9, 8, 6, 0, 0, 0, 0},
{5, 6, 7, 9, 13, 0, 0},
{8, 7, 10, 13, 0, 0, 0},
{9, 11, 12, 13, 0, 0, 0},
{12, 10, 0, 0, 0, 0, 0},
{16, 15, 13, 10, 11, 0, 0},
{8, 10, 12, 15, 14, 0, 0},
{13, 15, 18, 17, 0, 0, 0},
{18, 14, 13, 12, 16, 19, 18},
{15, 12, 19, 0, 0, 0, 0},
{22, 14, 18, 0, 0, 0, 0},
{17, 14, 15, 19, 0, 0, 0},
{18, 15, 16, 0, 0, 0, 0},
{1, 21, 23, 0, 0, 0, 0},
{23, 20, 22, 0, 0, 0, 0},
{23, 21, 17, 26, 0, 0, 0},
{24, 20, 21, 22, 26, 25, 0},
{23, 25, 29, 0, 0, 0, 0},
{24, 23, 26, 27, 30, 29, 0},
{25, 23, 22, 28, 27, 0, 0},
{25, 26, 28, 30, 0, 0, 0},
{27, 26, 30, 0, 0, 0, 0},
{24, 25, 30, 0, 0, 0, 0},
{29, 25, 27, 28, 0, 0, 0},
};

const int MENU_positions_MAIN[4][4] = {
    { 250, 193, 64, 12 },
    { 250, 205, 61, 10 },
    { 250, 215, 29, 12 },
    { 250, 227, 50, 10 }
};

const int MENU_positions_BATTLE[2][4] =
{
{249, 194, 46, 9},
{249, 204, 46, 8}
};

const int menu_positions[23][4] = {
    {250, 193, 64, 12},
    {250, 205, 61, 10},
    {250, 215, 29, 12},
    {250, 227, 50, 10},
    {249, 194, 46, 9}, //MENU_positions_BATTLE
    {249, 204, 46, 8},
    {250, 193, 64, 12}, //MENU_positions_MARCH
    {250, 205, 64, 13},
    {250, 227, 64, 10},
    {250, 198, 320, 240},  //MENU_positions_BUY
    {263, 204, 11, 10},
    {257, 207, 13, 7},
    {250, 227, 50, 10},
    {249, 194, 48, 12},  //MENU_positions_SIEGE
    {249, 213, 47, 10},
    {249, 194, 70, 45}  //MENU_positions_AFTER_BATTLE
    {249, 194, 63, 24}  //MENU_positions_SIEGE_TURN_END
    {249, 194, 66, 22},  //MENU_positions_WILL_SORTIE
    {264, 223, 13, 10},
    {281, 223, 18, 10},
    {249, 194, 46, 9},  //MENU_positions_SORTIE
    {249, 204, 46, 8},
    {249, 214, 15, 8}
};

enum {
    MENU_AFTER_BATTLE = 0,
    MENU_BATTLE,
    MENU_BUY,
    MENU_MAIN,
    MENU_MARCH,
    MENU_SIEGE,
    MENU_SIEGE_TURN_END,
    MENU_SORTIE,
    MENU_WILL_SORTIE,
    MENU_COUNT
};


#define SWITCH_ADDR 0x4000010
#define BUTTON_ADDR 0x40000d0
#define VGA_ADDR 0x08000000

volatile unsigned char* const VGA = (volatile unsigned char*)VGA_ADDR;
volatile unsigned int* const SWITCH = (volatile unsigned int*)SWITCH_ADDR;
volatile unsigned int* const BUTTON = (volatile unsigned int*)BUTTON_ADDR;
static int has_prev = 0;

#define NUM_REGIONS 30
#define REGION_SOLDIERS 0
#define REGION_HOUSES   1
#define REGION_CASTLE   2

int gold[4] = { 0, 0, 0, 0 };
int region_state[NUM_REGIONS][3];
unsigned char g_player_colors[4] = { 0, 0, 0, 0 }; // copied from player_colors

#define GAME_MENU_ACTION 0
#define GAME_MENU_MOVE   1

#define BORDER_SELECT_ACTION 0
#define BORDER_SELECT_MOVE   1

static int selected_action_region = -1; // 1..30, -1 = ingen
static int selected_move_region = -1; // 1..30, -1 = ingen

typedef struct {
    int initialized;
    int prev_switch;
    int prev_button;
} InputState;

// Read raw switch/button and detect edges
void read_input(InputState* state,
    int* sw_value, int* btn_value,
    int* switch_toggled, int* button_rising)
{
    int sw = (*SWITCH) & 1;
    int btn = (*BUTTON) & 1;

    if (!state->initialized)
    {
        state->initialized = 1;
        state->prev_switch = sw;
        state->prev_button = btn;
        *switch_toggled = 0;
        *button_rising = 0;
    }
    else
    {
        *switch_toggled = (sw != state->prev_switch);
        *button_rising = (btn == 1 && state->prev_button == 0);

        state->prev_switch = sw;
        state->prev_button = btn;
    }

    *sw_value = sw;
    *btn_value = btn;
}


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
        return;
    }

    // Recursive call to fill inner area
    draw_filled_rect(inner_x, inner_y, inner_w, inner_h, color);
}

void spawn_soldier(int x, int y, int color)
{
    draw_faction_sprite(x, y, soldat_sprite, 9, 19, color);
}

void spawn_house(int x, int y)
{
    draw_sprite(x, y, house_sprite, 9, 8);
}

void spawn_castle(int x, int y)
{
    // 11x5, enligt din castle_sprite
    draw_sprite(x, y, castle_sprite, 11, 5);
}

void buy_castle(int turn_player)
{
    // valid player?
    if (turn_player < 0 || turn_player >= 4)
        return;

    // need 5 gold
    if (gold[turn_player] < 5)
        return;

    // need a selected action region
    if (selected_action_region < 1 || selected_action_region > NUM_REGIONS)
        return;

    int idx = selected_action_region - 1; // 0..29

    // already has a castle?
    if (region_state[idx][REGION_CASTLE] != 0)
        return;

    // pay
    gold[turn_player] -= 5;

    // mark castle present
    region_state[idx][REGION_CASTLE] = 1;

    // draw castle at its position
    int x = region_positions[idx][8];
    int y = region_positions[idx][9];
    spawn_castle(x, y);
}

void buy_house(int turn_player)
{
    // check valid player
    if (turn_player < 0 || turn_player >= 4)
        return;

    // need at least 3 gold
    if (gold[turn_player] < 3)
        return;

    // need a selected action region
    if (selected_action_region < 1 || selected_action_region > NUM_REGIONS)
        return;

    int idx = selected_action_region - 1; // 0..29

    // max 3 houses
    int before = region_state[idx][REGION_HOUSES];
    if (before >= 3)
        return;

    // pay
    gold[turn_player] -= 3;

    int after = before + 1;
    region_state[idx][REGION_HOUSES] = after;

    // place the new house at correct slot
    if (after == 1)
    {
        int x = region_positions[idx][10];
        int y = region_positions[idx][11];
        spawn_house(x, y);
    }
    else if (after == 2)
    {
        int x = region_positions[idx][12];
        int y = region_positions[idx][13];
        spawn_house(x, y);
    }
    else if (after == 3)
    {
        int x = region_positions[idx][14];
        int y = region_positions[idx][15];
        spawn_house(x, y);
    }
}

void buy_soldier(int turn_player)
{
    // invalid player index guard
    if (turn_player < 0 || turn_player >= 4)
        return;

    // need at least 3 gold
    if (gold[turn_player] < 3)
        return;

    // need a selected action region
    if (selected_action_region < 1 || selected_action_region > NUM_REGIONS)
        return;

    int idx = selected_action_region - 1; // 0..29

    // pay
    gold[turn_player] -= 3;

    int before = region_state[idx][REGION_SOLDIERS];
    if (before < 0) before = 0;

    region_state[idx][REGION_SOLDIERS] = before + 1;
    int after = region_state[idx][REGION_SOLDIERS];

    // draw new soldier sprite only if we have 1..2 visible positions
    // if there is 1 soldier -> use positions[2], [3]
    // if there are 2 soldiers -> use positions[4], [5]

    if (after == 1)
    {
        spawn_soldier(region_positions[idx][2], region_positions[idx][3], g_player_colors[turn_player]);
    }
    else if (after == 2)
    {
        spawn_soldier(region_positions[idx][4], region_positions[idx][5], g_player_colors[turn_player]);
    }
    else if (after == 3)
    {
        spawn_soldier(region_positions[idx][6], region_positions[idx][7], g_player_colors[turn_player]);
    }
}


void init_region_state(void)
{
    for (int i = 0; i < NUM_REGIONS; i++)
    {
        region_state[i][REGION_SOLDIERS] = 1; // alla 
        region_state[i][REGION_HOUSES] = 0; // inga hus
        region_state[i][REGION_CASTLE] = 0; // ingen borg
    }
}

void option_select(int x, int y, int width, int height, int selection_color, int background_color)
{
    static int prev_x = 0;
    static int prev_y = 0;
    static int prev_w = 0;
    static int prev_h = 0;

    // Remove previous selection border by drawing over it with background color
    if (has_prev)
    {
        draw_rect(prev_x, prev_y, prev_w, prev_h, background_color);
    }

    // Draw new selection border with constant color 216
    draw_rect(x, y, width, height, selection_color);

    // Remember this selection for next time
    prev_x = x;
    prev_y = y;
    prev_w = width;
    prev_h = height;
    has_prev = 1;
}

void border_select(int region, int select_type)
{
    if (region < 1 || region > 30)
        return; // ogiltigt regions-id

    int color_select;
    int* prev_region_ptr;

    if (select_type == BORDER_SELECT_MOVE) {
        color_select = 220;                 
        prev_region_ptr = &selected_move_region;
    }
    else {
        color_select = 132;                 
        prev_region_ptr = &selected_action_region;
    }

    int idx = region - 1;                   // 0..29

    // Avselektera tidigare region i samma kategori (om den finns)
    if (*prev_region_ptr >= 1 && *prev_region_ptr <= 30 && *prev_region_ptr != region)
    {
        int prev_idx = *prev_region_ptr - 1;
        int px = region_positions[prev_idx][0];
        int py = region_positions[prev_idx][1];
        const BorderInfo* pb = &borders[prev_idx];
 
        draw_faction_sprite(px, py, pb->data, pb->width, pb->height, 36);
    }


    *prev_region_ptr = region;


    int x = region_positions[idx][0];
    int y = region_positions[idx][1];
    const BorderInfo* b = &borders[idx];
    draw_faction_sprite(x, y, b->data, b->width, b->height, color_select);
}

void next_action_region(int turn_player,
    int player_countries[4][15],
    int player_country_counts[4])
{
    static int current_region_index = 0; // index in current player's country list
    static int last_turn_player = -1;
    static int initialized = 0;

    // If first call or player turn changed, reset index
    if (!initialized || last_turn_player != turn_player)
    {
        initialized = 1;
        last_turn_player = turn_player;
        current_region_index = 0;
    }

    int country_count = player_country_counts[turn_player];
    if (country_count <= 0)
        return;

    int region_id = player_countries[turn_player][current_region_index]; // 1..30
    border_select(region_id, BORDER_SELECT_ACTION);

    // Advance index with wrap
    current_region_index++;
    if (current_region_index >= country_count)
        current_region_index = 0;
}


void next_move_target(void)
{
    extern const int move_targets[30][7]; // adjacency table
    extern int selected_action_region;    // from border_select

    static int current_target_index = 0;  // index into move_targets row
    static int last_source_region = -1;
    static int initialized = 0;

    if (!initialized)
    {
        initialized = 1;
        current_target_index = 0;
        last_source_region = -1;
    }

    // Need a valid source region selected for ACTION
    if (selected_action_region < 1 || selected_action_region > 30)
        return;

    int src_region = selected_action_region;
    int src_idx = src_region - 1; // 0..29

    // If source region changed, reset cycling index
    if (last_source_region != src_region)
    {
        last_source_region = src_region;
        current_target_index = 0;
    }

    // Find next non-zero neighbor in list
    int tries = 0;
    int target_region = 0;

    while (tries < 7)
    {
        target_region = move_targets[src_idx][current_target_index];
        current_target_index++;
        if (current_target_index >= 7)
            current_target_index = 0;

        if (target_region != 0)
            break;

        tries++;
    }

    if (target_region == 0)
        return; // no valid neighbors

    // Highlight this as MOVE selection
    border_select(target_region, BORDER_SELECT_MOVE);


    border_select(selected_action_region, BORDER_SELECT_ACTION);
}

int index(int key)
{
    switch (key)
    {
    case 0: // MENU_AFTER_BATTLE
        return 15;

    case 1: // MENU_BATTLE
        return 4;

    case 2: // MENU_BUY
        return 9;

    case 3: // MENU_MAIN
        return 0;

    case 4: // MENU_MARCH
        return 6;

    case 5: // MENU_SIEGE
        return 13;

    case 6: // MENU_SIEGE_TURN_END
        return 16;

    case 7: // MENU_SORTIE
        return 20;

    case 8: // MENU_WILL_SORTIE
        return 17;

    default:
        return 0;
    }
}

void draw_menu(int menu_index, int option, int can)
{


    if (menu_index < 0 || menu_index >= 9)
        return;

    const unsigned char* sprite = menu_sprites[menu_index];


    draw_filled_rect(248, 193, 72, 47, 109);
    draw_sprite(248, 193, sprite, 72, 47);

    int color;
    if (can == 1)
        color = 252;
    else
        color = 200;

    option = option + index(menu_index);

    int x = menu_positions[option][0];
    int y = menu_positions[option][1];
    int width = menu_positions[option][2];
    int height = menu_positions[option][3];

    option_select(x, y, width, height, color, 109);
}




void handle_main_menu_selection(int* current_mode,
    int* menu_index,
    int* menu_option_count,
    int* turn_player,
    int player_countries[4][15],
    int player_country_counts[4])
{
    switch (*current_mode)
    {
    case 0:
        next_action_region(*turn_player, player_countries, player_country_counts);
        break;
    case 1:
        *current_mode = 0;
        *menu_option_count = 3;
        *menu_index = 4;
        draw_menu(*menu_index, 0, 1);
        break;
    case 2:
        // samma menu option count some main menu
        *current_mode = 0;
        *menu_index = 2;
        draw_menu(*menu_index, 0, 1);
        break;
    case 3:
        *current_mode = 0;
        *menu_option_count = 1;
        *menu_index = MENU_SIEGE_TURN_END;
        draw_menu(*menu_index, 0, 1);
        break;

    }

}
void handle_march_menu_selection(int* current_mode, int* menu_index, int* menu_option_count)
{
    switch (*current_mode)
    {
    case 0:
        next_move_target();
        break;
    case 1:
        break;
    case 2:
        *menu_option_count = 4;
        *menu_index = 3;
        *current_mode = 1;
        draw_menu(*menu_index, 1, 1);
        break;
    }
}
void handle_buy_menu_selection(int* current_mode, int* menu_index,
    int* menu_option_count, int turn_player)

{
    switch (*current_mode)
    {
    case 0:
        // buy one soldier in the currently selected action region
        buy_soldier(turn_player);
        break;
    case 1:
        // k�p hus
        buy_house(turn_player);
        break;
    case 2:
        buy_castle(turn_player);
        break;
    case 3:
        *menu_index = 3;
        *current_mode = 2;
        //samma menu option count som main menu
        draw_menu(*menu_index, 2, 1);
        break;
    }
}
// ... fler handler-deklarationer efter behov

void game_menu(int* menu_index,
    int* current_mode,
    int* menu_option_count,
    int* turn_player,
    int player_countries[4][15],
    int player_country_counts[4],
    int num_players)
{
    static InputState input_state = { 0 };

    int sw, btn;
    int sw_toggled, btn_rising;

    read_input(&input_state, &sw, &btn, &sw_toggled, &btn_rising);

    // Toggle on switch: go to next option in current menu and redraw menu
    if (sw_toggled)
    {
        (*current_mode)++;
        if (*current_mode >= *menu_option_count)
            *current_mode = 0;

        int can = 1; // TODO: compute real "can" later
        draw_menu(*menu_index, *current_mode, can);
    }

    // Button press: perform action depending on which menu we are in
    if (btn_rising)
    {
        switch (*menu_index)
        {
        case MENU_MAIN:
            handle_main_menu_selection(current_mode, menu_index, menu_option_count, turn_player, player_countries, player_country_counts);
            break;

        case MENU_MARCH:
            handle_march_menu_selection(current_mode, menu_index, menu_option_count);
            break;

        case MENU_BUY:
            handle_buy_menu_selection(current_mode, menu_index, menu_option_count,
                *turn_player);
            break;

        case MENU_SIEGE:
            // handle_siege_menu_selection(...)
            break;

        case MENU_AFTER_BATTLE:
            // ...
            break;

        case MENU_BATTLE:
            // ...
            break;

        case MENU_SIEGE_TURN_END:
            (*turn_player)++;
            if (*turn_player >= num_players) {
                *turn_player = 0;
            }
            *menu_index = MENU_MAIN;
            *current_mode = 0;
            *menu_option_count = 4;
            gold[*turn_player] += player_country_counts[*turn_player];
            draw_menu(*menu_index, *current_mode, 1);
            // ...
            break;

        case MENU_SORTIE:
            // ...
            break;

        case MENU_WILL_SORTIE:
            // ...
            break;

        default:
            break;
        }
    }
}



// ===== Game start / setup =====

void start_game(int num_players, unsigned char player_colors[4],
    int player_countries[4][15], int player_country_counts[4])
{
    int turn_player = 0;

    int game_mode = 0;          // current option in current menu
    int menu_index = MENU_MAIN; // start in main menu
    int menu_option_count = 4;  // main menu has 4 options

    for (int p = 0; p < num_players; p++) {
        g_player_colors[p] = player_colors[p];
    }

    init_region_state();

    draw_sprite(0, 0, game_map, 320, 240);
    draw_rect(247, 192, 73, 48, 36);
    draw_filled_rect(248, 193, 72, 47, 109);



    for (int i = 0; i < num_players; i++) {
        for (int n = 0; n < player_country_counts[i]; n++) {
            int region_id = player_countries[i][n];   // 1..30
            int idx = region_id - 1;                  // 0..29
            spawn_soldier(region_positions[idx][2], region_positions[idx][3], g_player_colors[i]);
        }
    }
    // draw initial menu
    has_prev = 0;
    draw_menu(menu_index, game_mode, 1);

    while (1) {
        game_menu(&menu_index, &game_mode, &menu_option_count,
            &turn_player, player_countries, player_country_counts, num_players);
    }
}


void setup_and_start_game(int num_players)
{

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

    for (int p = 0; p < 4; p++)
        gold[p] = 0;  // nollst�ll

    gold[0] = player_country_counts[0];

    // ---- Start the actual game ----
    start_game(num_players, player_colors, player_countries, player_country_counts);
}

// ===== start menu logic (switch + button) =====

void update_start_menu()
{
    static int current_index = 0;   // 0 -> 2 players, 1 -> 3, 2 -> 4
    static int initialized_selection = 0;
    static InputState input_state = { 0 };

    int sw, btn;
    int sw_toggled, btn_rising;

    read_input(&input_state, &sw, &btn, &sw_toggled, &btn_rising);
    entropy_counter++;

    if (!initialized_selection)
    {
        initialized_selection = 1;
        option_select(60, 30, 200, 36, 216, 36);  // start at "2 players"
        return;
    }

    // Switch toggle: move selection in start menu
    if (sw_toggled)
    {
        current_index++;
        if (current_index >= 3)
            current_index = 0;

        if (current_index == 0)
            option_select(60, 30, 200, 36, 216, 36);
        else if (current_index == 1)
            option_select(60, 102, 200, 36, 216, 36);
        else
            option_select(60, 174, 200, 36, 216, 36);
    }

    // Button press: confirm selection and start game
    if (btn_rising)
    {
        int num_players;
        if (current_index == 0)      num_players = 2;
        else if (current_index == 1) num_players = 3;
        else                         num_players = 4;

        // seed_rng(...);
        unsigned int seed = entropy_counter
            ^ (unsigned int)sw
            ^ ((unsigned int)btn << 8);

        seed_rng(seed);
        setup_and_start_game(num_players);
    }
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