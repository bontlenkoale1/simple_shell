#include "shell.h"

char *get_environment_variable(char *variable_name)
{
	int index;
	
	for (index = 0; environ[index]; index++)
	{
		if (strncmp(environ[index], variable_name, strlen(variable_name)) == 0)
		{
			return environ[index];
		}
	}
	return NULL;
}
