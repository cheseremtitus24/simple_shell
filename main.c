#include "main.h"


/**
 * main - main program
 * @argc: Number of commandline arguments passed in
 * @argv: array of commandline arguments passed in
 * @envp: Environment Variables array passed in
 * Return: 0 always
 */
int main(int __attribute__((unused)) argc,
		char **argv, char __attribute__((unused))**envp)
{
	int bytes_read, input_args_status;
	bool maintain_runtime_loop;
	bool no_eof_present;
	size_t nbytes;
	char *command_input;
	char *temp;
	int stringlen;
	op_t command_argument_struct_exec;

	int __attribute__((unused)) command_counter_control;
	char __attribute__((unused)) **temp_ptr_arr;

	command_input = NULL;
	command_argument_struct_exec._size = 0;
	command_argument_struct_exec._capacity = 0;
	temp = NULL;
	maintain_runtime_loop = true;
	no_eof_present = true;
	/* repeat until a blank line is input */
	while (maintain_runtime_loop && no_eof_present)
	{
		command_counter_control = 0;
		/* prompt and gather input */
		write(STDIN_FILENO, "$ ", 2);
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
		if (stringlen == 0)
		{
			free(temp);
			continue;
		}


		if (strncmp(temp, TERM_Exit_Signal, 5) == 0)
		{
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
		if (bytes_read == -1)
		{
			/* ctrl-D present in string */
			no_eof_present = false;

		} else
		{
			/* ctrl-D not in string */
/*            printf("You typed (%ld): %s",nbytes,command_input);*/
/*            printf("After tokenization we have the following: \n");*/

			/**
			 * Below function should return a structure that is
			 * ready to be passed to execve subroutine
			 */


			/* adds commands arguments to queue array for */
			input_args_status = _input_tokenizer(command_input, argv,
					&command_argument_struct_exec);
			/* Ready to process structure of arguments*/
			/* if input_args_status is -1 if an error is reported was not found*/
			if (input_args_status < 0)
			{
/*                command_argument_struct_exec.arr = NULL;*/
				reset(&command_argument_struct_exec);
				continue;
				/*free(command_argument_struct_exec.arr);*/
			} else if (input_args_status == 0)
			{

				/**
				 * Perform a check in the array_struct of
				 * whether a command path expansion ocurred
				 */
				if (command_argument_struct_exec.arr)
				{

					execute_command(&command_argument_struct_exec, argv);
				} else
				{
					continue;
				}
			}

		}

	}
	free(command_input);
	free(command_argument_struct_exec.arr);
	return (0);

}
