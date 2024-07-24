#include "../minishell.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

void add_token(t_token **token_list, char *value, t_token_type type, t_malloc *gc)
{
    t_token *new_token = gc_malloc(sizeof(t_token));
    if (!new_token)
        return;

    new_token->value = ft_strdup(value);
    new_token->type = type;
    new_token->next = NULL;

    if (*token_list == NULL)
    {
        *token_list = new_token;
    }
    else
    {
        t_token *current = *token_list;
        while (current->next)
            current = current->next;
        current->next = new_token;
    }
}

t_token_type get_token_type(char *str)
{
    if (ft_strcmp(str, "|") == 0)
        return TOKEN_PIPE;
    else if (ft_strcmp(str, "<") == 0)
        return TOKEN_REDIRECT_IN;
    else if (ft_strcmp(str, ">") == 0)
        return TOKEN_REDIRECT_OUT;
    else if (ft_strcmp(str, ">>") == 0)
        return TOKEN_APPEND;
    else if (ft_strcmp(str, "<<") == 0)
        return TOKEN_HEREDOC;
    else
        return TOKEN_WORD;
}

void classify_token(t_data *data, char *str)
{
    t_token_type type = get_token_type(str);
    add_token(&data->token, str, type, data->garbage_c);
}

void handle_quotes(char **input, char **token, int *i, int *j)
{
    char quote = (*input)[*i];
    (*i)++;
    (*token)[(*j)++] = quote;

    while ((*input)[*i] && (*input)[*i] != quote)
    {
        (*token)[(*j)++] = (*input)[*i];
        (*i)++;
    }

    if ((*input)[*i] == quote)
    {
        (*token)[(*j)++] = (*input)[*i];
        (*i)++;
    }
    else
    {
        char *new_input = NULL;
        while (1)
        {
            new_input = readline("> ");
            if (!new_input)
                break;

            *input = ft_strjoin(*input, "\n");
            *input = ft_strjoin(*input, new_input);

            while ((*input)[*i] && (*input)[*i] != quote)
            {
                (*token)[(*j)++] = (*input)[*i];
                (*i)++;
            }

            if ((*input)[*i] == quote)
            {
                (*token)[(*j)++] = (*input)[*i];
                (*i)++;
                break;
            }
        }
        free(new_input);
    }
}

char *get_next_token(char **input, int *i)
{
    char *token = ft_calloc(256, sizeof(char));
    int j = 0;

    while ((*input)[*i] && (*input)[*i] != ' ')
    {
        if ((*input)[*i] == '\'' || (*input)[*i] == '\"')
            handle_quotes(input, &token, i, &j);
        else
        {
            token[j] = (*input)[*i];
            (*i)++;
            j++;
        }
    }

    token[j] = '\0';
    return token;
}

void lexer(t_data *data)
{
    int i = 0;
    char *token;
    char **input = ft_split(data->user_input, ' ');

    while (input[i])
    {
        int j = 0;
        while (input[i][j])
        {
            token = get_next_token(&input[i], &j);
            classify_token(data, token);
            free(token);
        }
        i++;
    }

    for (int k = 0; input[k]; k++)
        free(input[k]);
    free(input);
}
