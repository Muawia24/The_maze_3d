#include "../headers/maze.h"
/**
 * render_env - renders the Game environment (walls, texture, 2d map)
 * @renderer: SDL renderer.
 * @game: pointer to struct for game map and textures.
 * @player: a struct that holds player directions and coordinates.
 * Return: nothing
 */
void render_env(SDL_Renderer *renderer, Game_env *game, Player player)
{
	/* Clear screen */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	/* Render the textured floor and ceiling */
	render_textured_floor_and_ceiling(renderer, game);

	/* Render walls with textures */
	render_walls(renderer, game, player);

	/* Render the 2D map */
	render_map(renderer, game, player);

	/* Render rain drops */
	render_rain(renderer);

	/* Present renderer */
	SDL_RenderPresent(renderer);
}
/**
 * load_all_textures - loades all textures wall, ceiling, floor.
 * @renderer: SDL renderer.
 * @window: SDL window.
 * @game: pointer to struct for game map and textures.
 * @file1: path to wall texture.
 * @file2: path to ceil texture.
 * Return: 0 in success otherwise 1.
 */
int load_all_textures(SDL_Renderer *renderer, Game_env *game,
			SDL_Window *window,
			const char *file1, const char *file2)
{
	/* Load the wall texture */
	game->wall_texture = load_texture(renderer, file1);
	if (!game->wall_texture)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		return (1);
	}
	/* Load the ceiling texture */
	game->ceiling_texture = load_texture(renderer, file2);
	if (!game->ceiling_texture)
	{
		SDL_DestroyTexture(game->wall_texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}
	return (0);
}
/**
 * clean_up - destroy every sdl instance and quit sdl.
 * @renderer: SDL renderer.
 * @window: SDL window.
 * Return: nothing.
 */
void clean_up(SDL_Renderer *renderer, SDL_Window *window)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
/**
 * main - Game main function.
 * @argc: number of terminal arguments.
 * @argv: array of terminal arguments.
 * Return: 0 in success otherwise 1.
 */
int main(void)
{
	int running = 1;
	SDL_Event event;
	SDL_Instance instance;
	Game_env game;

	if (init_instance(&instance) != 0)
		return (1);
	/* Load the map from a file */
	if (load_map_from_file("maps/map.txt", &game) != 0)
	{
		clean_up(instance.renderer, instance.window);
		return (1);
	}
	Player player = {5, 5, 0};  /* Start in the middle of the map */

	if (load_all_textures(instance.renderer, &game, instance.window,
				"textures/Bricks.png",
				"textures/ceiling-sky.png") != 0)
		return (1);

	init_rain(); /* initialize raindrop */
	const Uint8 *keyState = SDL_GetKeyboardState(NULL);

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = 0;
		}
		running = handle_input(&player, &game, keyState);/* Handle input */
		update_rain(); /* updates raindrop */
		render_env(instance.renderer, &game, player);/* Render Game environment */
		SDL_Delay(16);  /* ~60 FPS */
	}
	/* Cleanup */
	SDL_DestroyTexture(game.wall_texture);
	SDL_DestroyTexture(game.ceiling_texture);
	clean_up(instance.renderer, instance.window);
	return (0);
}
