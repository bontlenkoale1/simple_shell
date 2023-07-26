#include "shell.h"

char *custom_strcpy(char *destination, char *source)
{
	int index;
	
	for (index = 0; source[index]; ++index)
		destination[index] = source[index];
	destination[index] = '\0';
	return (destination);
}

char *custom_strcat(char *destination, char *source)
{
	int dest_len = strlen(destination);
	int index;
	
	for (index = 0; source[index]; ++index)
		destination[dest_len + index] = source[index];
	destination[dest_len + index] = '\0';
	return (destination);
}
