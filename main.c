#include <wait.h>
#include <zconf.h>
#include "main.h"

int execute_command(op_t *pArgs);
void reset(op_t *pArray);
/**
 * main - gets the pid and parent pid of a running process
 * Return: 0
 */
int main(int __attribute__((unused)) argc, char **argv) {
    int bytes_read, input_args_status;
    bool maintain_runtime_loop;
    bool no_eof_present;
    size_t nbytes;
    char *command_input;
    char *temp;
    char *expanded_command_path;
    int stringlen;
    int __attribute__((unused))command_counter_control;
    char __attribute__((unused))**temp_ptr_arr;
    op_t command_argument_struct_exec;


    command_input = NULL;
    temp = NULL;
    maintain_runtime_loop = true;
    no_eof_present = true;
    /* repeat until a blank line is input */
    do {

        /* reset our counter once a single loop finishes*/
        temp_ptr_arr = (char **) malloc(ARG_ARR_SIZE * sizeof(char *));
        command_argument_struct_exec.arr = temp_ptr_arr;
	command_argument_struct_exec._capacity = 3;
	command_argument_struct_exec._size = 0;
       command_argument_struct_exec.env_val_expansion=	false;
        reset(&command_argument_struct_exec);


        command_counter_control = 0;
        /* prompt and gather input */
        printf("$ ");
        bytes_read = getline(&command_input, &nbytes, stdin);
        _trim(command_input);
        /*printf("The bytes that have been read in are %d",bytes_read);*/
        /* if empty string is provided or when length is 1 skip loop*/

/*        if (bytes_read == 1)*/
/*            continue;*/

        temp = strdup(command_input);
        _trim(temp);
        stringlen = strlen(temp);
/*        printf("The trimmed string is <%d>",stringlen);*/
/* handle case when a newline character is input to terminal*/
        if (stringlen == 0) {
            free(temp);
            continue;
        }


        if (strncmp(temp, TERM_Exit_Signal, 5) == 0) {
            maintain_runtime_loop = false;
            free(temp);

            continue;
        }

        /* show input */
        free(temp);
        /* Check for an EOF character*/
        /**
         * getline return -1 when EOF
         * character is detected in User input
         */
        if (bytes_read == -1) {
            /* ctrl-D present in string */
            no_eof_present = false;

        }

        else
            {
            /* ctrl-D not in string */
/*            printf("You typed (%ld): %s",nbytes,command_input);*/
/*            printf("After tokenization we have the following: \n");*/

            /**
             * Below function should return a structure that is
             * ready to be passed to execve subroutine
             */


            /* adds commands arguments to queue array for */
            input_args_status = _cmd_input_tokenizer(command_input, argv, &command_argument_struct_exec);
            /* Ready to process structure of arguments*/
            /* if input_args_status is -1 if an error is reported was not found*/
            if (input_args_status < 0) {
/*                command_argument_struct_exec.arr = NULL;*/
                reset(&command_argument_struct_exec);
                continue;
                /*free(command_argument_struct_exec.arr);*/
            }
            else if (input_args_status == 0 )
            {

                /**
                 * Perform a check in the array_struct of
                 * whether a command path expansion ocurred
                 */
                if (command_argument_struct_exec.env_val_expansion) {
                    /* Replace the first command with the path expansion */
                    expanded_command_path = _cmd_path_search_tokenizer(command_argument_struct_exec.arr[0],
                                                                       &command_argument_struct_exec);
                    /* If command was found in path it will return a string else NULL*/
                    if (expanded_command_path != NULL) {
/*                 printf("We have expanded and the found path is %s\n", expanded_command_path);*/
                        /* Replace array index 0 with the found command full path*/
                        command_argument_struct_exec.arr[0] = expanded_command_path;
/*                 print(&command_argument_struct_exec);*/
                        command_argument_struct_exec.env_val_expansion = false;
/*                        printf("This is content of structure to be executed \n");*/
/*                        print(&command_argument_struct_exec);*/
/*                        printf("\n end of check\n");*/
                        command_argument_struct_exec.env_val_expansion = false;
                        execute_command(&command_argument_struct_exec);
/*                        continue;*/
                    }
                    else {
                        printf("%s: command not founds\n", command_argument_struct_exec.arr[0]);
                        command_argument_struct_exec.env_val_expansion = false;
                    }
                }
                else
                    {

                    execute_command(&command_argument_struct_exec);
                }


            }

            reset(&command_argument_struct_exec);



            /**
             * TODO: Process tokens
             */

        }
/*            print(&command_argument_struct_exec);*/

    } while (maintain_runtime_loop && no_eof_present);
    free(command_input);
    return (0);

}

int execute_command(op_t *pArgs) {
    /* call fork to execute the command*/
    /* Add NULL to end of ARRAY for ExecVE*/

	pid_t pid;
	char *command;

    command = peek(pArgs);
    enqueue(pArgs, NULL);
/*    printf("The size of filed array is %d", pArgs->_size);*/
    /**
     * Wrap execute within a fork
     * subprocess so that the
     * main thread is not replaced
     */
    /* Create a child process for the command execution*/
    pid = fork();
    /* If it failed, exit program*/
    if (pid == -1) {
        fprintf(stderr, "\nFailed to fork!\n");
        return (-1);
    }
    /*char *arr3[2] = {"/usr", NULL};*/
    /* child instance*/
    if (pid == 0) {
/*        print(pArgs);*/
        execve(command, pArgs->arr, NULL);
/*        execvp(command, arr3);*/
        fprintf(stderr, "\n%s Failed!", command);
        /* If you don't include this you will leave
         * zombie processes running
         */
        exit(EXIT_FAILURE);

    }
    /* Parent process waits for the child to terminate*/
    waitpid(pid, NULL, 0);
    return (0);

}

void reset(op_t *pArray)
{
    unsigned int i;
    for(i = 0; i < pArray->_size; i++)
        dequeue(pArray);
}
