#include "../../includes/minishell.h"
#include <stdio.h>

void echo(t_data *data)
{
	int newline = 1;
	data->token = data->token->next;
	while (data->token && ft_strcmp(data->token->value, "-n") == 0)
	{
		newline = 0;
		data->token = data->token->next;
	}

	while (data->token)
	{
		if (is_args(data->token))
			printf("%s", data->token->value);
		else
			return;
		if (data->token->next && (is_args(data->token->next)))
			printf(" ");
		data->token = data->token->next;
	}

	if (newline)
		printf("\n");
}
