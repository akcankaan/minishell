/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:11:26 by mehakcan          #+#    #+#             */
/*   Updated: 2024/07/30 16:27:00 by mehakcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/minishell.h"
#include "../libft/libft.h"
#include <readline/history.h>

t_malloc  *get_garbage_c(void)
{
    static  t_malloc *garbage_c = {NULL, NULL};

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

void    ft_exit(void)
{
    gc_free();
    clear_history();
    exit(1);
}