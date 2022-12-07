/**
 *Created by lab on 11/19/22.
*/


/*
 *   This program illustrates reading and parsing
 *   command-line input based on a : character.
*/

#include "main.h"

char *_cmd_path_search_tokenizer(const char *binary_name, op_t __attribute__((unused)) *array_queue)
{

    const char *colon = ":";
    char *token;
    char *temp_bin_path;
    char *path;
    char *tmp;
    char *retval;
    char *value;
    char *path_values;
    unsigned int i, j;
    bool kill_loop;
    int __attribute__((unused)) enqueue_counter;
    /* Copy a set of paths into the buffer. */
    /*char *buffer = malloc(sizeof(path_values) * sizeof(char));*/
    char buffer[SYSTEM_PATH_ARRAY_SIZE_STRING];

    temp_bin_path = malloc(sizeof(char));
    path = SYSTEM_BIN_PATH;
    path_values = _getenv(path);
    enqueue_counter = 0;
    retval = NULL;
    kill_loop = false;


    strcpy(buffer, path_values);

    /* Print the paths. */

/*    printf("\nThese are the paths:  %s\n", buffer);*/

    /* Print the paths broken into colon-delimited tokens. */

/*    printf("\nThese are the paths parsed into colon-delimited tokens (one per line):  \n\n");*/

    token = strtok(buffer, colon);

    temp_bin_path = realloc(temp_bin_path,sizeof(token) + sizeof(binary_name) + 4);
    while (token != NULL && !kill_loop)
    {

        /**
         * Perform a test to check if the binary file
         * exists in current search path
         * if found return the full binary path so that it can
         * be added to the command Execution Queue
         */
         for (i = 0; token[i] != '\0'; i++)
         {
             /* copy and overwrite elements in the temp_bin_path array*/
             temp_bin_path[i] = token[i];
         }
         /* Add the forward slash for the path*/
         temp_bin_path[i++] = SYSTEM_PATH_SEPARATOR;
         /* append the binary_name*/
         for (j = 0; binary_name[j] != '\0'; j++)
         {
             /* Copy contents to temp_bin_path*/
             temp_bin_path[i++] = binary_name[j];
         }
         /**
          * Terminate the temp_bin_path with a null character
          * that signifies end of string
          */
          temp_bin_path[i++] = '\0';



          /**
           * Check if File Exists and if so return to main
           * after appending the command to array execution queue
           */
          tmp = strdup(temp_bin_path);
           if(file_exists(tmp))
           {

               retval = tmp;
               kill_loop = true;
           }

        token = strtok(NULL, colon);

    }
    if (retval)
        value = strdup(retval);
/*    free(temp_bin_path);*/

    return (value);

}
