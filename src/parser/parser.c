#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>

void debug_tokens(t_data *data) {
    t_token *token = data->token;
    while (token) {
        printf("Token value: %s\n", token->value);
        token = token->next;
    }
}

void single_command(t_data *data) {
    while (data->token) {
        if (is_args(data->token)) {
            if (!ft_strcmp(data->token->value, "echo"))
                echo(data);
            else if (!ft_strcmp(data->token->value, "env"))
                env(data);
            else if (!ft_strcmp(data->token->value, "pwd"))
                cmd_pwd(data);
            else if (!ft_strcmp(data->token->value, "exit"))
                cmd_exit(data);
            else if (!ft_strcmp(data->token->value, "export"))
                cmd_export(data);
            else if (!ft_strcmp(data->token->value, "unset"))
                cmd_unset(data);
            else if (!ft_strcmp(data->token->value, "cd"))
                cmd_cd(data);  // cd komutunu işleme
            else
                printf("minishell: %s: command not found\n", data->token->value);
        }
        if (data->token)
            data->token = data->token->next;
    }
}

