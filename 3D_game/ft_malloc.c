/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahij <ybahij@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:52:00 by ybahij            #+#    #+#             */
/*   Updated: 2025/01/04 22:55:45 by ybahij           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_garbage	**ft_garbage(void)
{
	static t_garbage	*garbage;

	return (&garbage);
}

void	ft_add_garbage(void *ptr)
{
	t_garbage	**garbage;
	t_garbage	*new_garbage;
	t_garbage	*last;

	garbage = ft_garbage();
	new_garbage = malloc(sizeof(t_garbage));
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
		last = *garbage;
		while (last->next != NULL)
			last = last->next;
		last->next = new_garbage;
	}
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf("Failed to allocate memory\n");
		garbage_collector();
		exit(1);
	}
	ft_add_garbage(ptr);
	return (ptr);
}

void	garbage_collector(void)
{
	t_garbage	**garbage;
	t_garbage	*current;
	t_garbage	*next;

	garbage = ft_garbage();
	current = *garbage;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	*garbage = NULL;
}
