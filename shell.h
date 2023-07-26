#ifndef SHELL_H
#define SHELL_H

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
#include <sys/stat.h>

#define NOT_BUILTIN 67

typedef struct builtin {
  char *name;
  int (*action)();
} builtin_command;

extern int errno;
extern char **environ;
extern int execution_counter;
char **command_tokens;
char *current_cmdline;
extern char *program_name;

void initialize_shell_data();


#endif
