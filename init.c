#include "shell.h"

char **command_tokens;
char *current_cmdline;

void initialize_shell_data()
{
	/* Initializes and allocates all memory needed by the shell */
	command_tokens = NULL;
	current_cmdline = NULL;
}

