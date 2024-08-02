#include <stdio.h>
#include "../libft/libft.h"
#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <string.h>
#include <unistd.h>

void    initilazor(t_data *data)
{
    data->env = gc_malloc(sizeof(t_env));
    data->token = NULL;
    data->cmd = 0;
    data->prompt = 0;
}

void    get_readline(t_data *data)
{
    data->cmd = readline("Minishell$ ");
    if (data->cmd && !is_space(data->cmd))
    {
        free(data->cmd);
        get_readline(data);
    }
    if (!data->cmd)
        ft_exit();
    add_history(data->cmd);
}

t_env    *get_env(t_data *data, char *key)
{
    t_env	*node;

    node = data->env;
    while (node)
    {
        if (!ft_strcmp(node->key, key))
            return (node);
        node = node->next;
    }
    return (NULL);
}

void	create_env(char **envp, t_data *data)
{
	t_env	*node;
	int		i;
	char	*tmp;

	i = -1;
	node = data->env;
	while (envp[++i])
	{
		tmp = ft_strchr(envp[i], '=');
		data->env->key = ft_substr(envp[i], 0, tmp - envp[i]);
		data->env->value = ft_substr(envp[i], tmp - envp[i] + 1,
				ft_strlen(envp[i]));
		add_garbage_c(data->env->key);
		add_garbage_c(data->env->value);
		if (envp[i + 1])
			data->env->next = gc_malloc(sizeof(t_env));
		data->env = data->env->next;
	}
	data->env = node;
}

int main(int ac, char **av, char **env)
{
    t_data data;
    (void)av;
    (void)env;
    if (ac >= 2)
        return (0);
    initilazor(&data);
    if (env && *env)
        create_env(env, &data);
    while (1)
    {
        get_readline(&data);
        lexer(&data);
        //token a ekleme yapılıp yapılmadığını kontrol etmek için
        //while (data.token)
        //{
        //    printf("Value = %s\n", data.token->value);
        //    printf("Type = %d\n", data.token->type);
        //    data.token = data.token->next;
        //}
        single_command(&data);
        free_token(&data);
        free(data.cmd);
    }
    ft_exit();
    return (0);
}
