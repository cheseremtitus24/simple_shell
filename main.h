
#ifndef CUSTOM_SHELL_MAIN_H
#define CUSTOM_SHELL_MAIN_H
/* Created by uwelekezo on 3/6/23.*/
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <wait.h>
#include <stdio.h>
#include <zconf.h>
#include <sys/stat.h>
#include <string.h>

#define TERM_Exit_Signal "exit"
#define ENV_VAR_PREFIX '$'
#define ARG_ARR_SIZE 3
#define SYSTEM_BIN_PATH "PATH"
#define SYSTEM_PATH_SEPARATOR '/'
#define SYSTEM_PATH_ARRAY_SIZE_STRING 1000




/**
 * struct command_args - Queue function that will store the passed
 * in commandline arguments
 * @arr: array of pointers to strings
 * @_capacity: Capacity of the Array
 * @_size: Number of Pointers to strings in the Array
 * Commandline Arguments are stored in a Queue.
 * This enables for First in First out order
 * e.g.
 * ls -a -l /var/www
 * # command arguments are split on spaces
 * [ls|-a|-l|/var/www]
 * This is stored within the queue Structure Declared Below
 *
 */
typedef struct command_args
{
	char **arr;
	unsigned int _capacity;
	unsigned int _size;

} op_t;


/* Queue implementation functions*/
bool enqueue(op_t *array, char *str);
bool dequeue(op_t *array);
char *peek(op_t *array);
bool is_full(op_t *array);
bool is_empty(op_t *array);
void reset(op_t *pArray);
void print(op_t *array);
int execute_command(op_t *pArgs, char **argv);
bool file_exists(char *av);
char *_getenv(const char *name);
char *find_binary(const char *binary_name);
void _trim(char *str);
int _input_tokenizer(char *command_input, char **argv, op_t *pOp);
/*End of  Queue implementation functions*/
#endif /*CUSTOM_SHELL_MAIN_H*/
