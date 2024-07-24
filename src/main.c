#include "../libft/libft.h"
#include "../minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void initializer(t_data *data)
{
    data->env = gc_malloc(sizeof(t_env));
    data->token = NULL;
    data->cmd = NULL;
    data->prompt = NULL;
}

void create_env(char **envp, t_data *data)
{
    t_env *node;
    int i;
    char *tmp;

    i = -1;
    node = data->env;
    while (envp[++i])
    {
        tmp = ft_strchr(envp[i], '=');
        data->env->key = ft_substr(envp[i], 0, tmp - envp[i]);
        data->env->value = ft_strdup(tmp + 1);
        add_garbage_c(data->env->key);
        add_garbage_c(data->env->value);
        if (envp[i + 1])
        {
            data->env->next = gc_malloc(sizeof(t_env));
            data->env = data->env->next;
            data->env->key = NULL;
            data->env->value = NULL;
            data->env->next = NULL;
        }
    }
    data->env = node;
}

t_env *get_env(t_data *data, char *key)
{
    t_env *node;

    node = data->env;
    while (node)
    {
        if (!ft_strncmp(node->key, key, ft_strlen(key)))
        {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void prtoken(t_data *data)
{
    t_token *node;

    node = data->token;
    while (node)
    {
        printf("%s\n", node->value);
        node = node->next;
    }
}

int main(int ac, char **av, char **env)
{
    t_data data;

    (void)av;
    if (ac >= 2)
    {
        return 0;
    }
    initializer(&data);
    if (env && *env)
    {
        create_env(env, &data);
    }
    while (1)
    {
        data.cmd = readline("My bash-0.1$ ");
        if (!data.cmd)
        {
            break;
        }
        add_history(data.cmd);
        lexer(&data);
        // expander(&data); // Bu fonksiyonlar tanımlanmalı
        // parser(&data);
        // free_token(&data);
    }
    gc_free();
    return 0;
}
