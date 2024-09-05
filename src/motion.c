#include "../headers/maze.h"

/**
 * handle_collision - checks for collision with walls.
 * @x: The x-coordinate of the player position.
 * @y: The y-coordinate of the camera position.
 *
 * Return: True if there is collision with walls, false if not.
 */
bool handle_collision(float x, float y, int map[8][8])
{
    int mapX = (int)x;
    int mapY = (int)y;

    // In case it hits the map boundries
    if (mapX < 0 || mapX >= 8 || mapY < 0 || mapY >= 8)
        return true;

    // True if there is a wall collision, False if no wall
    return map[mapX][mapY] > 0;
}

/**
 * player_motion -  Handles the player movements.
 * *
 * @diffX: The change in x-coordinate of the player.
 * @diffY: The change in y-coordinate of the player.
 *
 * Return: nothing.
 */
void player_motion(float diffX, float diffY, positions_t **player)
{
    // The next move coordinates
    float nextX = (*player)->x + diffX;
    float nextY = (*player)->y + diffY;

    // Check collision
    if (!handle_collision(nextX, nextY, map))
    {
        (*player)->x = nextX;
        (*player)->y = nextY;
    }
    else
    {
        // Slide along the walls (horizontal movement)
        // Sliding coordinates
        float slideX = diffX;
        float slideY = 0.0;
        if (handle_collision((*player)->x + slideX, (*player)->y + slideY, map))
        {
            (*player)->x += slideX;
            (*player)->y += slideY;
        }
        // Slide along the walls (vertical movement)
        else
        {
            // Sliding coordinates
            slideX = 0.0;
            slideY = diffY;
            if (handle_collision((*player)->x + slideX, (*player)->y + slideY, map))
            {
                (*player)->x += slideX;
                (*player)->y += slideY;
            }
        }
    }
}

/**
 * handle_keys - checks which key is pressed and move the player accordingly.
 *
 * @rot_speed: camera rotation speed.
 * @cam_speed: camera speed.
 *
 * Return: nothing.
 */
void handle_keys(const float rot_speed, const float cam_speed, positions_t *player, SDL_Event *e)
{
            // Player's next move coordinates
	        float moveX = 0, moveY = 0.0;
            switch (e->key.keysym.sym)
                {
                case SDLK_LEFT:
                    player->camAngle -= rot_speed;
                    break;
                case SDLK_RIGHT:
                    player->camAngle += rot_speed;
                    break;
                case SDLK_w:
                    moveX = (cos(player->camAngle)) * cam_speed;
                    moveY = sin(player->camAngle) * cam_speed;
                    player_motion(moveX, moveY, &player);
                    break;
                case SDLK_s:
                    moveX = -cos(player->camAngle) * cam_speed;
                    moveY = -sin(player->camAngle) * cam_speed;
                    player_motion(moveX, moveY, &player);
                    break;
                case SDLK_a:
                    moveX = sin(player->camAngle) * cam_speed;
                    moveY = -cos(player->camAngle) * cam_speed;
                    player_motion(moveX, moveY, &player);
                    break;
                case SDLK_d:
                    moveX = -sin(player->camAngle) * cam_speed;
                    moveY = cos(player->camAngle) * cam_speed;
                    player_motion(moveX, moveY, &player);
                    break;
                default:
                    break;
                }
}