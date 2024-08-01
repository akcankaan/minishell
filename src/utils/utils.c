#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int	is_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
		return (0);
	return (1);
}

int	is_args(t_token *node)
{
	if (node->type == WORD)
		return (1);
	else if (node->type == DOUBLE_QUOTE)
		return (2);
	else if (node->type == SINGLE_QUOTE)
		return (3);
	else
		return (0);
}

int	is_validchar(int c)
{
	return (ft_isprint(c) && c != ' ');
}
