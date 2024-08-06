#include <stdio.h>
#include "../../includes/minishell.h"

int ft_str_is_numeric(char *str)
{
    int i;

    i = skip_space(str, 0);
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void cmd_exit(t_data *data)
{
    gc_free();
    printf("exit\n");
    exit(data->exit_status);
}

// void cmd_exit(t_data *data)
// {
//     t_token *node;

//     node = data->token->next;
//     if (node)
//     {
//         if (is_args(node))
//         {
//             if (node->value && ft_str_is_numeric(node->value))
//                 *get_exit_status() = ft_atoi(node->value) % 256;
//             else
//                 print_error(node, ": numeric argument required\n", 2);
//             if (node->next)
//                 print_error(node->next, ": too many arguments\n", 2);
//             exit(*get_exit_status());
//         }
//         else
//         {
//             ft_putendl_fd("exit", 2);
//             *get_exit_status() = 255;
//         }
//         gc_free();
//         ft_putendl_fd("exit", 2);
//         exit(*get_exit_status());
//     }
// }

int *get_exit_status(void)
{
    static int exit_status = 0;

    return (&exit_status);
}

void update_exit_status(t_data *data)
{
    if (WIFEXITED(data->exit_status))
        data->exit_status = WEXITSTATUS(data->exit_status);
    else
    {
     if (WIFSIGNALED(data->exit_status))
        data->exit_status = 128 + WTERMSIG(data->exit_status);
    }
}