#include "../../includes/minishell.h"
#include <limits.h>

char	*ft_str_arr_join(char **str_list, unsigned int str_count)
{
	unsigned int	total_len;
	unsigned int	result_len;
	unsigned int	i;
	char			*result;

	i = 0;
	total_len = 0;
	if (!str_list)
		return (NULL);
	while (i < str_count)
	{
		total_len += ft_strlen(str_list[i]);
		i++;
	}
	if (total_len == 0)
		return (NULL);
	result = (char *)gc_malloc(sizeof(char) * (total_len + 1));
	i = -1;
	result_len = 0;
	while (++i < str_count && str_list[i])
		result_len += ft_strlcpy(&result[result_len], str_list[i], UINT_MAX);
	return (result);
}

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
	if (node->type == SINGLE_QUOTE)
		return (2);
	return (node->type == WORD || node->type == DOUBLE_QUOTE);
}

int	is_validchar(int c)
{
	return (ft_isprint(c) && c != ' ');
}


int	rdir(t_token *node)
{
	if (node->type == HERADOC)
		return (2);
	return (node->type == REDIRECT_IN || node->type == REDIRECT_OUT
		|| node->type == APPEND);
}


int	skip_space(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}