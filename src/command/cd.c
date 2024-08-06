#include "../../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

void    update_oldpwd(t_data *data, char *old_pwd)
{
    t_env *node = get_env(data, "OLDPWD");
    if (!node)
    {
        node = gc_malloc(sizeof(t_env));
        node->key = ft_strdup("OLDPWD");
        node->value = ft_strdup(old_pwd);
        node->next = data->env;
        data->env = node;
    }
    else
    {
        garbage_collecter(node->value);
        node->value = ft_strdup(old_pwd);
    }
}

void    update_pwd(t_data *data)
{
    t_env *pwd_node = get_env(data, "PWD");
    if (pwd_node)
    {
        garbage_collecter(pwd_node->value);
        pwd_node->value = getcwd(NULL, 0);
    }
    else
    {
        pwd_node = gc_malloc(sizeof(t_env));
        pwd_node->key = ft_strdup("PWD");
        pwd_node->value = getcwd(NULL, 0);
        pwd_node->next = data->env;
        data->env = pwd_node;
    }
}

char    *get_cd_path(t_data *data)
{
    if (data->token->next && is_args(data->token->next))
        return (data->token->next->value);
    
    t_env *home_node = get_env(data, "HOME");
    if (home_node)
        return (home_node->value);
    
    print_error(data->token, ": Home not set\n", 1);
    return (NULL);
}

void    cmd_cd(t_data *data)
{
    char *path = get_cd_path(data);
    if (!path)
        return;
    
    char *pwd = getcwd(NULL, 0);
    if (chdir(path) == -1)
        print_error(data->token, ": No such file or directory\n", 1);
    else
    {
        update_oldpwd(data, pwd);
        update_pwd(data);
    }
    free(pwd);
}