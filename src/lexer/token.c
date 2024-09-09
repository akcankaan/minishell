/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecer <iecer@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:30:03 by mehakcan          #+#    #+#             */
/*   Updated: 2024/09/09 12:53:53 by iecer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stddef.h>

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

t_token	*new_token(char *value, enum e_token_type type)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token));
	*token = (t_token){.value = value, .type = type, .flag = 0};
	return (token);
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
