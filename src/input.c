#include "headers/maze.h"
/**
 * handle_input - handle input and sliding along walls.
 * @player: a struct that holds player directions and coordinates.
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
}