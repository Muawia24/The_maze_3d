#include "headers/maze.h"


int map[MAP_WIDTH][MAP_HEIGHT] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,1},
    {1,0,1,0,1,1,1,0,0,1},
    {1,0,1,0,1,0,0,1,0,1},
    {1,0,0,0,1,0,0,1,0,1},
    {1,0,1,1,1,0,0,1,0,1},
    {1,0,0,0,0,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

SDL_Texture* wall_texture;    // Wall texture
SDL_Texture* ceiling_texture; // Ceiling texture

// Function to handle input and sliding along walls when colliding
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

    // Check X-axis collision
    if (map[(int)(player->x + move_x)][(int)player->y] == 0) {
        player->x += move_x;
    }
    // Check Y-axis collision
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

// Load a texture from a file
SDL_Texture* load_texture(SDL_Renderer *renderer, const char* file) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, file);
    if (!texture) {
        printf("Failed to load texture: %s\n", IMG_GetError());
    }
    return texture;
}

// Optimized function to render the static textured ceiling and the floor
void render_textured_floor_and_ceiling(SDL_Renderer *renderer, Player player) {
    int tex_width, tex_height;
    SDL_QueryTexture(ceiling_texture, NULL, NULL, &tex_width, &tex_height);

    // Render the static ceiling (top half of the screen)
    for (int y = 0; y < SCREEN_HEIGHT / 2; y++) {
        // Compute the y coordinate in the texture (static, no perspective)
        int tex_y = y % tex_height;

        // Create a source rectangle for the entire row of the texture
        SDL_Rect src_rect = { 0, tex_y, tex_width, 1 };

        // Destination rectangle spans the entire screen width for this row
        SDL_Rect dest_rect = { 0, y, SCREEN_WIDTH, 1 };

        // Render the entire row in one call
        SDL_RenderCopy(renderer, ceiling_texture, &src_rect, &dest_rect);
    }

    // Render the floor (bottom half) as a solid color (you can replace it with a texture)
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Dark gray for floor
    SDL_Rect floor = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_RenderFillRect(renderer, &floor);
}

// Perform Digital Differential Analysis (DDA) to handle ray intersections
double cast_ray(double player_x, double player_y, double ray_angle, int *side, double *hit_x) {
    int map_x = (int)player_x;
    int map_y = (int)player_y;

    double delta_dist_x = fabs(1 / cos(ray_angle));
    double delta_dist_y = fabs(1 / sin(ray_angle));

    double side_dist_x, side_dist_y;
    int step_x, step_y;
    int hit = 0;

    if (cos(ray_angle) < 0) {
        step_x = -1;
        side_dist_x = (player_x - map_x) * delta_dist_x;
    } else {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - player_x) * delta_dist_x;
    }

    if (sin(ray_angle) < 0) {
        step_y = -1;
        side_dist_y = (player_y - map_y) * delta_dist_y;
    } else {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - player_y) * delta_dist_y;
    }

    while (!hit) {
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            *side = 0;  // Hit on the X side
        } else {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            *side = 1;  // Hit on the Y side
        }

        if (map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT) {
            if (map[map_x][map_y] == 1) {
                hit = 1;
            }
        }
    }

    // Calculate where the ray hit the wall (x-coordinate on the texture)
    if (*side == 0) {
        *hit_x = player_y + (side_dist_x - delta_dist_x) * sin(ray_angle);
    } else {
        *hit_x = player_x + (side_dist_y - delta_dist_y) * cos(ray_angle);
    }
    *hit_x -= floor(*hit_x);  // Get fractional part of the hit location

    if (*side == 0) {
        return (map_x - player_x + (1 - step_x) / 2) / cos(ray_angle);
    } else {
        return (map_y - player_y + (1 - step_y) / 2) / sin(ray_angle);
    }
}

// Correct fish-eye effect and render textured walls
void render_walls(SDL_Renderer *renderer, Player player) {
    int tex_width, tex_height;
    SDL_QueryTexture(wall_texture, NULL, NULL, &tex_width, &tex_height);

    for (int ray = 0; ray < NUM_RAYS; ray++) {
        // Calculate ray angle with FOV spread
        double ray_angle = player.angle - (FOV / 2) * (M_PI / 180.0) + (ray * (FOV * (M_PI / 180.0)) / NUM_RAYS);
        
        int side;
        double hit_x;
        // Cast the ray and get the distance to the wall
        double distance_to_wall = cast_ray(player.x, player.y, ray_angle, &side, &hit_x);

        // Correct fish-eye effect
        distance_to_wall *= cos(ray_angle - player.angle);

        // Calculate wall height based on corrected distance
        int wall_height = (int)(SCREEN_HEIGHT / distance_to_wall);

        // Get the x-coordinate of the texture
        int tex_x = (int)(hit_x * tex_width);
        if (side == 0 && cos(ray_angle) > 0) tex_x = tex_width - tex_x - 1;
        if (side == 1 && sin(ray_angle) < 0) tex_x = tex_width - tex_x - 1;

        // Draw the textured wall slice
        SDL_Rect src_rect = {tex_x, 0, 1, tex_height};
        SDL_Rect dest_rect = {ray, (SCREEN_HEIGHT - wall_height) / 2, 1, wall_height};
        SDL_RenderCopy(renderer, wall_texture, &src_rect, &dest_rect);
    }
}

// Function to render the minimap
void render_map(SDL_Renderer *renderer, Player player) {
    int tile_size = MAP_SCALE;  // Size of each tile on the minimap
    int map_offset_x = 10;      // X offset for the minimap position on the window
    int map_offset_y = 10;      // Y offset for the minimap position on the window

    // Loop through the map array and render the tiles
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SDL_Rect tile_rect = {
                map_offset_x + x * tile_size,
                map_offset_y + y * tile_size,
                tile_size,
                tile_size
            };

            if (map[x][y] == 1) {
                // Wall tile
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color for walls
            } else {
                // Empty space
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black color for empty space
            }
            SDL_RenderFillRect(renderer, &tile_rect);

            // Draw grid lines (optional, for clarity)
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);  // Gray for grid lines
            SDL_RenderDrawRect(renderer, &tile_rect);
        }
    }

    // Draw the player on the minimap
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red for the player
    SDL_Rect player_rect = {
        map_offset_x + (int)(player.x * tile_size) - tile_size / 4,  // Center the player marker
        map_offset_y + (int)(player.y * tile_size) - tile_size / 4,
        tile_size / 2,
        tile_size / 2
    };
    SDL_RenderFillRect(renderer, &player_rect);

    // Optional: Draw player direction (a line indicating the player's facing direction)
    int line_length = tile_size * 2;
    int line_x = map_offset_x + player.x * tile_size + cos(player.angle) * line_length;
    int line_y = map_offset_y + player.y * tile_size + sin(player.angle) * line_length;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red for the direction line
    SDL_RenderDrawLine(renderer,
        map_offset_x + player.x * tile_size, map_offset_y + player.y * tile_size,
        line_x, line_y);
}