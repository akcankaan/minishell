#include "../../includes/minishell.h"
#include <stdio.h>

void	echo(t_data *data)
{
	while (data->token->next)
	{
		if (is_args(data->token->next))
			printf("%s",data->token->next->value);
		else
			return ;
		if (data->token->next && (is_args(data->token->next)))
			printf(" ");
		data->token = data->token->next;
	}
	printf("\n");
}
