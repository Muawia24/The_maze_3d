#include "headers/maze.h"
/**
 * load_map_from_file - Parses and load the mape from a file.
 * @filename: Path to map file.
 * Return: 0 in success otherwise 1.
 */
/* Function to load the map from a file */
int load_map_from_file(const char* filename, Game_env *game)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Failed to open map file: %s\n", filename);
		return (1);
	}
    char line[MAP_WIDTH + 2];  /* Buffer to hold each line of the file (including newline) */
    int row = 0;

    while (fgets(line, sizeof(line), file)) {
        /* Ensure the file contains the correct number of rows */
        if (row >= MAP_HEIGHT) {
            printf("Map file has too many rows (expected %d rows).\n", MAP_HEIGHT);
            fclose(file);
            return 1;
        }
        /* Read each character in the line */
        for (int col = 0; col < MAP_WIDTH; col++) {
            if (line[col] == '1') {
                game->map[col][row] = 1;  /* Wall */
            } else if (line[col] == '0') {
                game->map[col][row] = 0;  /* Empty space */
            } else {
                printf("Invalid character '%c' in map file at row %d, col %d\n", line[col], row, col);
                fclose(file);
                return 1;
            }
        }
        row++;
    }
    /* Ensure the file has the correct number of rows */
    if (row != MAP_HEIGHT) {
        printf("Map file has too few rows (expected %d rows).\n", MAP_HEIGHT);
        fclose(file);
        return 1;
    }
    fclose(file);
    return 0;
}
