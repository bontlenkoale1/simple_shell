#include "shell.h"

void free_string_array(char **string_array)
{
	int index = 0;
	while (string_array[index])
		free(string_array[index++]);
	free(string_array);
}

