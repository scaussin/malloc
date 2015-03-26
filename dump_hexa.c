/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_hexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 15:37:32 by scaussin          #+#    #+#             */
/*   Updated: 2015/03/25 16:07:18 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_alloc_mem_ex(void *ptr)
{
	t_header		*header;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!ptr)
		return ;
	header = (ptr - SIZE_H);
	while (i < header->size)
	{
		ft_printf("0x%X    ", ptr + i);
		print_hexa(header->size, ptr, i, &j);
		ft_printf("   ");
		printf_char(header->size, ptr, i, j);
		i += j;
		ft_printf("\n");
	}
}

void	printf_char(size_t size, void *ptr, unsigned int i, unsigned int j)
{
	unsigned int	k;
	unsigned char	c;

	k = 0;
	while (k < (i + j > size ? size - i : j))
	{
		ft_memcpy(&c, ptr + i + k, 1);
		if (ft_isprint(c))
			write(1, ptr + i + k, 1);
		else
			ft_printf(".");
		k++;
	}
}

void	print_hexa(size_t size, void *ptr, unsigned int i, unsigned int *j)
{
	unsigned char	c;

	*j = 0;
	while (*j < 16)
	{
		if (i + *j < size)
		{
			ft_memcpy(&c, ptr + i + *j, 1);
			if (c < 15)
				ft_printf("0");
			ft_printf("%X", c);
		}
		else
			ft_printf("  ");
		if ((*j+1) % 2 == 0)
			ft_printf(" ");
		(*j)++;
	}
}
