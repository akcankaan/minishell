#include "minishell.h"

int main(void)
{
    char *input;
    
    signal(SIGINT, handle_signal);

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;
        if (strlen(input) > 0)
            add_history(input);
        parse_input(input);
        free(input);
    }
    return 0;
}s