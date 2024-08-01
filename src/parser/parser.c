#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	single_command(t_data *data)
{
		if(is_args(data->token))
		{
			if(!ft_strcmp(data->token->value, "echo"))
				echo(data);
		}
}
