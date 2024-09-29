#pragma once

// Define map dimensions (this can be shared across files)
#define MAP_WIDTH 8
#define MAP_HEIGHT 8

// Declare the map globally (use 'extern' to indicate it's defined elsewhere)
extern int game_map[MAP_WIDTH][MAP_HEIGHT];

int map_get_value(int x, int y);
int map_width();
int map_height();