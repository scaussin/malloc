/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 11:58:13 by scaussin          #+#    #+#             */
/*   Updated: 2015/03/04 15:21:23 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print(char c)
{
	int i = 1;
	int d = 0;

	while (i <= 128)
	{
		if (c & i)
			d = d | i;
		i = i << 1;
	}
	ft_putnbr(d);
}

void	print_header(t_header *header)
{
	ft_printf("sizeof t_header : %d\nTINY_PAGE : %d\n", SIZE_H, TINY_PAGE);
	ft_printf("\n----------- print_header -----------");
	if (!header)
		ft_printf("\n(NULL)");
	while (header)
	{
		ft_printf("\naddr : %p -> %d\nsize : %d\nreal size : %d\nfree : %d\nstring : %s\nnext : %p -> %p\n",
			header, header, 
			header->size, header->next ? (void *)header->next - (void *)header : (void *)header->next - (void *)header->next,
			header->free, header + 1, &(header->next), header->next);
		header = header->next;
		ft_printf("------------------------------------");
	}
	ft_printf("\n------------------------------------\n\n");
}

int		main()
{
	char	*str;
	str = malloc2(sizeof(*str) * 4096);
	ft_printf("malloc 1 OK -> %p\n", str);
	ft_memset(str, 'a', 4096);
	str[4095] = '\0';

	char	*str2;
	str2 = malloc2(sizeof(*str2) * 3000);
	ft_printf("malloc 2 OK -> %p\n", str2);
	ft_memset(str2, 'b', 3000);
	str2[2999] = '\0';

	char	*str3;
	str3 = malloc2(sizeof(*str3) * 3000);
	ft_printf("malloc 2 OK -> %p\n", str3);
	ft_memset(str3, 'c', 3000);
	str3[2999] = '\0';

	char	*str4;
	str4 = malloc2(sizeof(*str4) * 1000);
	ft_printf("malloc 2 OK -> %p\n", str4);
	ft_memset(str4, 'd', 1000);
	str4[999] = '\0';

	char	*str5;
	str5 = malloc2(sizeof(*str5) * 30);
	ft_printf("malloc 2 OK -> %p\n", str5);
	ft_memset(str5, 'e', 30);
	str5[29] = '\0';
	
	print_header(g_first_header.tiny);

	show_alloc_mem();

	return (0);
}

/*void	free(void *ptr)
{
	
}*/

void	*malloc2(size_t size)
{
	if (size <= TINY)
		return (get_mem(size, TINY, &(g_first_header.tiny)));
	else
		return 0;
}

void	*get_mem(size_t size, unsigned int size_alloc, t_header **first_header)
{
	t_header *tmp;
	t_header *last;
	t_header *tmptmp;

	if (!(*first_header))
	{
		if (!new_alloc(first_header, size_alloc))
			return (0);
		return(get_mem(size, size_alloc, first_header));
	}
	tmp = *first_header;
	while (tmp)
	{
		if (tmp->free && (tmp->size >= size + SIZE_H || (tmp->size >= size && tmp->next)))
		{
			tmp->free = 0;
			if (tmp->next)
			{
				if (tmp->size - size >= SIZE_H)
				{
					tmptmp = tmp->next;
					tmp->next = (t_header *)((void *)tmp + size + SIZE_H);
					tmp->next->size = tmp->size - size - SIZE_H;
					tmp->next->free = 1;
					tmp->next->prev = tmp;
					tmp->next->next = tmptmp;
					tmp->next->next->prev = tmp->next;
					tmp->size = size;
				}
			}
			else
			{
				tmp->next = (t_header *)((void *)tmp + size + SIZE_H);
				tmp->next->size = tmp->size - size - SIZE_H;
				tmp->size = size;
				tmp->next->free = 1;
				tmp->next->prev = tmp;
			}
			return (tmp + 1);
		}
		last = tmp;
		tmp = tmp->next;
	}
	if (!new_alloc(&(last->next), size_alloc))
		return (0);
	return(get_mem(size, size_alloc, first_header));
}

int		new_alloc(t_header **last, unsigned int size_alloc)
{
	if (!(*last = (t_header*)mmap(0, size_alloc, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (0);
	(*last)->size = size_alloc - SIZE_H;
	(*last)->free = 1;
	(*last)->next = NULL;
	(*last)->prev = NULL;
	return (1);
}

int		print_alloc_mem(t_header *first_header)
{
	int		count;

	count = 0;
	while (first_header)
	{
		if (!first_header->free)
		{
			ft_printf("0x%X - 0x%X : %d octets\n", first_header + 1,
				(void *)(first_header + 1) + first_header->size,
				((void *)(first_header + 1) + first_header->size) -
				(void *)(first_header + 1));
			count += ((void *)(first_header + 1) + first_header->size) -
				(void *)(first_header + 1);
		}
		first_header = first_header->next;
	}
	return (count);
}

void	show_alloc_mem()
{
	int		count;

	ft_printf("TINY : 0x%X\n", g_first_header.tiny);
	count = print_alloc_mem(g_first_header.tiny);
	ft_printf("SMALL : 0x%X\n", g_first_header.small);
	count += print_alloc_mem(g_first_header.small);
	ft_printf("LARGE : 0x%X\n", g_first_header.large);
	count += print_alloc_mem(g_first_header.large);
	ft_printf("Total : %d octets\n", count);
}
