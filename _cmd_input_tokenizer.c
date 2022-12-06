//
// Created by lab on 11/18/22.
//
#include "main.h"


/**
 * _cmd_input_tokenizer - Create a function that Captures/Parses and Generates Commandline Arguments
 * @command_input: Command Input to be Parsed
 * Return: Zero on success else -1 on Failure
*/

int _cmd_input_tokenizer(char *command_input, char **argv, op_t *pOp) {
    const char *whitespace = " \n\r\f\t\v";
    char *token;
    char *command;
    char *temp = strdup(command_input);
    token = strtok(temp, whitespace);
    /* stores path to the redirection file ls -a > file.txt*/
    char *outfile_path = NULL;
    /*stores environment name lookup value e.g HOME="/root/" env_val="/root/"*/
    char *env_val = NULL;

    int counter = 0;
    /**
     * Initialize commands_counter to 0 so that we may be able to capture
     * the first command
     */


    /**
     * Process 3 types of tokens
     * 1. redirection operators ['<', '>']
     * Test_cases [ cat < file.txt, ls -a > file.txt]
     * 2. environment_Var variable ['$']
     * Test_cases [ echo $$PATH, echo $Path, echo $PATH$]
     * - Once _get_env.c is called ensure to free(variable).
     * 3. other variables
     */
    while (token != NULL) {

        if (counter == 0) {
            /**
             * Parse this command by performing a lookup in the path
             * and once file is found append it to file arguments struct
             *
             */

            /* search for two start characters ['/','./','..../']*/

            /* the file provided contains a full path to the command*/
            if (strchr(token, '/') != NULL)

            {
                /*check if the file exists n if not report an error n return*/

                if(file_exists(token) && is_regular_file(token))
                {
//                    printf("The first cmd argument is %s\n", token);
                    /* Save the first token to a linked list queue*/
                    if (enqueue(pOp, token)) {
//                        print(pOp);
                        //printf("\nCapacity is %d and size is %d \n", pOp->_capacity, pOp->_size);
                    } else {
                        perror("queue enqueue error");
                    }
                }
                /* Report Error that User has provided a directory*/
                else if (isDirectory(token))
                {
                    ReportError(token, argv);
                    return (-1);

                }
                    /* Show Error that File or Directory not found */
                else
                {
                    //fprintf(stderr,"%s: %s: No such file or directory\n",argv[0],token);
                    printf("%s: %s: No such file or directory\n",argv[0],token);
                    return (-1);

                }

            }
            /**
             * full path of command is not given and we have to find
             * it in path
             */

            else {
                /**
                 * provided command is not a full path thus we have to search
                 * for the file in PATH
                 */
                 /**
                  * Check if token exists in file path else return -1
                  */

                    enqueue(pOp,token);

                //TODO: Create an option that will be used to overwrite the first item in array_queue
                // Modify the _cmd_path_search so that it will be returning a malloc'd string
                // then use this string to overwrite the array item at index 0

                /* Set env val expansion to true*/
                pOp->env_val_expansion = true;

            }


        }

        else {
            /* Check for file redirection, pipes or $ENV_NAME symbols*/
            if (strchr(token, '<') != NULL)
            {
                printf("< detected %s\n", token);
                /**
                 * Set a flag in the Structure that will guide
                 * main to delegate the next token so that it can
                 * be saved else where maybe on a different structure
                 *
                 */
//                 return (0);

            }

            else if (strchr(token, '>') != NULL)
            {
                printf("> detected %s\n", token);
//                return (0);

            }
           else if (strchr(token, '$') != NULL)
           {
               printf("$ detected in %s\n",token);
//               return (0);
           }

            else
            {
                /* Just Add token to queue */
                enqueue(pOp, token);
//                return (0);
            }
        }

        /* parse the token to ensure we evaluate the tokens properly*/
        token = strtok(NULL, whitespace);
        counter++;
    }

    return (0);
}

bool ReportError(char *filepath, char **argv) {
    struct stat sb;

    if (lstat(filepath, &sb) == -1) {
//        perror(filepath);
        return false;
    } else {
        switch (sb.st_mode & S_IFMT) {
            case S_IFBLK:  printf("%s: %s: Is a block device\n", argv[0],filepath);            break;
            case S_IFCHR:  printf("%s: %s: Is a character device\n",argv[0],filepath);        break;
            case S_IFDIR:  printf("%s: %s: Is a directory\n",argv[0],filepath);               break;
            case S_IFIFO:  printf("%s: %s: Is a FIFO/pipe\n",argv[0],filepath);               break;
            case S_IFLNK:  printf("%s: %s: Is a symlink\n",argv[0],filepath);                 break;
            case S_IFREG:  printf("%s: %s: Is a regular file\n",argv[0],filepath);            break;
            case S_IFSOCK: printf("%s: %s: Is a socket\n",argv[0],filepath);                  break;
            default:       printf("%s: %s: Is unknown?\n",argv[0],filepath);                break;
        }

        return (true);
    }
}


