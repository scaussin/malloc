/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 11:58:13 by scaussin          #+#    #+#             */
/*   Updated: 2015/03/02 19:38:14 by scaussin         ###   ########.fr       */
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
	//ft_printf("sizeof t_header : %d\nTINY_PAGE : %d\n", SIZE_H, TINY_PAGE);
	ft_printf("\n----------- print_header -----------");
	while (header)
	{
		ft_printf("\naddr : %p -> %d\nsize : %d\nreal size : %d\nfree : %d\nstring : %s\nnext : %p\n",
			header, header, header->size, header->next ? (void *)header->next - (void *)header : (void *)header->next - (void *)header->next,
			header->free, header + 1, header->next);
		header = header->next;
		ft_printf("------------------------------------");
	}
	ft_printf("\n------------------------------------\n\n");
}

int			main()
{
	char	*str;

	str = malloc2(sizeof(*str) * 4096);
	ft_printf("malloc 1 OK -> %p\n", str);
	ft_memset(str, 'a', 4096);
	str[4095] = '\0';
	//print_header(g_first_header.tiny);

	char	*str2;
	str2 = malloc2(sizeof(*str2) * 4096);
	ft_printf("malloc 2 OK -> %p\n", str2);
	ft_memset(str2, 'b', 4096);
	str2[4095] = '\0';
	//print_header(g_first_header.tiny);
	/*char	*str3;
	if ((str3 = malloc2(sizeof(*str3) * 4096)))
	{
		ft_printf("malloc3\n");
		ft_memset(str3, 'c', 4095);
		str3[4095] = '\0';
	}

	print_header(g_first_header.tiny);
*/
	/*str2 = malloc2(sizeof(*str2) * 3);
	str2[0] = 'b';
	str2[1] = 'c';
	str2[2] = 0;*/

	return (0);
}

/*void	free(void *ptr)
{
	if (ptr)
	{
		if sylvain est moche 
			return sylain est moche
	}
}*/

void		*malloc2(size_t size)
{
	if (size <= TINY)
		return (get_tiny(size));
	else
		return 0;
}

void	*get_tiny(size_t size)//return first free
{
	t_header *tmp;
	t_header *last;

	//print_header(g_first_header.tiny);
	if (!g_first_header.tiny)
	{
		gen_tiny(&g_first_header.tiny);
		return(get_tiny(size));
	}
	tmp = g_first_header.tiny;
	while (tmp)
	{
		ft_printf("while tmp\n");
		if (tmp->free && tmp->size >= size + SIZE_H)
		{
			if (tmp->next)
			{
				// TODO : raccordement
				ft_printf("TODO : raccordement...");
				return (0);
			}
			else
			{
				tmp->free = 0;
				tmp->next = (t_header *)((void *)tmp + size + SIZE_H);
				/*if (tmp->size - SIZE_H == size)
					tmp->next->size = 0;
				else*/
					tmp->next->size = tmp->size - size - SIZE_H;
				tmp->size = size;
				tmp->next->free = 1;
				tmp->next->prev = tmp;
				//print_header(g_first_header.tiny);
				return (tmp + 1);
			}
		}
		last = tmp;
		tmp = tmp->next;
	}
	// liste pleine
	ft_printf("avant - %p %p\n", &tmp, tmp);
	print_header(tmp);

	gen_tiny(&tmp);
	ft_printf("apres - %p %p\n", &tmp, tmp);
	print_header(tmp);
	tmp->prev = last;
	return(get_tiny(size));
}

void		gen_tiny(t_header **last)
{
	ft_printf("gen_tiny\n");
	*last = (t_header*)mmap(0, TINY_PAGE, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	(*last)->size = TINY_PAGE - SIZE_H;
	(*last)->free = 1;
	(*last)->next = NULL;
	(*last)->prev = NULL;
}
