#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	lexer_word(t_data *data, int *i)
{
	t_token	*node;
	int		end;

	end = *i;
	while (data->cmd[end] && !(ft_strchr(" \t\v\f|<>\'\"", data->cmd[end])))
		++end;
	node = new_token(WORD, ft_substr(data->cmd, *i, end - *i));
	add_garbage_c(node->value);
	add_token_back(&data->token, node);
	*i = end - 1;
}

void	lexer_quote(t_data *data, int *i, enum e_token_type type)
{
	t_token	*node;
	int		end;
	char	quote;

	quote = data->cmd[*i];
	end = *i;
	while (data->cmd[++end] != quote)
		if (data->cmd[end] == '\0')
		{
			data->syntax = 1;
			return;
		}
	node = new_token(type, ft_substr(data->cmd, *i + 1, end - *i - 1));
	add_garbage_c(node->value);
	add_token_back(&data->token, node);
	*i = end;
}

void	lexer(t_data *data)
{
	int		i;

	i = -1;
	while (data->cmd[++i])
	{
		while (data->cmd[i] == ' ')
			++i;
		if (data->cmd[i] == '\0')
			break ;
		if (data->cmd[i] == '|')
			; //lexer_pipe
		else if (data->cmd[i] == '\'')
			lexer_quote(data, &i, SINGLE_QUOTE); //lexer_single_quote
		else if (data->cmd[i] == '\"')
			lexer_quote(data, &i, DOUBLE_QUOTE); //lexer_double_quote
		else if (data->cmd[i] == '<')
			;	//lexer_redirect_in
		else if (data->cmd[i] == '>')
			;	//lexer_redirect_out
		else
			lexer_word(data, &i);
	}
}
