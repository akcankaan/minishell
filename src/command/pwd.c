#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

char *get_pwd(t_data *data)
{
    t_env *node;

    node = get_env(data, "PWD");
    if (!node)
    {
        node = gc_malloc(sizeof(t_env));
        node->key = "PWD";
        node->value = getcwd(NULL, 0);
        add_garbage_c((void *)node->value);
        node->next = data->env;
        data->env = node;
    }
    return (node->value);
}

void cmd_pwd(t_data *data)
{
    char    *pwd;

    pwd = get_pwd(data);
    printf("%s\n", pwd);
}