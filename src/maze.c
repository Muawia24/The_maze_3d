// main.c
#include "headers/maze.h"

// render the game
void render_env(SDL_Renderer *renderer, Player player)
{
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
}
int load_all_textures(SDL_Renderer *renderer, SDL_Window *window, const char* file1, const char* file2)
{
    // Load the wall texture
    wall_texture = load_texture(renderer, file1);
    if (!wall_texture) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // Load the ceiling texture
    ceiling_texture = load_texture(renderer, file2);
    if (!ceiling_texture) {
        SDL_DestroyTexture(wall_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    return 0;
}
void clean_up(SDL_Renderer *renderer, SDL_Window *window)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
int main(int argc, char* argv[]) {
    int running = 1;
    SDL_Event event;
    SDL_Instance instance;

    if (init_instance(&instance) != 0)
        return 1;

    // Load the map from a file
    if (!load_map_from_file("maps/map.txt")) {
        clean_up(instance.renderer, instance.window);
        return 1;
    }
    Player player = {5, 5, 0};  // Start in the middle of the map

    // Load textures
    if (load_all_textures(instance.renderer, instance.window, "textures/Bricks.png",
                            "textures/ceiling-sky.png") != 0)
        return 1;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }
        // Handle input
        handle_input(&player, keyState);
        // Render Game environment
        render_env(instance.renderer, player);
        SDL_Delay(16);  // ~60 FPS
    }
    // Cleanup
    SDL_DestroyTexture(wall_texture);
    SDL_DestroyTexture(ceiling_texture);
    clean_up(instance.renderer, instance.window);
    return 0;
}