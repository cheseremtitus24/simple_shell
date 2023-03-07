/* Created by lab on 11/19/22.*/
#include "main.h"

/**
 * _getenv- Retrieves a malloc'd Value of an Environment Variable
 * @name: Environment Variable name to perform a Look up
 * Return: Pointer to a string else NULL
 */
char *_getenv(const char *name)
{
	extern char **environ;
	char **env = environ;
	size_t var_name_len = strlen(name);

	while (*env)
	{
		if (strncmp(*env, name, var_name_len) == 0 && (*env)[var_name_len] == '=')
		{
			return (*env + var_name_len + 1);
		}
		env++;
	}

	return (NULL);
}
