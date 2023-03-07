/* Created by uwelekezo on 3/6/23.*/


#include "main.h"

/**
 * file_exists - verifies if a file exists
 * @av: filename to check if it exists
 *
 * Return: true if file exists else false
 */
bool file_exists(char *av)
{
	struct stat st;
	/*printf("Full File path : %s",av);*/

	if (stat(av, &st) == 0)
	{
		/*printf(" FOUND\n");*/
		return (true);
	}
	else
	{
		/*printf(" NOT FOUND\n");*/
		return (false);
	}
}
