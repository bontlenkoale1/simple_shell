#include "shell.h"

void tokenize_command()
{
	char **command_tokens;
	char *token;
	int token_index = 0;
	
	/* Allocate space for the command tokens */
	command_tokens = malloc(32 * sizeof(char *));
	if (!command_tokens)
	{
		exit(1);
	}
	/* Split the current command line into arguments */
	token = custom_strtok(current_cmdline, " ");
	while (token)
	{
		command_tokens[token_index++] = strdup(token);
		token = custom_strtok(NULL, " ");
	}
	/* Set the shell's command tokens variable to the current token array */
	tokens = command_tokens;
}
