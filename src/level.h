#ifndef LEVEL_H
#define LEVEL_H

#include <raylib.h>

#define TILE_SIZE 48
#define MAX_PW_SPEED 3
#define MAX_PW_HEALTH 5
#define MAX_PW_INK 2

/* A level is a matrix of cells, each cell is represented using chars.
'.' = free cells
'#' = walls
'I' = ink
'H' = health potion
'S' = speed increase
*/
typedef struct {
    int size_x, size_y;
    char **cells;
    Texture2D texture_pw, texture_t; // Powerups textures.
    int frame_speed_health, frame_ink; // Frames for each texture
} level;

// Create a new level with the given size, allocates memory for it.
level *level_new(int size_x, int size_y);

// Retrieves the cell at a given position, can be used for cells outside the board.
int level_get(const level *lvl, int x, int y);

// Put randomly placed walls of the given size in the level.
void level_fill_random(level *lvl, int wall_size);

// Destroy a level, free its memory.
void level_free(level *lvl);

// Create and place power-ups in the level (5 health potions, 3 speed increase, 2 ink).
void level_powerups(level *lvl);

#endif
