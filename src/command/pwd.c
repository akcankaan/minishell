#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

t_env	*get_pwd(t_data *data)
{
	t_env	*node;

	node = get_env(data, "PWD");
	if (!node)
	{
		node = gc_malloc(sizeof(t_env));
		node->key = "PWD";
		node->value = getcwd(NULL, 0);
		add_garbage_c((void *)node->value);
		node->next = data->env;
		data->env = node;
	}
	return (node);
}

void	cmd_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	add_garbage_c(pwd);
	printf("%s\n", pwd);
}