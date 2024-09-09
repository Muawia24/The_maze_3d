#include "headers/maze.h"
int map[MAP_WIDTH][MAP_HEIGHT];
/* Function to handle input and sliding along walls when colliding */
void handle_input(Player *player, const Uint8 *keyState) {
    double move_x = 0, move_y = 0;

    if (keyState[SDL_SCANCODE_W]) {
        move_x = cos(player->angle) * PLAYER_SPEED;
        move_y = sin(player->angle) * PLAYER_SPEED;
    }
    if (keyState[SDL_SCANCODE_S]) {
        move_x = -cos(player->angle) * PLAYER_SPEED;
        move_y = -sin(player->angle) * PLAYER_SPEED;
    }

    /* Check X-axis collision */
    if (map[(int)(player->x + move_x)][(int)player->y] == 0) {
        player->x += move_x;
    }
    /* Check Y-axis collision */
    if (map[(int)player->x][(int)(player->y + move_y)] == 0) {
        player->y += move_y;
    }

    if (keyState[SDL_SCANCODE_A]) {
        player->angle -= PLAYER_ROT_SPEED;
    }
    if (keyState[SDL_SCANCODE_D]) {
        player->angle += PLAYER_ROT_SPEED;
    }
}