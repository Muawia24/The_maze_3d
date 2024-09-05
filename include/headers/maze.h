#ifndef MAZE_H
#define MAZE_H

#include <../sdl/SDL.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>


// Maze Structures
typedef struct SDL_Instance
{
        SDL_Window *window;
        SDL_Renderer *renderer;
} SDL_Instance;

// player coordinates
typedef struct positions_s
{
    float x;
    float y;
    float camAngle;
} positions_t;

/**
 * struct Screen - screen dimensions
 * @WIDTH: width of the screen
 * @HEIGHT: height of the screen
 *
 * Description: holds information about the window/screen dimensions
 */
typedef struct Screen
{
    const int WIDTH;
    const int HEIGHT;
} Screen;

extern Screen SCREEN;
// 1 is a wall and the 0 are empt spaces
extern int map[8][8];

// Maze Functions
int init_instance(SDL_Instance **);
void handle_keys(const float rot_speed, const float cam_speed, positions_t *player, SDL_Event *e);
void player_motion(float diffX, float diffY, positions_t **player);
bool handle_collision(float x, float y, int map[8][8]);
void renderWalls(SDL_Renderer *renderer, Screen SCREEN, int map[8][8], int map_width, int map_Height, positions_t *player);

#endif