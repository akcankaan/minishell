#include <stdio.h>
#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <readline/history.h>

t_malloc  *get_garbage_c(void)
{
    static  t_malloc garbage_c = {NULL, NULL};
    return (&garbage_c);
}

void    gc_free(void)
{
    t_malloc    *tmp;
    t_malloc    *garbage_c;

    garbage_c = get_garbage_c()->next;
    while (garbage_c)
    {
        tmp = garbage_c;
        garbage_c = garbage_c->next;
        free(tmp->ptr);
        free(tmp);
    }
}

void    *gc_malloc(unsigned int size)
{
    void *ptr;
    t_malloc    *garbage_c;

    garbage_c = get_garbage_c();
    while (garbage_c->next)
        garbage_c = garbage_c->next;
    garbage_c->next = ft_calloc(1, sizeof(t_malloc));
    if (!garbage_c->next)
        ft_exit();
    ptr = ft_calloc(1, size);
    if (!ptr)
        ft_exit();
    *garbage_c->next = (t_malloc){.ptr = ptr, .next = NULL};
    return (ptr);
}

void	add_garbage_c(void *ptr)
{
	t_malloc	*garbage_c;

	if (!ptr)
		ft_exit();
	garbage_c = get_garbage_c();
	while (garbage_c->next)
		garbage_c = garbage_c->next;
	garbage_c->next = ft_calloc(1, sizeof(t_malloc));
	if (!garbage_c->next)
		ft_exit();
	*garbage_c->next = (t_malloc){.ptr = ptr, .next = NULL};
}
void	print_error(t_token *node, char *str, int exit_status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->value, 2);
	ft_putstr_fd(str, 2);
	*get_exit_status() = exit_status;
}

void    ft_exit(void)
{
    gc_free();
    clear_history();
    exit(1);
}
void	garbage_collecter(void *ptr)
{
	t_malloc	*garbage_c;
	t_malloc	*tmp;

	if (!ptr)
		return ;
	garbage_c = get_garbage_c();
	while (garbage_c)
	{
		if (garbage_c->ptr == ptr)
		{
			tmp->next = garbage_c->next;
			free(garbage_c);
			free(ptr);
			ptr = NULL;
			return ;
		}
		tmp = garbage_c;
		garbage_c = garbage_c->next;
	}
}
void	free_token(t_data *data)
{
	t_token	*token;
	t_token	*tmp;

	token = data->token;
	while (token)
	{
		tmp = token;
		token = token->next;
		garbage_collecter(tmp->value);
		garbage_collecter(tmp);
	}
	data->token = NULL;
}
