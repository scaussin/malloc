/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 15:40:39 by scaussin          #+#    #+#             */
/*   Updated: 2015/04/03 14:36:17 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_first_header g_first_header;

int		print_alloc_mem(t_header *first_header)
{
	int		count;

	count = 0;
	while (first_header)
	{
		if (!first_header->free)
		{
			ft_putstr("0x");
			ft_printf_xx((unsigned int)(first_header + 1));
			ft_putstr(" - 0x");
			ft_printf_xx((unsigned int)((void *)(first_header + 1) +
				first_header->size));
			ft_putstr(" : ");
			ft_putnbr((unsigned int)(((void *)(first_header + 1) +
				first_header->size) -
				(void *)(first_header + 1)));
			ft_putstr(" octets\n");
			count += ((void *)(first_header + 1) + first_header->size) -
				(void *)(first_header + 1);
		}
		first_header = first_header->next;
	}
	return (count);
}

void	show_alloc_mem(void)
{
	int		count;

	ft_putstr("TINY : 0x");
	ft_printf_xx((unsigned int)(g_first_header.tiny));
	ft_putchar('\n');
	count = print_alloc_mem(g_first_header.tiny);
	ft_putstr("SMALL : 0x");
	ft_printf_xx((unsigned int)(g_first_header.small));
	ft_putchar('\n');
	count += print_alloc_mem(g_first_header.small);
	ft_putstr("LARGE : 0x");
	ft_printf_xx((unsigned int)(g_first_header.large));
	ft_putchar('\n');
	count += print_alloc_mem(g_first_header.large);
	ft_putstr("Total : ");
	ft_putnbr(count);
	ft_putstr(" octets\n");
}
