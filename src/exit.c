#include "../minishell.h"

t_malloc *g_garbage_collector = NULL;

void add_garbage_c(void *ptr)
{
    t_malloc *new_node = malloc(sizeof(t_malloc));
    if (!new_node)
    {
        exit(EXIT_FAILURE);
    }
    new_node->ptr = ptr;
    new_node->next = g_garbage_collector;
    g_garbage_collector = new_node;
}

void gc_free(void)
{
    t_malloc *current = g_garbage_collector;
    t_malloc *tmp;
    while (current)
    {
        free(current->ptr);
        tmp = current;
        current = current->next;
        free(tmp);
    }
    g_garbage_collector = NULL;
}

void *gc_malloc(unsigned int size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        gc_free();
        exit(EXIT_FAILURE);
    }
    add_garbage_c(ptr);
    return ptr;
}

void ft_exit(t_data *data)
{
    gc_free();
    exit(1);
}
