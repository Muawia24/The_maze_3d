#include "headers/maze.h"
/**
 * draw_player_mapDirection - Draw the player on the 2d map in the window corner.
 * @renderer: SDL renderer.
 * @player: a struct that holds player directions and coordinates.
 * Return: nothing.
 */
void draw_player_mapDirection(SDL_Renderer *renderer, Player player)
{
    int tile_size = MAP_SCALE;
    int map_offset_x = 10, map_offset_y = 10;
     /* Draw the player on the minimap */
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  /* Red for the player */
    SDL_Rect player_rect = {
        map_offset_x + (int)(player.x * tile_size) - tile_size / 4,  /* Center the player marker */
        map_offset_y + (int)(player.y * tile_size) - tile_size / 4,
        tile_size / 2,
        tile_size / 2
    };
    SDL_RenderFillRect(renderer, &player_rect);
    /* Optional: Draw player direction (a line indicating the player's facing direction) */
    int line_length = tile_size * 2;
    int line_x = map_offset_x + player.x * tile_size + cos(player.angle) * line_length;
    int line_y = map_offset_y + player.y * tile_size + sin(player.angle) * line_length;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  /* Red for the direction line */
    SDL_RenderDrawLine(renderer,
        map_offset_x + player.x * tile_size, map_offset_y + player.y * tile_size,
        line_x, line_y);
}
/**
 * render_map - Draws a 2d map to track the player movement on the window.
 * @renderer: SDL renderer.
 * @player: a struct that holds player directions and coordinates.
 * Return: nothing.
 */
void render_map(SDL_Renderer *renderer, Player player)
{
    int tile_size = MAP_SCALE;  /* Size of each tile on the minimap */
    int map_offset_x = 10, map_offset_y = 10;      /* X, Y offset for the minimap position on the window */

    /* Loop through the map array and render the tiles */
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            SDL_Rect tile_rect = {
                map_offset_x + x * tile_size,
                map_offset_y + y * tile_size,
                tile_size,
                tile_size
            };

            if (map[x][y] == 1)
            {
                /* Wall tile */
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  /* White color for walls */
            }
            else
            {
                /* Empty space */
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  /* Black color for empty space */
            }
            SDL_RenderFillRect(renderer, &tile_rect);
            /* Draw grid lines */
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);  /* Gray for grid lines */
            SDL_RenderDrawRect(renderer, &tile_rect);
        }
    }
   draw_player_mapDirection(renderer, player);
}