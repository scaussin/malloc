/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 15:36:09 by scaussin          #+#    #+#             */
/*   Updated: 2015/03/25 17:07:09 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_first_header g_first_header;

void	*get_mem(size_t size, unsigned int size_alloc, t_header **first_header)
{
	t_header	*tmp;
	t_header	*last;

	if (!(*first_header))
	{
		if (!new_alloc(first_header, size_alloc, NULL))
			return (0);
		return (get_mem(size, size_alloc, first_header));
	}
	tmp = *first_header;
	while (tmp)
	{
		if (tmp->free && (tmp->size >= size + SIZE_H ||
			(tmp->size >= size && tmp->next)))
		{
			create_header(tmp, size);
			return (tmp + 1);
		}
		last = tmp;
		tmp = tmp->next;
	}
	if (!new_alloc(&(last->next), size_alloc, last))
		return (0);
	return (get_mem(size, size_alloc, first_header));
}

int		new_alloc(t_header **last, unsigned int size_alloc, t_header *prev)
{
	if (!(*last = (t_header*)mmap(0, size_alloc, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (0);
	if (size_alloc <= SMALL)
		(*last)->size = size_alloc - SIZE_H;
	else
		(*last)->size = size_alloc;
	(*last)->free = 1;
	(*last)->next = NULL;
	(*last)->prev = prev;
	return (1);
}

void	*find_new_size_in_mem(t_header *header, size_t size)
{
	size_t	add_size;
	void	*new_mem;

	add_size = ft_abs(size - header->size);
	if (header->prev && header->prev->free && mem_following(header->prev) &&
		header->prev->size + SIZE_H >= add_size && same_class(header, size))
		return (move_header(add_size, header->prev, 1));
	if (header->next && header->next->free && mem_following(header) &&
		header->next->size + SIZE_H >= add_size && same_class(header, size))
		return (move_header(add_size, header, 0));
	if (header->size <= SMALL)
	{
		add_size = header->size;
		free((void *)header + SIZE_H);
		new_mem = malloc(size);
		ft_memcpy(new_mem, ((void *)header + SIZE_H), add_size);
	}
	else
	{
		new_mem = malloc(size);
		ft_memcpy(new_mem, ((void *)header + SIZE_H), header->size);
		free((void *)header + SIZE_H);
	}
	return (new_mem);
}

void	free_large(t_header *ptr)
{
	if (ptr->prev)
		ptr->prev->next = ptr->next;
	else
		g_first_header.large = ptr->next;
	if (ptr->next)
		ptr->next->prev = ptr->prev;
	munmap(ptr, ptr->size + SIZE_H);
}
