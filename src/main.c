/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 11:58:13 by scaussin          #+#    #+#             */
/*   Updated: 2015/04/02 18:34:43 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <fcntl.h>

t_first_header		g_first_header = {0, NULL, NULL};

/*int		main()
{

    char    *str;
    int        i;

    i = 1;
    str = malloc(i);
    while (i < 100)
    {
        str = malloc2(i);
        ft_memset(str, 'a',  i);
        if (i % 10 == 0)
        {
        	ft_putnbr(i);
        	ft_putendl("");
        }
        i++;
    }

	show_alloc_mem();
	return (0);
}*/

/*
	char *line;
	int fd = open("test", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		//print_header(g_first_header.tiny);
		ft_printf("%s\n", line);
		//free2(line);
	}
*/

void	*malloc(size_t size)
{
	void *ret;
	ft_putendl("malloc");
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

	if (!ptr)
		return ;

	if (!search_header(g_first_header.tiny, ptr))
		return ;

	header = (t_header *)(ptr - SIZE_H);
	ft_putendl("free");
	write(1, header+1, header->size);
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

	if (!ptr || size == 0)
		return (ptr);
	header = (t_header *)(ptr - SIZE_H);
	if (header->size >= size)
		return (ptr);
	return (find_new_size_in_mem(header, size));
}
