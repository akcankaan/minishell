#include "../../includes/minishell.h"

void	cmd_export(t_data *data)
{
	t_token *node;
	char *key;
	char *value;
	t_env *env;
	int len;

	node = data->token;
	if (node)
	{
		len = ft_strchr(node->value, '=') - node->value;
		node = node->next;
		key = ft_substr(node->value, 0, len);
		value = ft_substr(node->value, len + 1, ft_strlen(node->value) - len);
		add_garbage_c(key);
		add_garbage_c(value);
		env = get_env(data, key);
		if (env)
		{
			garbage_collecter(env->value);
			env->value = ft_strdup(value);
		}
		else
		{
			env = gc_malloc(sizeof(t_env));
			env->key = key;
			env->value = value;
			env->next = data->env;
			data->env = env;
		}
	}
}
