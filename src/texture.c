#include "headers/maze.h"
<<<<<<< HEAD
=======

SDL_Texture *wall_texture;    /* Wall texture */
SDL_Texture *ceiling_texture; /* Ceiling texture */
>>>>>>> f49c51ec4c19ddf5c0ef2fc05d6cd1d522726d3b
/**
 * load_texture - Load a texture from a file.
 * @renderer: SDL renderer.
 * @file: path to the texture file.
 * Return: The SDL texture.
 */
SDL_Texture *load_texture(SDL_Renderer *renderer, const char *file)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, file);

	if (!texture)
		printf("Failed to load texture: %s\n", IMG_GetError());
	return (texture);
}
/**
 * render_textured_floor_and_ceiling - renders textured ceiling and floor
 * @renderer: SDL renderer.
 * @player: a struct that holds player directions and coordinates.
 * Return: nothing
 */
<<<<<<< HEAD
void render_textured_floor_and_ceiling(SDL_Renderer *renderer, Game_env *game, Player player) {
    int tex_width, tex_height;
    SDL_QueryTexture(game->ceiling_texture, NULL, NULL, &tex_width, &tex_height);
=======
void render_textured_floor_and_ceiling(SDL_Renderer *renderer, Player player)
{
	int tex_width, tex_height;
>>>>>>> f49c51ec4c19ddf5c0ef2fc05d6cd1d522726d3b

	SDL_QueryTexture(ceiling_texture, NULL, NULL, &tex_width, &tex_height);

	/* Render the static ceiling (top half of the screen) */
	for (int y = 0; y < SCREEN_HEIGHT / 2; y++)
	{
		/* Compute the y coordinate in the texture */
		int tex_y = y % tex_height;

		/* Create a rectangle for the texture */
		SDL_Rect src_rect = { 0, tex_y, tex_width, 1 };

<<<<<<< HEAD
        /* Render the entire row in one call */
        SDL_RenderCopy(renderer, game->ceiling_texture, &src_rect, &dest_rect);
    }
=======
		/* Destination rectangle */
		SDL_Rect dest_rect = { 0, y, SCREEN_WIDTH, 1 };
>>>>>>> f49c51ec4c19ddf5c0ef2fc05d6cd1d522726d3b

		/* Render the entire row in one call */
		SDL_RenderCopy(renderer, ceiling_texture,
				&src_rect, &dest_rect);
	}

	/* Render the floor */
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); /* Dark gray floor */
	SDL_Rect floor = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH,
				SCREEN_HEIGHT / 2};
	SDL_RenderFillRect(renderer, &floor);
}
