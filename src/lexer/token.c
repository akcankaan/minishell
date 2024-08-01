#include "../../includes/minishell.h"

t_token	*new_token(enum e_token_type type, char *value)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	return (token);
}

t_token	*last_token(t_token *node)
{
	if (node == NULL)
		return (0);
	while (node)
	{
		if (node->next == NULL)
			return (node);
		node = node->next;
	}
	return (node);
}

void	add_token_back(t_token **node, t_token *new)
{
	t_token	*token;

	if (!new)
		return ;
	if (*node)
	{
		token = last_token(*node);
		new->prev = token;
		token->next = &*new;
	}
	else
		*node = new;
}
