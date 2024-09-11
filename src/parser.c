#include "headers/maze.h"
/**
 * load_map_from_file - Parses and load the mape from a file.
 * @filename: Path to map file.
 * @game: pointer to struct for game map and textures.
 * Return: 0 in success otherwise 1.
 */
int load_map_from_file(const char *filename, Game_env *game)
{
	FILE *file = fopen(filename, "r");
	char line[MAP_WIDTH + 2];  /* Buffer to hold each line of the file*/
	int row = 0;

	if (file == NULL)
	{
		printf("Failed to open map file: %s\n", filename);
		return (1);
	}
	while (fgets(line, sizeof(line), file))
	{
		if (row >= MAP_HEIGHT) /* Ensure file contains correct rows num*/
		{
			printf("Map file has too many rows(expected %d rows).\n", MAP_HEIGHT);
			fclose(file);
			return (1);
		}
		for (int col = 0; col < MAP_WIDTH; col++)
		{	/* Read each character in the line */
			if (line[col] == '1')
				game->map[col][row] = 1;  /* Wall */
			else if (line[col] == '0')
				game->map[col][row] = 0;  /* Empty space */
			else
			{
				printf("Invalid character '%c' in map row %d, col %d\n", line[col],
						row, col);
				fclose(file);
				return (1);
			}
		}
		row++;
	}
	if (row != MAP_HEIGHT) /* Ensure file has correct rows number */
	{
		printf("Map file has too few rows, expected %d rows.\n", MAP_HEIGHT);
		fclose(file);
		return (1);
	} fclose(file);
	return (0);
}
