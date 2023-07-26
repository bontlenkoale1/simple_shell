#include "shell.h"

char *integer_to_string(int num)
{
	char *str;
	char *reversed_str;
	int i, len;
	
	str = malloc(6 * sizeof(char));
	if (!str)
		exit(1);
	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	
	for (i = 0; num; i++)
	{
		str[i] = '0' + (num % 10);
		num /= 10;
	}
	str[i] = '\0';
	
	/* Reverse the string */
	reversed_str = strdup(str);
	len = strlen(str);
	for (i = 0; --len >= 0; ++i)
		str[i] = reversed_str[len];
	free(reversed_str);
	return (str);
}

void print_error_message(char *error_msg)
{
	write(STDERR_FILENO, error_msg, strlen(error_msg)); 
}

void print_command_error()
{
	char *error_num_str = integer_to_string(execution_counter);
	
	print_error_message(program_name);
	print_error_message(": ");
	print_error_message(error_num_str);
	print_error_message(": ");
	print_error_message(tokens[0]);
	print_error_message(": ");
	
	if (errno == 126 || errno == 127)
		print_error_message(errno == 127 ? "not found\n" : "Permission denied\n");
	/* Print error specific to the cd command */
	
	if (strcmp(tokens[0], "cd") == 0)
	{
		print_error_message("can't cd to ");
		print_error_message(tokens[1]);
		print_error_message("\n");
	}
	free(error_num_str);
}
