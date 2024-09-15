/* init_window.c */
#include "../headers/maze.h"
/**
 * init_instance - Function that initialize SDL window and SDL surface.
 * @instance: instance of a struct that contains SDL window and surface.
 * Return: 0 in success, otherwise 1.
 */
int init_instance(SDL_Instance *instance)
{
	/* Initialize video subsystem */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}
	/* Create SDL Window */
	instance->window = SDL_CreateWindow("The Maze 3D",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n",
			SDL_GetError());
		SDL_Quit();
		return (1);
	}
	/* Create SDL Renderer */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
				SDL_RENDERER_ACCELERATED);

	if (instance->renderer == NULL)
	{
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n",
			SDL_GetError());
		SDL_DestroyWindow(instance->window);
		SDL_Quit();
		return (1);
	}
	return (0);
}
