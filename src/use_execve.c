#include "../includes/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

void    use_execve(t_data *data)
{
    pid_t   pid;
    char    **env;
    char    *path;
    char    **args;

    env = env_to_char(data);
    if (is_args(data->token))
    {
        path = finding_path(data, data->token);
        if (!path)
            return ;
        args = get_command_args(data->token);
        while (data->token->next && is_args(data->token->next))
            data->token = data->token->next;
        pid = fork();
        if (pid == -1)
            ft_exit();
        else if (pid == 0)
            if (execve(path, args, env) == -1)
                perror("execve");
        waitpid(pid, get_exit_status(), 0);
        update_exit_status(data);
    }
}