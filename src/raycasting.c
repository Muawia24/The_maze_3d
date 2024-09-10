#include "headers/maze.h"

SDL_Texture* wall_texture;    /* Wall texture */
SDL_Texture* ceiling_texture; /* Ceiling texture */
/**
 * cast_ray - Perform Digital Differential Analysis (DDA)
 * @player_x: player horizontal coordinates.
 * @player_y: player vertical coordinates.
 * @ray_angle: the player view angle.
 * @side: definese the side hit 0 for x 1 for y
 * @hit_x: texture hit x-coordinate.
 * Return: Distance to wall.
 */
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
            *side = 0;  /* Hit on the X side */
        } else {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            *side = 1;  /* Hit on the Y side */
        }

        if (map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT) {
            if (map[map_x][map_y] == 1) {
                hit = 1;
            }
        }
    }

    /* Calculate where the ray hit the wall (x-coordinate on the texture) */
    if (*side == 0) {
        *hit_x = player_y + (side_dist_x - delta_dist_x) * sin(ray_angle);
    } else {
        *hit_x = player_x + (side_dist_y - delta_dist_y) * cos(ray_angle);
    }
    *hit_x -= floor(*hit_x);  /* Get fractional part of the hit location */

    if (*side == 0) {
        return (map_x - player_x + (1 - step_x) / 2) / cos(ray_angle);
    } else {
        return (map_y - player_y + (1 - step_y) / 2) / sin(ray_angle);
    }
}

/* Correct fish-eye effect and render textured walls */
/**
 * render_walls - render textured walls.
 * @renderer: SDL renderer.
 * @player: player movment coordinates.
 * Return: nothing.
 */
void render_walls(SDL_Renderer *renderer, Player player) {
    int tex_width, tex_height;
    SDL_QueryTexture(wall_texture, NULL, NULL, &tex_width, &tex_height);

    for (int ray = 0; ray < NUM_RAYS; ray++) {
        /* Calculate ray angle with FOV spread */
        double ray_angle = player.angle - (FOV / 2) * (M_PI / 180.0) + (ray * (FOV * (M_PI / 180.0)) / NUM_RAYS);
        
        int side;
        double hit_x;
        /* Cast the ray and get the distance to the wall */
        double distance_to_wall = cast_ray(player.x, player.y, ray_angle, &side, &hit_x);

        /* Correct fish-eye effect */
        distance_to_wall *= cos(ray_angle - player.angle);

        /* Calculate wall height based on corrected distance */
        int wall_height = (int)(SCREEN_HEIGHT / distance_to_wall);

        /* Get the x-coordinate of the texture */
        int tex_x = (int)(hit_x * tex_width);
        if (side == 0 && cos(ray_angle) > 0) tex_x = tex_width - tex_x - 1;
        if (side == 1 && sin(ray_angle) < 0) tex_x = tex_width - tex_x - 1;

        /* Draw the textured wall slice */
        SDL_Rect src_rect = {tex_x, 0, 1, tex_height};
        SDL_Rect dest_rect = {ray, (SCREEN_HEIGHT - wall_height) / 2, 1, wall_height};
        SDL_RenderCopy(renderer, wall_texture, &src_rect, &dest_rect);
    }
}