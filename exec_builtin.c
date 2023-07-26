#include "shell.h"

int execute_builtin_exit()
{
	int exit_status = 0;
	
	if (tokens[1] != NULL)
		exit_status = atoi(tokens[1]);
	
	/* Free any necessary program data */
	free_string_array(tokens);
	free(current_cmdline);
	exit(exit_status);
}

int execute_builtin_env()
{
	int i;
	
	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

int execute_builtin_cd()
{
	char directory[1024] = {'\0'};
	if (tokens[1] == NULL)
	{
		errno = 127;
		return -1;
	}
	
	if (chdir(tokens[1]) == -1)
	{
		/* If we aren't able to cd to the directory return -1 for unsuccessful
		 * execution */
		return -1;
	}
	/* Get the current working directory */
	getcwd(directory, 1024);
	/* Set the PWD to directory */
	setenv("PWD", directory, 0);
	return 0;
}

int is_builtin_command()
{
	builtin_command actions[] = {{"exit", execute_builtin_exit},
                               {"env", execute_builtin_env},
                               {"cd", execute_builtin_cd},

                               {NULL, NULL}};
	int i;
	
	for (i = 0; actions[i].command_name; i++)
	{
		/* Compare the command with the built-in commands to find a match */
		if (strcmp(actions[i].command_name, tokens[0]) == 0)
		{
			return actions[i].action();
		}
	}
	/* No match was found */
	return (NOT_BUILTIN);
}
