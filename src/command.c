#include "../minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void execute_command(char **args, char **env)
{
    if (fork() == 0)
    {
        if (execve(args[0], args, env) < 0)
        {
            perror("minishell");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int status;
        wait(&status);
    }
}

void handle_command(t_data *data, char **env)
{
    t_token *current = data->token;
    char *command[256];
    int i = 0;

    while (current)
    {
        if (current->type == TOKEN_REDIRECT_IN)
        {
            current = current->next;
            if (current && current->type == TOKEN_WORD)
            {
                if (handle_redirect_in(current->value) < 0)
                    return;
            }
            else
            {
                fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n", current->value);
                return;
            }
        }
        else
        {
            command[i++] = current->value;
        }
        current = current->next;
    }
    command[i] = NULL;

    execute_command(command, env);
}

int handle_redirect_in(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("minishell");
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("minishell");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

void handle_echo(char **args)
{
    int i = 1;
    int newline = 1;

    if (args[1] && ft_strcmp(args[1], "-n") == 0)
    {
        newline = 0;
        i = 2;
    }
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
}

void handle_cd(char **args, t_data *data)
{
    char *home_dir;
    char cwd[1024];

    if (!args[1])
    {
        home_dir = getenv("HOME");
        if (home_dir)
            chdir(home_dir);
        else
            fprintf(stderr, "minishell: cd: HOME not set\n");
    }
    else if (chdir(args[1]) != 0)
    {
        perror("minishell: cd");
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        ft_setenv(data, "PWD", cwd);
    }
    else
    {
        perror("minishell: getcwd");
    }
}

void handle_env(t_data *data)
{
    t_env *env = data->env;
    while (env)
    {
        if (env->key && env->value)
            printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}

void handle_export(char **args, t_data *data)
{
    char *key;
    char *value;

    if (!args[1])
    {
        fprintf(stderr, "minishell: export: not enough arguments\n");
        return;
    }

    char *equal_sign = strchr(args[1], '=');
    if (!equal_sign)
    {
        fprintf(stderr, "minishell: export: invalid format\n");
        return;
    }

    key = ft_substr(args[1], 0, equal_sign - args[1]);
    value = ft_strdup(equal_sign + 1);
    if (!key || !value)
    {
        free(key);
        free(value);
        return;
    }

    ft_setenv(data, key, value);
    free(key);
    free(value);
}

void handle_unset(char **args, t_data *data)
{
    t_env *current;
    t_env *prev;

    if (!args[1])
    {
        fprintf(stderr, "minishell: unset: not enough arguments\n");
        return;
    }

    current = data->env;
    prev = NULL;

    while (current)
    {
        if (ft_strcmp(current->key, args[1]) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                data->env = current->next;

            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void handle_exit(t_data *data)
{
    gc_free();
    exit(0);
}

int ft_setenv(t_data *data, char *name, const char *value)
{
    t_env *env = data->env;
    char *key;
    char *val;

    while (env)
    {
        if (ft_strcmp(env->key, name) == 0)
        {
            free(env->value);
            env->value = ft_strdup(value);
            return 0;
        }
        env = env->next;
    }

    env = gc_malloc(sizeof(t_env));
    if (!env)
        return -1;

    key = ft_strdup(name);
    val = ft_strdup(value);
    if (!key || !val)
    {
        free(key);
        free(val);
        return -1;
    }

    env->key = key;
    env->value = val;
    env->next = data->env;
    data->env = env;

    return 0;
}
