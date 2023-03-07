/*Created by lab on 11/19/22. */

#include "main.h"

/**
 * find_binary- retrieves the full path to a binary file
 * @filename: binary filename to search and retrieve
 *
 * Return: pointer to binary full path string else NULL
 */
char *find_binary(const char *filename)
{
	const char *path = _getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");

	while (dir)
	{
		char *full_path = malloc(strlen(dir) + strlen(filename) + 2);

		sprintf(full_path, "%s/%s", dir, filename);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}






