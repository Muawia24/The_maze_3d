#include "headers/maze.h"

SDL_Texture* wall_texture;    /* Wall texture */
SDL_Texture* ceiling_texture; /* Ceiling texture */

/* Load a texture from a file */
SDL_Texture* load_texture(SDL_Renderer *renderer, const char* file) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, file);
    if (!texture) {
        printf("Failed to load texture: %s\n", IMG_GetError());
    }
    return texture;
}

/* Optimized function to render the static textured ceiling and the floor */
void render_textured_floor_and_ceiling(SDL_Renderer *renderer, Player player) {
    int tex_width, tex_height;
    SDL_QueryTexture(ceiling_texture, NULL, NULL, &tex_width, &tex_height);

    /* Render the static ceiling (top half of the screen) */
    for (int y = 0; y < SCREEN_HEIGHT / 2; y++) {
        /* Compute the y coordinate in the texture (static, no perspective) */
        int tex_y = y % tex_height;

        /* Create a source rectangle for the entire row of the texture */
        SDL_Rect src_rect = { 0, tex_y, tex_width, 1 };

        /* Destination rectangle spans the entire screen width for this row */
        SDL_Rect dest_rect = { 0, y, SCREEN_WIDTH, 1 };

        /* Render the entire row in one call */
        SDL_RenderCopy(renderer, ceiling_texture, &src_rect, &dest_rect);
    }

    /* Render the floor (bottom half) as a solid color (you can replace it with a texture) */
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); /* Dark gray for floor */
    SDL_Rect floor = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_RenderFillRect(renderer, &floor);
}