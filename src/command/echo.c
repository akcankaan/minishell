#include "../../includes/minishell.h"
#include <stdio.h>

void echo(t_data *data)
{
	int newline = 1; // Newline basılmasını kontrol eden değişken
	if (data->token->next && ft_strcmp(data->token->next->value, "-n") == 0)
	{
		newline = 0; // -n argümanı varsa newline basılmamalı
		data->token = data->token->next->next; // -n argümanını atla
	}

	while (data->token)
	{
		if (is_args(data->token))
			printf("%s", data->token->value);
		else
			return;
		if (data->token->next && (data->token->next->type == WORD || data->token->next->type == SINGLE_QUOTE || data->token->next->type == DOUBLE_QUOTE))
			printf(" ");
		//if (data->token->next && (is_args(data->token->next)))

		data->token = data->token->next;
	}

	if (newline)
		printf("\n");
}
