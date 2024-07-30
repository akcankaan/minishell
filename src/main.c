/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:56:22 by mehakcan          #+#    #+#             */
/*   Updated: 2024/07/30 16:25:35 by mehakcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
        data.cmd = readline("WSB Team Minishel$ ");
        if (!data.cmd)
            break ;
        add_history(data.cmd);
    }
    ft_exit();
    return (0);
}