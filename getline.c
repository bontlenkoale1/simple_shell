#include "shell.h"

ssize_t get_command_line()
{
	char cmdline_buffer[1024] = {'\0'};         /* Buffer to read the command line into */
	static char *pending_commands[64] = {NULL}; /* Stores the pending command lines */
	ssize_t line_length;
	char *line;
	int command_count = 0;
	
	/* Check if there is no pending command line to execute. We only want to read
	 * line if there is no pending command */
	if (pending_commands[0] == NULL)
	{
		/* No pending command, so we need to read */
		line_length = read(STDIN_FILENO, cmdline_buffer, 1024);
		/* Check if EOF was read */
		if (line_length == 0)
		{
			/* Free any necessary data and exit since this will only occur in
			 * * non-interactive mode */
			exit(errno);
		}
		/* Get all command lines from the input */
		line = split_line(cmdline_buffer, "\n");
		while (line)
		{
			pending_commands[command_count] = strdup(line);
			command_count++;
			line = split_line(NULL, "\n");
		}
	}
	/* Pick the first command line and set it as the current command line to
	 * * execute */
	current_cmdline = pending_commands[0];
	/* Shift the commands to make the next command line be at the first index*/
	command_count = 0;
	while (pending_commands[command_count] != NULL)
		pending_commands[command_count] = pending_commands[command_count + 1];
	/* Check if the current command line is not null and return the length */
	if (current_cmdline)
		return (strlen(current_cmdline));
	return (0);
}
