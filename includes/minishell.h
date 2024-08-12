
#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"

typedef struct s_malloc
{
    void *ptr;
    struct s_malloc *next;
}              t_malloc;

enum    e_token_type
{
    WORD,
    PIPE,
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    REDIRECT_IN,
    REDIRECT_OUT,
    APPEND,
    HERADOC,
};

typedef struct s_token
{
    enum e_token_type type;
    char           *value;
    struct s_token  *prev;
    struct s_token  *next;
    int             flag; 
}             t_token;

typedef struct  s_env
{
    char    *key;
    char    *value;
    struct s_env *next;
}               t_env;


typedef struct s_data
{
    t_env   *env;
    t_token *token;
    char    *prompt;
    char    *cmd;
    int     syntax;
    int    exit_status;
}              t_data;

// exit.c
void    *gc_malloc(unsigned int size);
void    ft_exit(void);
void    gc_free(void);
void    add_garbage_c(void *ptr);
void	free_token(t_data *data);
void	garbage_collecter(void *ptr);
void    print_error(t_token *node, char *str, int exit_status);


// main.c
void    initilazor(t_data *data);
void    create_env(char **envp, t_data *data);
t_env    *get_env(t_data *data, char *key);

// utils.c
char	*ft_str_arr_join(char **str_list, unsigned int str_count);
int	is_space(char *cmd);
int	is_args(t_token *node);
int	is_validchar(int c);
int	rdir(t_token *node);
int	skip_space(char *str, int i);

// expander.c

void    expander(t_data *data);
void    select_expand_value(t_data *data, t_token *node);


// parser.c
void    parse_commands(t_data *data);
void	single_command(t_data *data);


// token.c
t_token	*new_token(enum e_token_type type, char *value);
t_token	*last_token(t_token *node);
void	add_token_back(t_token **node, t_token *new);

// lexer.c
void	lexer(t_data *data);

//command
void	echo(t_data *data);
void    env(t_data *data);
void	cmd_pwd(void);
void    cmd_exit(t_data *data);
void	cmd_export(t_data*data);
void	cmd_unset(t_data *data);
void	cmd_cd(t_data *data, t_token *node);
int						*get_exit_status(void);

char    **env_to_char(t_data *data);
char	*finding_path(t_data *data, t_token *node);
void    use_execve(t_data *data);

t_env	*get_pwd(t_data *data);

char	**get_command_args(t_token *node);
void    update_exit_status(t_data *data);



#endif
