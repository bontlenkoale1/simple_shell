#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(info_t *info_t)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info_t->argv[1])
	{
		dir = _getenv(info_t, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info_t, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info_t->argv[1], "-") == 0)
	{
		if (!_getenv(info_t, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info_t, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info_t, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info_t->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info_t, "can't cd to ");
		_eputs(info_t->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info_t, "OLDPWD", _getenv(info_t, "PWD="));
		_setenv(info_t, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
