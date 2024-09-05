#include "../headers/maze.h"
int map[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};
/* Camera rotation speed and movement speed */
const float rot_speed = M_PI / 4;
const float cam_speed = 0.05;
/* Player positions */

/**
 * main - function that initialize the game loop until player QUIT.
 * Return: 0 in success, otherwise 1.
 */
int main(int argc, char *argv[])
{
	SDL_Instance *instance;
	SDL_Event e;
	bool quit = false;
	positions_t player = {6.0, 1.0, 90.0};
	if (init_instance(&instance) != 0)
		return (1);

	SDL_SetRelativeMouseMode(SDL_TRUE);

	while (!quit)
	{
		// Time at frame start
		uint32_t frame_start = SDL_GetTicks();

		// Handleing user interactions
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
			else if (e.type == SDL_KEYDOWN)
			{
				
				handle_keys(rot_speed, cam_speed, &player, &e);
			}
			// Adjust the camera angle left or right based on mouse movements
			else if (e.type == SDL_MOUSEMOTION)
				player.camAngle += e.motion.xrel * (rot_speed / 10.0);
		}
		// Color the sky rgba
		SDL_SetRenderDrawColor(instance->renderer, 135, 206, 235, 255);
		// Clear the gRenderer with the drawing color
		SDL_RenderClear(instance->renderer);
		// Draw the walls
		renderWalls(instance->renderer, SCREEN, map, 8, 8, &player);

		// Present the backbuffer to the screen
		SDL_RenderPresent(instance->renderer);
	}
	SDL_DestroyRenderer(instance->renderer);
	instance->renderer = NULL;
	SDL_DestroyWindow(instance->window);
	instance->window = NULL;
	SDL_Quit();
	return (0);
}