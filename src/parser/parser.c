#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	single_command(t_data *data)
{
	while (data->token)
	{
		if(is_args(data->token))
		{
			if(!ft_strcmp(data->token->value, "echo"))
				echo(data);
			else if (!ft_strcmp(data->token->value, "env"))
				env(data);
			else if (!ft_strcmp(data->token->value, "pwd"))
				cmd_pwd(data);
			else if (!ft_strcmp(data->token->value, "exit"))
				cmd_exit(data);
		}
		if (data->token)
			data->token = data->token->next;
	}
}
