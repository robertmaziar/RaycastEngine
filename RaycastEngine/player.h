#pragma once
#include <SDL.h>
#include <stdbool.h>

typedef struct {
    float x, y;      // Position
    float angle;     // Angle of view
    float moveSpeed; // Speed of movement
    float rotSpeed;  // Speed of rotation
} Player;

Player create_player(float x, float y, float angle);

void handle_input(Player* player, int(*map)[8], bool* running);
bool is_wall_collision(float x, float y, int(*map)[8]);