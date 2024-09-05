#include "../headers/maze.h"

Screen SCREEN = {1280, 720};
int map[8][8];
/**
 * renderWalls - This function draws wall in the 3D maze
 *
 * @gRenderer: SDL renderer used to draw the walls.
 * @SCREEN: Struct holding screen dimensions.
 * @wMap: Array that represents the map of walls.
 * @mWidth: The width of the map in cells.
 * @mHeight: The height of the map in cells.
 * @player: Struct holding player position information.
 */
void renderWalls(SDL_Renderer *renderer, Screen SCREEN, int map[8][8], int map_width, int map_height, positions_t *player)
{
    // Field of view
    float fov = 60.0 * (M_PI / 180.0);
    float halfFov = fov / 2.0;

    // Drawing the walls using raycasting
    for(int x = 0; x < SCREEN.WIDTH; x++)
    {
        float rayAngle = (player->camAngle - halfFov) + ((float)x / (float)SCREEN.WIDTH) *fov;

        float rayX = cos(rayAngle);
        float rayY = sin(rayAngle);


        int mapX = (int)player->x;
        int mapY = (int)player->y;

        float deltaDistX = fabs(1 / rayX);
        float deltaDistY = fabs(1 / rayY);
        float sideDistX;
        float sideDistY;
        float perpWallDist;

        int stepX;
        int stepY;

        if (rayX < 0)
        {
            stepX = -1;
            sideDistX = (player->x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player->x) * deltaDistX;
        }

        if(rayY < 0)
        {
            stepY = -1;
            sideDistY = (player->y - mapY) + deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->y) * deltaDistY;
        }

        bool collision = false;
        bool side;
        while(!collision)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += sideDistX;
                mapX += stepX;
                side = false;
            }
            else
            {
                sideDistY += sideDistY;
                mapY += stepY;
                side = true;
            }

            if(map[mapX][mapY] > 0)
            {
                collision = true;
            }
        }

        if(side)
        {
            perpWallDist = (mapY - player->y + (1 - stepY) / 2) / rayY;
        }
        else
        {
            perpWallDist = (mapX - player->x + (1 - stepX) / 2) / rayX;
        }

        int lineHeight = (int)(SCREEN.HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + SCREEN.HEIGHT / 2;
        if(drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN.HEIGHT / 2;
        if(drawEnd >= SCREEN.HEIGHT) drawEnd = SCREEN.HEIGHT - 1;

        // Color the ground
        SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
        SDL_Rect ground = {0, drawEnd, SCREEN.WIDTH, SCREEN.HEIGHT - drawEnd};
        SDL_RenderFillRect(renderer, &ground);

        // Color the walls
        if(side) // East or West facing walls
        {
            SDL_SetRenderDrawColor(renderer, 112, 112, 112, 255);
        }
        else // North or South facing walls
        {
            SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
        }
        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }
}