
#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

/* UseFul macros */
/* checked for in order to decide when to exit a shell*/
#define TERM_Exit_Signal "exit"
#define ENV_VAR_PREFIX '$'
#define ARG_ARR_SIZE 3
#define SYSTEM_BIN_PATH "PATH";
#define SYSTEM_PATH_SEPARATOR '/'
#define SYSTEM_PATH_ARRAY_SIZE_STRING 1000



/* Function Declarations */
void _trim(char * str); /*trims before and after command input*/
char *_getenv(char *env_name); /*retrieves environment Variable Values*/
bool file_exists(char *filepath); /*checks if file exists given its full path*/
bool ReportError(char *token, char **argv ); /* report error when binary is not found*/
int is_regular_file(const char* path);/* check if a file in a path is a regular file*/
int isDirectory(const char* path);/* checks if a file is a directory*/

typedef struct command_args
{
    char **arr;
    unsigned int _capacity;
    unsigned int _size;
    bool env_val_expansion;

} op_t;

/* Queue implementation functions*/
bool enqueue(op_t *array, char *str);
bool dequeue(op_t *array);
char *peek(op_t *array);
bool is_full(op_t *array);
bool is_empty(op_t *array);
void print(op_t *array);
/*End of  Queue implementation functions*/



int _cmd_input_tokenizer(char *command_input, char **argv, op_t *pOp); /* Tokenizes commandline input*/
char *_cmd_path_search_tokenizer(const char *binary_name, op_t *array_queue);
#endif /* _MAIN_H_ */
