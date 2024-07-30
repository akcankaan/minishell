/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:57:17 by mehakcan          #+#    #+#             */
/*   Updated: 2024/07/30 16:22:26 by mehakcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    char *value;
    struct s_token *prev;
    struct s_token *next;
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
    int    exit_status;
}              t_data;

// exit.c
void    *gc_malloc(unsigned int size);
void    ft_exit(void);
void    gc_free(void);
void    add_garbage_c(void *ptr);

// main.c
void    initilazor(t_data *data);
void    create_env(char **envp, t_data *data);

#endif