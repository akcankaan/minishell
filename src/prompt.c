#include "../minishell.h"

void get_prompt(t_data *data, char **env)
{
    while (1)
    {
        data->user_input = readline("minishell$ ");
        if (!data->user_input)
            break;

        if (data->user_input && *data->user_input)
            add_history(data->user_input);

        if (data->user_input)
        {
            lexer(data);
            handle_command(data, env);
        }

        t_token *current = data->token;
        while (current)
        {
            t_token *tmp = current;
            current = current->next;
            free(tmp->value);
            free(tmp);
        }
        data->token = NULL;
        free(data->user_input);
    }
    ft_exit(data);
}
