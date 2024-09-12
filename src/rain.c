#include "headers/maze.h"
/**
 * init_rain - initialize the raindrops
 * Return: nothing.
 */
void init_rain()
 {
    for (int i = 0; i < MAX_RAIN_DROPS; i++)
    {
        raindrops[i].x = rand() % SCREEN_WIDTH;  // Random x position
        raindrops[i].y = rand() % SCREEN_HEIGHT / 2;  // Random y position (starting from the top half)
        raindrops[i].speed = 2.0f + rand() % 3;  // Random speed for each raindrop
    }
}
/**
 * update_rain - update raindrops
 * Return: nothing.
 */
void update_rain()
{
    for (int i = 0; i < MAX_RAIN_DROPS; i++)
    {
        raindrops[i].y += raindrops[i].speed;  // Make the raindrop fall

        // Reset the raindrop if it reaches the bottom of the screen
        if (raindrops[i].y > SCREEN_HEIGHT)
        {
            raindrops[i].x = rand() % SCREEN_WIDTH;  // Random new x position
            raindrops[i].y = 0;  // Reset to the top of the screen
            raindrops[i].speed = 2.0f + rand() % 3;  // New random speed
        }
    }
}
/**
 * render_rain - render raindrops.
 * @renderer: SDL Renderer.
 * Return: nothing.
 */
void render_rain(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);  // Light blue color for raindrops

    for (int i = 0; i < MAX_RAIN_DROPS; i++)
    {
        SDL_RenderDrawLine(renderer, raindrops[i].x, raindrops[i].y, raindrops[i].x, raindrops[i].y + 10);  // Draw a line for each raindrop
    }
}