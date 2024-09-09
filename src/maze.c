// main.c
#include "headers/maze.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *window = SDL_CreateWindow("The Maze 3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Player player = {5, 5, 0};  // Start in the middle of the map

    // Load the wall texture
    wall_texture = load_texture(renderer, "textures/Bricks.png");
    if (!wall_texture) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load the ceiling texture
    ceiling_texture = load_texture(renderer, "textures/ceiling-sky.png");
    if (!ceiling_texture) {
        SDL_DestroyTexture(wall_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int running = 1;
    SDL_Event event;
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Handle input
        handle_input(&player, keyState);

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the textured floor and ceiling
        render_textured_floor_and_ceiling(renderer, player);

        // Render walls with textures
        render_walls(renderer, player);

        // Render the 2D map
        render_map(renderer, player);

        // Present renderer
        SDL_RenderPresent(renderer);

        SDL_Delay(16);  // ~60 FPS
    }

    // Cleanup
    SDL_DestroyTexture(wall_texture);
    SDL_DestroyTexture(ceiling_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
