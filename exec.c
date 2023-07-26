#include "shell.h"

char *find_executable_path(char *command)
{
	char *path_env = strdup(_getenv("PATH"));
	char *path_value, *directory;
	char *full_path;
	int path_len;
	
	/* Get the value of the PATH environment variable */
	custom_strtok(path_env, "=");
	path_value = custom_strtok(NULL, "=");
	
	/* Get the first directory in the path */
	directory = _strtok(path_value, ":");
	/* Iterate over each directory in the path to find the executable */
	while (directory != NULL)
	{
		/* Calculate the length of the full path */
		path_len = (strlen(command) + strlen(directory) + 2);
		/* Allocate space for the full path */
		full_path = malloc(path_len * sizeof(char));
		if (full_path == NULL)
			exit(EXIT_FAILURE);
		/* Build the full path */
		
		_strcpy(full_path, directory);
		_strcat(full_path, "/");
		_strcat(full_path, command);
		
		/* Check if the full path exists */
		if (access(full_path, F_OK) == 0)
		{
			free(path_env);
			return (full_path);
		}
		
		/* Free the current full path, since it is not needed */
		free(full_path);
		
		/* Get the next directory in the path */
		directory = _strtok(NULL, ":");
	}
	free(path_env);
	return (NULL);
}

void execute_command()
{
	pid_t child_pid;
	int status;
	
	/* Create a new process to run the execve function in */
	child_pid = fork();
	
	/* Check if the process was not created successfully */
	if (child_pid == -1)
	{
		exit(errno);
	}
	
	/* Check if we are in the child process */
	if (child_pid == 0)
	{
		/* Execute the command passing the arguments */
		execve(tokens[0], tokens, environ);
		exit(1);
	}
	/* Check if we are in the parent process */
	if (child_pid > 0)
	{
		/* Wait for the child process to finish executing */
		waitpid(child_pid, &status, WUNTRACED);
		/* Check if the child process exited normally */
		if (WIFEXITED(status))
		{
			/* Set the errno to the exit code */
			errno = WEXITSTATUS(status);
		}
	}
}

int execute_binary_command()
{
	char *command = tokens[0];
	char *executable_path;
	
	/* Check if the command is a path */
	if (command[0] == '/' || command[0] == '.')
	{
		/* Check if the file exists and has execution permission */
		if (access(command, F_OK) != 0 || access(command, X_OK) != 0)
		{
			errno = 127;
			return (-1);
		}
	}
	else
	{
		/* Find the path to the executable if it exists */
		executable_path = find_executable_path(command);
		
		/* If the path doesn't exist */
		if (executable_path == NULL)
		{
			errno = 127;
			return (-1);
		}
		
		/* Replace the entered command with the full path */
		free(tokens[0]);
		tokens[0] = executable_path;
	}
	
	/* Execute the command */
	execute_command();
	return (0);
}
