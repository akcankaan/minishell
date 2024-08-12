#include "../../includes/minishell.h"

t_token	*args_to_token(char **args)
{
	t_token	*token;
	int		i;

	i = -1;
	token = NULL;
	while (args[++i])
        add_token_back(&token, new_token(WORD, args[i]));
	return (token);
}

void    join_value(t_token *node)
{
    char   *new_value;

    if (!node || !node->prev)
        return ;
    new_value = ft_strjoin(node->prev->value, node->value);
    add_garbage_c(new_value);
    node->prev->value = new_value;
    node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    node->prev->flag = node->flag;
}

char    *expand_variable(t_data *data, t_token *node, char *tmp, int i)
{
    t_env   *env;
    char    *env_key;
    char    *prev;
    char    *result;

    env_key = ft_substr(tmp + 1, 0, i - 1);
    add_garbage_c(env_key);
    prev = ft_substr(node->value, 0, tmp - node->value);
    add_garbage_c(prev);

    env = get_env(data, env_key);
    if (env)
        result = ft_str_arr_join((char *[]){prev, env->value, tmp + i}, 3);
    else if (*env_key == '?')
        result = ft_str_arr_join((char *[]){prev, ft_itoa(*get_exit_status()), tmp + 2}, 3);
    else
        result = ft_str_arr_join((char *[]){prev, tmp + i}, 2);
    garbage_collecter(node->value);
    add_garbage_c(result);

    return (result ? result : ft_strdup(""));
}

void    select_expand_value(t_data *data, t_token *node)
{
    char    *tmp;
    int     i;

    tmp = ft_strchr(node->value, '$');
    while (tmp)
    {
        i = 1;
        while (tmp[i] && (ft_isalnum(tmp[i]) || tmp[i] == '?'))
        {
            i++;
            if (ft_isdigit(tmp[i]))
                break;
        }
        if (i == 1)
        {
            tmp++;
            tmp = ft_strchr(tmp, '$');
            continue;
        }
        node->value = expand_variable(data, node, tmp, i);
        tmp = ft_strchr(node->value, '$');
    }
}

void    expander(t_data *data)
{
    t_token *node;
    int heredoc_mode;

    node = data->token;
    heredoc_mode = 0;
    while (node)
    {
        if (node->type == HERADOC)
        {
            heredoc_mode = 1;
            node = node->next;
            continue;
        }

        if ((node->type == WORD || node->type == DOUBLE_QUOTE) && !heredoc_mode)
            select_expand_value(data, node);
        if (node->prev && node->prev->flag)
            join_value(node);
        if (!node->flag)
            heredoc_mode = 0;
        node = node->next;
    }
}
