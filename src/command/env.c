#include "../../includes/minishell.h"

void    env(t_data *data)
{
    t_env	*env;

    env = data->env;
    while (env)
    {
        if (env->value)
        {
            ft_putstr_fd(env->key, 1);
            ft_putstr_fd("=", 1);
            ft_putstr_fd(env->value, 1);
            ft_putstr_fd("\n", 1);
        }
        env = env->next;
    }
}
