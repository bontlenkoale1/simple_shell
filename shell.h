#ifndef SHELL_H
#define SHELL_H

#define MAX_COMMAND 10

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void prompt(char **av, char **env);
