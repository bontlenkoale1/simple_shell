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
#include <limits.h>
#include <sys/types.h>
#include <stdbool.h>

int main(int argc, char **argv);
void print_prompt1(void);
void print_prompt2(void);
char *read_cmd(void);
int exec_cmd(char *cmd);
#endif
