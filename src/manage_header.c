/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 15:41:30 by scaussin          #+#    #+#             */
/*   Updated: 2015/04/03 14:35:52 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	insert_header(t_header *prev, t_header *new_h, size_t size)
{
	t_header *tmp;

	tmp = prev->next;
	prev->next = new_h;
	new_h->size = prev->size - size - SIZE_H;
	new_h->free = 1;
	new_h->prev = prev;
	new_h->next = tmp;
	new_h->next->prev = new_h;
	prev->size = size;
}

void	create_header(t_header *tmp, size_t size)
{
	tmp->free = 0;
	if (tmp->next)
	{
		if (tmp->size - size >= SIZE_H)
			insert_header(tmp, (t_header *)((void *)tmp + size + SIZE_H), size);
	}
	else
	{
		if (size <= SMALL)
		{
			tmp->next = (t_header *)((void *)tmp + size + SIZE_H);
			tmp->next->size = tmp->size - size - SIZE_H;
			tmp->next->free = 1;
			tmp->next->prev = tmp;
			tmp->next->next = NULL;
		}
		tmp->size = size;
	}
}

void	merge_header(t_header *header)
{
	if (header && header->next)
	{
		header->size += header->next->size + SIZE_H;
		header->next = header->next->next;
		if (header->next)
			header->next->prev = header;
	}
}

void	*move_header(size_t add_size, t_header *header, int move_left)
{
	t_header	save_header_next;
	size_t		size_tmp;

	header->free = 0;
	if (add_size >= header->next->size)
		merge_header(header);
	else
	{
		size_tmp = header->next->size;
		header->next->size = header->size - add_size;
		header->size = size_tmp + add_size;
		header->next->free = 1;
		ft_memcpy(&save_header_next, header->next, SIZE_H);
		if (move_left)
			ft_memcpy((void *)header + SIZE_H, (void *)header->next + SIZE_H,
				size_tmp);
		ft_memcpy((void *)header + SIZE_H + header->size, &save_header_next,
			SIZE_H);
		ft_printf("OK2\n");
		header->next = (void *)header + SIZE_H + header->size;
		if (header->next->next)
			header->next->next->prev = header->next;
	}
	return ((void *)header + SIZE_H);
}
