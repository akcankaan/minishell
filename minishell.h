#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

// Function prototypes
void execute_command(char *cmd);
void handle_signal(int sig);
void parse_input(char *input);
void free_memory(char **array);
void error_handling(const char *msg);

#endif