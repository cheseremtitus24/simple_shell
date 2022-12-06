//
// Created by lab on 11/19/22.
//
#include "main.h"
/**
 * _getenv- Retrieves a malloc'd Value of an Environment Variable
 * @env_name: Environment Variable name to perform a Look up
 * Return: Pointer to a string else NULL
 */
char *_getenv(char *env_name)
{
    char *value = NULL;
    char *retval = NULL;
    unsigned int i;

    value = getenv(env_name);
    retval = strdup(value);

    return (retval);
}