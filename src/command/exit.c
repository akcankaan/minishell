#include <stdio.h>
#include "../../includes/minishell.h"

void cmd_exit(t_data *data)
{
    gc_free();
    printf("exit\n");
    exit(data->exit_status);
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