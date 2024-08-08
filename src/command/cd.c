#include "../../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

void	update_oldpwd(t_data *data, char *pwd)
{
	t_env	*node;

	node = get_env(data, "OLDPWD");
	if (!node)
	{
		node = gc_malloc(sizeof(t_env));
		node->key = ft_strdup("OLDPWD");
		node->value = ft_strdup(pwd);
		node->next = data->env;
		data->env = node;
	}
	else
	{
		free(node->value);
		node->value = ft_strdup(pwd);
	}
}

void	cmd_cd(t_data *data, t_token *node)
{
	t_env	*env;
	char	*path;
	char	*pwd;

	path = NULL;
	env = get_env(data, "HOME");
	if (node && is_args(node))
		path = node->value;
	else if (!node && env)
		path = env->value;
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		*get_exit_status() = 1;
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		print_error(node, ": No such file or directory\n", 1);
		free(pwd); // Bellek sızıntısını önlemek için pwd'yi serbest bırak
	}
	else
	{
		update_oldpwd(data, pwd);
		free(pwd); // getcwd tarafından döndürülen eski pwd'yi serbest bırakıyoruz
		pwd = getcwd(NULL, 0);
		t_env *pwd_node = get_pwd(data);
		free(pwd_node->value); // Mevcut PWD değerini serbest bırakıyoruz
		pwd_node->value = pwd;
		add_garbage_c(pwd);
	}
}
