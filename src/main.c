/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 11:58:13 by scaussin          #+#    #+#             */
/*   Updated: 2015/03/30 15:56:49 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <fcntl.h>

t_first_header		g_first_header = {0, NULL, NULL};

int		main()
{
	char *line;
	int fd = open("test", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		//print_header(g_first_header.tiny);
		ft_printf("%s\n", line);
		//free2(line);
	}
	show_alloc_mem();
	//print_header(g_first_header.tiny);
	return (0);
}

void	*malloc2(size_t size)
{
	if (size <= TINY)
		return (get_mem(size, TINY_PAGE, &(g_first_header.tiny)));
	else if (size <= SMALL)
		return (get_mem(size, SMALL_PAGE, &(g_first_header.small)));
	else
		return (get_mem(size, size + SIZE_H, &(g_first_header.large)));
}

void	free2(void *ptr)
{
	t_header	*header;

	if (!ptr)
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

void	*realloc2(void *ptr, size_t size)
{
	t_header	*header;

	if (!ptr || size == 0)
		return (ptr);
	header = (t_header *)(ptr - SIZE_H);
	if (header->size >= size)
		return (ptr);
	return (find_new_size_in_mem(header, size));
}
