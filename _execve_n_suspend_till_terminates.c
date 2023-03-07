/* Created by uwelekezo on 3/6/23.*/


#include "main.h"
/**
 * execute_command- passes args to execve
 * @pArgs: arguments array
 * @argv: commandline arguments array from main
 *
 * Description- appends a null at end of array before passing array
 * to execve. Furthermore, it locates the binary file in its fullpath
 * by searching for it in path.
 *
 * Return: 0 on success -1 on failure
 */
int execute_command(op_t *pArgs, char **argv)
{
	extern char **environ;
	char **envp = environ;
	pid_t pid;
	int i;
	char *command;

	command = NULL;

	/* Capture the command name and retrieve it from the env_var_list*/
	/**
	 * Check if the file exists and if so Proceed
	 * else Search for this File in the path Then Replace it.
	 */
	command = peek(pArgs);
	/**
	 * Handle Special Case of Printing
	 * Internal Env
	 */
	if (strcmp(command, "env") == 0 || strcmp(command, "printenv") == 0)
	{
		for (i = 0; envp[i] != NULL; i++)
		{
			printf("%s\n", envp[i]);
		}
		reset(pArgs);
		return (0);
	}
	if (!file_exists(command))
	{
		/**
		 * If the command is not found
		 * Look for a matching file in the
		 * Current System Path
		 * then return its Full Path
		 * to Replace Current Command.
		 * else set command to NULL
		 */

		/*char *env_binary_paths = _getenv("PATH");*/
		/*printf("fullpath is %s\n",env_binary_paths);*/

		/*printf("full binary in path is %s\n",find_binary("ls")); */
		/**
		 * split the envpaths by ":"
		 * iterate through each to find where the file can be found
		 * Else set command to NULL
		 */
		command = find_binary(command);
	}
	/**
	 * if Command is not found in current
	 * System Path Exit from the
	 * Program
	 */
	if (!command)
	{
		dprintf(2, "%s: 1:%s: not found\n", argv[0], peek(pArgs));
		reset(pArgs);
		return (0);
	}
	/* End of the CommandList Array must be terminated with a NULL value*/
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
	if (pid == -1)
	{
		fprintf(stderr, "\nFailed to fork!\n");
		return (-1);
	}
	/*char *arr3[2] = {"/usr", NULL};*/
	/* child instance*/
	if (pid == 0)
	{
		/* You can pass environment variables to end instead of NULL*/
		execve(command, pArgs->arr, envp);
		/*        execvp(command, arr3);*/
		fprintf(stderr, "\n%s Failed!", command);
		/* If you don't include this you will leave  zombie processes running */
		exit(EXIT_FAILURE);
	}
	/* Parent process waits for the child to terminate*/
	waitpid(pid, NULL, 0);
	if (command)
		free(command);
	reset(pArgs);
	return (0);
}
