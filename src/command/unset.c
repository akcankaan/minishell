#include "../../includes/minishell.h"
#include <stdio.h>

void	cmd_unset(t_data *data)
{
	t_env	*node;
	t_env	*prev;
	char	*key;

	key = ft_strdup(data->cmd + 6);
	node = data->env;
	prev = NULL;
	while (node)
	{
		if (node->key)
		{
			if (ft_strncmp(node->key, key, (ft_strlen(key) + 1)) == 0)
			{
				if (prev)
					prev->next = node->next;
				else
					data->env = node->next;
				// free(node->key);              burayı garbagele freele
				// free(node->value);
				// free(node);
				break ;
			}
			prev = node;
			node = node->next;
		}
	}
	if (key)
		free(key);
}
