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
	return (node->type == WORD || node ->type == SINGLE_QUOTE || node->type == DOUBLE_QUOTE);
}

int	is_validchar(int c)
{
	return (ft_isprint(c) && c != ' ');
}
