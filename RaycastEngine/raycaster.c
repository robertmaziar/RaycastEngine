#include "raycaster.h"
#include "map.h"
#include <math.h>
#include <stdbool.h>

void render_walls(SDL_Renderer* renderer, Player* player, int screenWidth, int screenHeight) {
    for (int x = 0; x < screenWidth; x++) {
        float rayAngle = player->angle - (M_PI / 6) + (x / (float)screenWidth) * (M_PI / 3);
        float rayX = cos(rayAngle);
        float rayY = sin(rayAngle);

        float distanceToWall = 0.0f;
        bool hitWall = false;

        while (!hitWall && distanceToWall < 30.0f) {
            distanceToWall += 0.1f;
            int testX = (int)(player->x + rayX * distanceToWall);
            int testY = (int)(player->y + rayY * distanceToWall);

            if (testX < 0 || testX >= map_width() || testY < 0 || testY >= map_height()) {
                hitWall = true;
                distanceToWall = 30.0f;
            }
            else if (map_get_value(testX, testY) == 1) {
                hitWall = true;
            }
        }

        int wallHeight = (int)(screenHeight / distanceToWall);
        int wallTop = (screenHeight - wallHeight) / 2;
        int wallBottom = (screenHeight + wallHeight) / 2;

        // --- Render the ceiling ---
       // Set the ceiling color (e.g., a light blue color)
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky blue
        // Draw the ceiling from the top of the screen to the top of the wall
        SDL_RenderDrawLine(renderer, x, 0, x, wallTop);

        // --- Render the wall ---
        // Wall color based on distance (darker the farther away)
        Uint8 color = (Uint8)(255 / (distanceToWall + 1));
        SDL_SetRenderDrawColor(renderer, color, color, color, 255);
        // Draw vertical slice of the wall
        SDL_RenderDrawLine(renderer, x, wallTop, x, wallBottom);

        // --- Render the floor ---
        // Set the floor color (e.g., gray)
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Gray for the floor
        // Draw the floor from the bottom of the wall to the bottom of the screen
        SDL_RenderDrawLine(renderer, x, wallBottom, x, screenHeight);
    }
}
