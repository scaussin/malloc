/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 11:58:13 by scaussin          #+#    #+#             */
/*   Updated: 2015/04/08 13:00:08 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <fcntl.h>

t_first_header		g_first_header = {0, NULL, NULL};

void	*malloc(size_t size)
{
	void *ret;

	if (size <= TINY)
		ret = get_mem(size, TINY_PAGE, &(g_first_header.tiny));
	else if (size <= SMALL)
		ret = get_mem(size, SMALL_PAGE, &(g_first_header.small));
	else
		ret = get_mem(size, size + SIZE_H, &(g_first_header.large));
	return (ret);
}

void	free(void *ptr)
{
	t_header	*header;

	if (!ptr || !search_header(g_first_header.tiny, ptr))
		return ;
	header = (t_header *)(ptr - SIZE_H);
	header->free = 1;
	if (header->size > SMALL)
	{
		free_large(header);
		return ;
	}
	if (header->prev && header->prev->free == 1 && mem_following(header->prev))
	{
		merge_header(header->prev);
		header = header->next->prev;
	}
	if (header->next && header->next->free == 1 && mem_following(header))
		merge_header(header);
}

void	*realloc(void *ptr, size_t size)
{
	t_header	*header;
	void		*tmp;

	if (!ptr && size == 0)
		return (NULL);
	if (!ptr && size != 0)
		return (malloc(size));
	if (ptr && size == 0)
	{
		tmp = malloc(((t_header *)(ptr - SIZE_H))->size);
		ft_memcpy(tmp, ptr, ((t_header *)(ptr - SIZE_H))->size);
		free(ptr);
		return (tmp);
	}
	header = (t_header *)(ptr - SIZE_H);
	if (header->size >= size)
		return (ptr);
	return (find_new_size_in_mem(header, size));
}
