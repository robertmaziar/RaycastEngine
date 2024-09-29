#include "player.h"
#include <math.h>
#include "timer.h"

#define M_PI_2 (M_PI / 2.0)

Player create_player(float x, float y, float angle) {
	Player player = { x, y, angle, 5.0f, 3.0f }; // Initial speed values
	return player;
}

void handle_input(Player* player, int(*map)[8], bool* running) {
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	if (keystates[SDL_SCANCODE_ESCAPE]) {
		*running = false;
	}

	if (keystates[SDL_SCANCODE_W]) {
		float nextX = player->x + cos(player->angle) * player->moveSpeed * deltaTime;
		float nextY = player->y + sin(player->angle) * player->moveSpeed * deltaTime;

		if (!is_wall_collision(nextX, nextY, map))
		{
			player->x = nextX;
			player->y = nextY;
		}
	}
	if (keystates[SDL_SCANCODE_S]) {
		float nextX = player->x - cos(player->angle) * player->moveSpeed * deltaTime;
		float nextY = player->y - sin(player->angle) * player->moveSpeed * deltaTime;

		if (!is_wall_collision(nextX, nextY, map))
		{
			player->x = nextX;
			player->y = nextY;
		}
	}
	if (keystates[SDL_SCANCODE_A]) {
		player->angle -= player->rotSpeed * deltaTime;
	}
	if (keystates[SDL_SCANCODE_D]) {
		player->angle += player->rotSpeed * deltaTime;
	}
	if (keystates[SDL_SCANCODE_E])
	{
		float strafeAngle = player->angle + M_PI_2;  // 90 degrees to the left
		float nextX = player->x + cos(strafeAngle) * player->moveSpeed * deltaTime;
		float nextY = player->y + sin(strafeAngle) * player->moveSpeed * deltaTime;

		if (!is_wall_collision(nextX, nextY, map))
		{
			player->x = nextX;
			player->y = nextY;
		}
	}
	if (keystates[SDL_SCANCODE_Q])
	{
		float strafeAngle = player->angle - M_PI_2;  // 90 degrees to the left
		float nextX = player->x + cos(strafeAngle) * player->moveSpeed * deltaTime;
		float nextY = player->y + sin(strafeAngle) * player->moveSpeed * deltaTime;

		if (!is_wall_collision(nextX, nextY, map))
		{
			player->x = nextX;
			player->y = nextY;
		}
	}
}

bool is_wall_collision(float x, float y, int(*map)[8])
{
	int mapX = (int)x;
	int mapY = (int)y;

	if (mapX < 0 || mapX >= 8 || mapY <= 0 || mapY >= 8)
	{
		// Out of bounds
		return true;
	}

	// Return true if it's a wall, or false if not
	return map[mapX][mapY] == 1;
}
