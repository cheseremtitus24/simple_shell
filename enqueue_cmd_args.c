/* Created by uwelekezo on 3/7/23.*/
#include "main.h"
/**
 * _input_tokenizer - Create a function that Captures/Parses and Generates
 * Commandline Arguments that are saved to the op_t array queue
 * @command_input: Command Input to be Parsed
 * @argv: will be used to parse special commandline variables e.g "$,<,>"
 * @pOp: Array queue to save command_input
 * Return: Zero on success else -1 on Failure
*/
int _input_tokenizer(char *command_input, char __attribute__((unused)) **argv,
					 op_t *pOp)
{
	/**
	 * Tokenize the input args and add them to the queue
	 */
	char *token;
	const char *whitespace = " \n\r\f\t\v";
	char *temp = NULL;

	if (!command_input)
	{
		return (-1);

	}
	if (!pOp)
	{
		return (-1);
	}

	temp = strdup(command_input);

	token = strtok(temp, whitespace);

	while (token != NULL)
	{
		/* Just Add token to queue */
		enqueue(pOp, token);
		/* parse the token to ensure we evaluate the tokens properly */
		token = strtok(NULL, whitespace);
	}
	return (0);
}
