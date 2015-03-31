/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 15:39:16 by scaussin          #+#    #+#             */
/*   Updated: 2015/03/26 16:56:20 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_first_header g_first_header;

int		ft_abs(int i)
{
	return (i > 0 ? i : -i);
}

int		mem_following(t_header *header)
{
	if (header->next &&
		((void *)header + header->size) + SIZE_H == header->next)
		return (1);
	return (0);
}

int		same_class(t_header *header, size_t size)
{
	if (header->size <= TINY && size <= TINY)
		return (1);
	else if (header->size <= SMALL && size <= SMALL)
		return (1);
	else if (header->size > SMALL && size > SMALL)
		return (1);
	else
		return (0);
}

/*
**
*/

void	print_header(t_header *header)
{
	//size_t	i;

	ft_printf("\n----------- print_header -----------");
	if (header == g_first_header.tiny)
		ft_printf("\n--------------- TINY ---------------");
	else if (header == g_first_header.small)
		ft_printf("\n--------------- SMALL --------------");
	else if (header == g_first_header.large)
		ft_printf("\n--------------- LARGE --------------");
	if (!header)
		ft_printf("\n(NULL)");
	while (header)
	{
		ft_printf("\naddr : %p\nsize : %d\nreal size : %d\nfree : %d\nstring : ",
			header,	header->size, header->next ? (void *)header->next - (void *)header : (void *)header->next - (void *)header->next,
			header->free);
		write(1, header +1, header->size);
		//i = 0;
		/*while (i < header->size)
		{
			if (ft_isprint(*((char *)((void *)header + SIZE_H + i))))
				ft_putchar(*((char *)((void *)header + SIZE_H + i)));
			i++;
		}*/
		ft_printf("\nnext : %p\nprev : %p\n", header->next, header->prev);
		header = header->next;
		ft_printf("------------------------------------");
	}
	ft_printf("\n------------------------------------\n\n");
}
