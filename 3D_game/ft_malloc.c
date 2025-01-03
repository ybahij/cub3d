#include "../cub3d.h"

t_garbage **ft_garbage(void)
{
    static t_garbage *garbage = NULL;
    return &garbage;
}

void ft_add_garbage(void *ptr)
{
    t_garbage **garbage = ft_garbage();
    t_garbage *new_garbage = malloc(sizeof(t_garbage));
    if (!new_garbage)
    {
        printf("Failed to allocate memory for garbage collector\n");
        garbage_collector();
        exit(1);
    }
    new_garbage->ptr = ptr;
    new_garbage->next = NULL;

    if (*garbage == NULL)
        *garbage = new_garbage;
    else
    {
        t_garbage *last = *garbage;
        while (last->next != NULL)
            last = last->next;
        last->next = new_garbage;
    }
}

void	*ft_malloc(size_t size)
{
	void	*ptr = malloc(size);
	if (!ptr)
	{
		printf("Failed to allocate memory\n");
		garbage_collector();
		exit(1);
	}
	ft_add_garbage(ptr);
	return (ptr);
}

void garbage_collector(void)
{
    t_garbage **garbage = ft_garbage();
    t_garbage *current = *garbage;

    while (current)
    {
        t_garbage *next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    *garbage = NULL;
}