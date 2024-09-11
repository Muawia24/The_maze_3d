#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define FOV 60
#define NUM_RAYS SCREEN_WIDTH
#define PLAYER_SPEED 0.05
#define PLAYER_ROT_SPEED 0.03
#define TILE_SIZE 1.0
#define MAP_SCALE 10  /* Scale for the minimap */

/**
 * struct SDL_Instance - struct to initialize a window instance.
 * @window: SDL window.
 * @renderer: SDL renderer.
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

/**
 * struct Player - struct for the player motion coordinates.
 * @x: x-coordinates (horizontal).
 * @y: y-coordinates (vertical).
 * @angle: player rotation angle.
 */
typedef struct Player
{
	double x, y;
	double angle;
} Player;

/**
 * struct Game_env - struct for game map and textures.
 * @map: map array.
 * @ceiling_texture: Ceiling texture
 * @wall_texture: Wall texture.
 */
typedef struct Game_env
{
	int map[MAP_WIDTH][MAP_HEIGHT];
	SDL_Texture *wall_texture;
	SDL_Texture *ceiling_texture;
} Game_env;
/* Function declarations */
int init_instance(SDL_Instance *instance);
int handle_input(Player *player, Game_env *game, const Uint8 *keyState);
void render_textured_floor_and_ceiling(SDL_Renderer *renderer,
		Game_env *game, Player player);
double cast_ray(double player_x, double player_y, double ray_angle,
		int *side, double *hit_x, Game_env *game);
void render_walls(SDL_Renderer *renderer, Game_env *game, Player player);
SDL_Texture *load_texture(SDL_Renderer *renderer, const char *file);
void render_map(SDL_Renderer *renderer, Game_env *game, Player player);
void render_env(SDL_Renderer *rendrer, Game_env *game, Player player);
int load_map_from_file(const char *filename, Game_env *game);

#endif /* MAZE_H*/
