#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

// Struct Definitions
typedef struct s_malloc
{
    void *ptr;
    struct s_malloc *next;
} t_malloc;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef enum s_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_APPEND,
    TOKEN_HEREDOC,
    TOKEN_SINGLE_QUOTE,
    TOKEN_DOUBLE_QUOTE
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

typedef struct s_data
{
    t_token *token;
    t_env *env;
    t_malloc *garbage_c;
    char *prompt;
    char *user_input;
    char *cmd;
} t_data;

// Function Prototypes
// exit.c
void *gc_malloc(unsigned int size);
void gc_free(void);
void ft_exit(t_data *data);
void add_garbage_c(void *ptr);

// main.c
void create_env(char **envp, t_data *data);
void initializer(t_data *data);

// prompt.c
void get_prompt(t_data *data, char **env);

// lexer.c
void add_token(t_token **token_list, char *value, t_token_type type, t_malloc *gc);
t_token_type get_token_type(char *str);
void classify_token(t_data *data, char *str);
void handle_quotes(char **input, char **token, int *i, int *j);
char *get_next_token(char **input, int *i);
void lexer(t_data *data);

// command.c
void handle_echo(char **args);
void handle_cd(char **args, t_data *data);
void handle_pwd();
void handle_env(t_data *data);
void handle_unset(char **args, t_data *data);
void handle_export(char **args, t_data *data);
void handle_exit(t_data *data);
void handle_command(t_data *data, char **env);

// command_execution.c
int handle_redirect_in(char *filename);
int ft_setenv(t_data *data, char *name, const char *value);

#endif
