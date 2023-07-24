#include "shell.h"

char *shell_name;

int main(int arg_count, char *arg_values[])
{
	char *shell_prompt = "";
	
	shell_name = arg_values[0];
	initialize_all_shell_data();
	
	/* Check if the shell is in interactive mode */
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		shell_prompt = "($) ";
	execute_shell(shell_prompt);
	return (0);
}

