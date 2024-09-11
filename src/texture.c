#include "headers/maze.h"
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
 * @game: Pointer to struct for game map and textures.
 * @player: a struct that holds player directions and coordinates.
 * Return: nothing.
 */
void render_textured_floor_and_ceiling(SDL_Renderer *renderer,
				Game_env *game, Player player)
{
	int tex_width, tex_height;

	SDL_QueryTexture(game->ceiling_texture, NULL, NULL, &tex_width, &tex_height);

	/* Render the static ceiling (top half of the screen) */
	for (int y = 0; y < SCREEN_HEIGHT / 2; y++)
	{
		/* Compute the y coordinate in the texture (static, no perspective) */
		int tex_y = y % tex_height;

		/* Create a source rectangle for the entire row of the texture */
		SDL_Rect src_rect = { 0, tex_y, tex_width, 1 };

		/* Destination rectangle spans the entire screen width for this row */
		SDL_Rect dest_rect = { 0, y, SCREEN_WIDTH, 1 };

		/* Render the entire row in one call */
		SDL_RenderCopy(renderer, game->ceiling_texture, &src_rect, &dest_rect);
	}

	/* Render the floor */
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); /* Dark gray for floor */
	SDL_Rect floor = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};

	SDL_RenderFillRect(renderer, &floor);
}
