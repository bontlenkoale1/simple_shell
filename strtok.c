#include "shell.h"

char *custom_strtok(char *str, char *delimiters)
{
	static char *buffer; /* Local buffer to track the progress */
	int delimiter_index; /* Delimiter index */
	char *token;
	/* Set the buffer if we are calling the function the first time */
	if (str != NULL)
		buffer = str;
	/* Get the start of the token */
	for (; *buffer != '\0'; buffer++)
	{
		for (delimiter_index = 0; delimiters[delimiter_index] != '\0'; delimiter_index++)
		{
			if (*buffer == delimiters[delimiter_index])
				break;
		}
		if (delimiters[delimiter_index] == '\0')
			break;
	}
	/* Set the token to point to the start */
	token = buffer;
	if (*token == '\0')
		return NULL;
	/* Set the end of the token */
	
	for (; *buffer != '\0'; buffer++)
	{
		for (delimiter_index = 0; delimiters[delimiter_index] != '\0'; delimiter_index++)
		{
			if (*buffer == delimiters[delimiter_index])
			{
				*buffer = '\0';
				buffer++;
				return (token);
			}
		}
	}
	return (token);
}
