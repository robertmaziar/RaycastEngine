#include <SDL.h>
#include <stdio.h>
#include "player.h"
#include "raycaster.h"
#include "map.h"
#include "timer.h"
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Raycast Engine",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Player player = create_player(2.0f, 2.0f, 0.0f);  // Initialize player
    start_timer();

    bool running = true;
    while (running) {
        // Update time for this frame
        update_timer();

        // Handle events
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        // Handle player input
        handle_input(&player, game_map, &running);

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render walls
        render_walls(renderer, &player, SCREEN_WIDTH, SCREEN_HEIGHT);

        // Present the screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
