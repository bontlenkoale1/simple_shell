#include "shell.h"

int command_counter = 0; /* Keeps track of the number of command lines that have been executed */

void run_shell(char *shell_prompt) 
{
	ssize_t num_bytes;
	int is_builtin_cmd, error_code;
	
	while (1)
	{
		/* Increment the command counter for every command line */
		command_counter++;
		/* Show prompt */
		write(STDIN_FILENO, shell_prompt, strlen(shell_prompt));
		/* Get the command line */
		num_bytes = read_command_line();
		/* Check if the command line is empty */
		if (num_bytes == 0)
			continue;
		/* Create the tokens - command args */
		tokenize_command();
		is_builtin_cmd = error_code = check_builtin_command();
		/* Check if the command is not a builtin command */
		if (is_builtin_cmd == NOT_BUILTIN)
		{
			/* execute the external command */
			error_code = execute_external_command();
		}
		
		/* Check if the command exits with an error */
		
		if (error_code != EXIT_SUCCESS)
		{
			/* Print the error message */
			print_error();
		}
		/* Free the data generated for this command */
		free_tokens_array(tokens);
		free(command_line);
	}
}
