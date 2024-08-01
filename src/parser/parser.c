#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	single_command(t_data *data)
{
	while (data->token->next)
	{
		if(is_args(data->token))
		{
			if(!ft_strcmp(data->token->value, "echo"))
				echo(data);
		}
		if(data->token->next)
			data->token = data->token->next;
	}
}
