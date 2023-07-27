#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
#include <stdio.h>
#include "shell.h"
  

/**
 * print_error - a function that prints an error
 * @info_t: variable
 * @error_message: prints error
 *
 * Return: void
 */
void print_error(info_t *info_t, char *error_message)
{
	
    if (info_t == NULL || error_message == NULL)
    {
       /* If either of the parameters is NULL, there's nothing meaningful to print */
        printf("Error: Invalid input parameters.\n");
        return;
    }

    /* Print the error message */
    printf("Error: %s\n", error_message);
}
#include <stdio.h>
#include <stdbool.h>

int _erratoi(char *str) 
{
    int result = 0;
    bool negative = false;

    
    if (*str == '-') 
    {
        negative = true;
        str++; /* Move past the negative sign */
    }


    
    while (*str != '\0' && (*str >= '0' && *str <= '9')) 
    {
        /* Convert the character to an integer and add it to the result */
        result = result * 10 + (*str - '0');
        str++;
    }

    /* If the number was negative, negate the result */
    if (negative) 
    {
        result = -result;
    }

    return result;
}
#include <stdbool.h>
#include <stdio.h>

void remove_comments(char *str)
{
    bool in_single_line_comment = false;
    bool in_multi_line_comment = false;
    char *read_ptr = str;  /* Pointer for reading characters from the input string */
    char *write_ptr = str; /* Pointer for writing characters back to the input string */

    while (*read_ptr != '\0')
    {
        if (!in_single_line_comment && !in_multi_line_comment)
	{
            if (*read_ptr == '/' && *(read_ptr + 1) == '/')
	    {
                in_single_line_comment = true;
                read_ptr++;
	    }
	    else if (*read_ptr == '/' && *(read_ptr + 1) == '*')
	    {
                in_multi_line_comment = true;
                read_ptr++;
	    }
	    else
	    {
                *write_ptr = *read_ptr;
                write_ptr++;
            }
        }
	else if (in_single_line_comment)
	{
            if (*read_ptr == '\n')
	    {
                in_single_line_comment = false;
                *write_ptr = *read_ptr;
                write_ptr++;
            }
        }
	else if (in_multi_line_comment)
	{
            if (*read_ptr == '*' && *(read_ptr + 1) == '/')
	    {
                in_multi_line_comment = false;
                read_ptr++;
            }
        }
        read_ptr++;
    }
    *write_ptr = '\0';
}
