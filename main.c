/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 11:58:13 by scaussin          #+#    #+#             */
/*   Updated: 2015/02/25 20:36:55 by scaussin         ###   ########.fr       */
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

int			main()
{
	char *str;
	char	*ptr;

	str = malloc2(sizeof(*str) * 2);
	str[0] = 'a';
	str[1] = 0;
	ft_printf("%s\n", str);

	t_header *test = malloc(sizeof(t_header));
	test->size = 256;
	test->free = 110;
	test->next = 0/*(t_header*)78*/;
	ptr = (char *)test;
	int i;

	for (i = 0; i < (int)sizeof(t_header) ; i++)
	{
		ft_printf("%p i: %d ->", ptr, i);
		print(*ptr);
		ft_printf("\n");

		ptr++;
	}


/*	for (i = 0; i < sizeof(t_header) ; i++)
	{
		n = (int *)ptr;
		c = (char *)ptr;
		p = (t_header *)ptr;
		ft_printf("%p -> %d \n size: %d \n free: %d \n next: %p\n",ptr, i, *n , *c , *p);
		ptr++;
	}*/

	ft_memset(((char*)test)+16, 255, 1);

	//ft_printf("\naddr : %p -> %d\nsize : %d\nfree : %d\nnext : %p\n",
			//test, test, test->size, test->free, test->next);
	// printf("debug ");
	//print_header(g_first_header.tiny);
	return (0);
}


void		*malloc2(size_t size)
{
	if (size < TINY)
		return (get_tiny(size));
	else
		return 0;
}

void	print_header(t_header *header)
{
	ft_printf("sizeof t_header : %d\nTINY_PAGE : %d\n----------- print_header -----------", sizeof(t_header), TINY_PAGE);
	while (header)
	{
		ft_printf("\naddr : %p -> %d\nsize : %d\nreal size : %d\nfree : %d\nnext : %p\n",
			header, header, header->size, header->next - header, header->free, header->next);
		header = header->next;
	}
	ft_printf("------------------------------------\n");
}

void	*get_tiny(size_t size)//return first free
{
	t_header *tmp;

	if (!g_first_header.tiny)
		gen_tiny(&g_first_header.tiny);
	tmp = g_first_header.tiny;
	while (tmp && !tmp->free && tmp->size < size)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->next = tmp + size + sizeof(t_header);
		tmp->next->size = tmp->size - size + sizeof(t_header);
		tmp->next->free = 1;
		tmp->free = 0;
		tmp->size = size;
		return (tmp + sizeof(t_header));
	}
	else
		gen_tiny(&(tmp->next));
	get_tiny(size);
	return (0);
}

void		gen_tiny(t_header **last)
{
	ft_printf("gen_tiny\n");
	*last = (t_header*)mmap(0, TINY_PAGE, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	(*last)->size = TINY_PAGE - sizeof(t_header);
	(*last)->free = 1;
	(*last)->next = NULL;
	//print_header(g_first_header.tiny);
}
