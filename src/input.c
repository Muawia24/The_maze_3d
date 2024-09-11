/* main.c */
#include "headers/maze.h"
/**
 * render_env - renders the Game environment (walls, texture, 2d map)
 * @renderer: SDL renderer.
 * @player: a struct that holds player directions and coordinates.
<<<<<<< HEAD
 * @game: pointer to struct for game map and textures.
 * @keyState: pointer to the keyboard input status.
 * Return: 1 or 0.
 */
int handle_input(Player *player, Game_env *game, const Uint8 *keyState)
{
	double move_x = 0, move_y = 0;

	if (keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP])
	{
	move_x = cos(player->angle) * PLAYER_SPEED;
	move_y = sin(player->angle) * PLAYER_SPEED;
	}
	if (keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN])
	{
		move_x = -cos(player->angle) * PLAYER_SPEED;
		move_y = -sin(player->angle) * PLAYER_SPEED;
	}

	/* Check X-axis collision */
	if (game->map[(int)(player->x + move_x)][(int)player->y] == 0)
		player->x += move_x;

	/* Check Y-axis collision */
	if (game->map[(int)player->x][(int)(player->y + move_y)] == 0)
		player->y += move_y;

	if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT])
		player->angle -= PLAYER_ROT_SPEED;

	if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT])
		player->angle += PLAYER_ROT_SPEED;
	if (keyState[SDL_SCANCODE_ESCAPE])
		return (0);
	
	return (1);
=======
 * Return: nothing
 */
void render_env(SDL_Renderer *renderer, Game_env *game, Player player)
{
	/* Clear screen */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	/* Render the textured floor and ceiling */
	render_textured_floor_and_ceiling(renderer, game, player);
	/* Render walls with textures */
	render_walls(renderer, game, player);
	/* Render the 2D map */
	render_map(renderer, game, player);
	/* Present renderer */
	SDL_RenderPresent(renderer);
}
/**
 * load_all_textures - loades all textures wall, ceiling, floor.
 * @renderer: SDL renderer.
 * @window: SDL window.
 * @file1: path to wall texture.
 * @file2: path to ceil texture.
 * Return: 0 in success otherwise 1.
 */
int load_all_textures(SDL_Renderer *renderer, Game_env *game, SDL_Window *window,
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
>>>>>>> ac998ece9d34b2f13e9b4f1c6379297155b784cb
}
/**
 * main - Game main function.
 * @argc: number of terminal arguments.
 * @argv: array of terminal arguments.
 * Return: 0 in success otherwise 1.
 */
int main(int argc, char *argv[])
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

	/* Load textures */
	if (load_all_textures(instance.renderer, &game, instance.window,
				"textures/Bricks.png",
				"textures/ceiling-sky.png") != 0)
		return (1);

	const Uint8 *keyState = SDL_GetKeyboardState(NULL);

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = 0;
		}
		/* Handle input */
		running = handle_input(&player, &game, keyState);
		/* Render Game environment */
		render_env(instance.renderer, &game,player);
		SDL_Delay(16);  /* ~60 FPS */
	}
	/* Cleanup */
	SDL_DestroyTexture(game.wall_texture);
	SDL_DestroyTexture(game.ceiling_texture);
	clean_up(instance.renderer, instance.window);
	return (0);
}

