/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_hexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 15:37:32 by scaussin          #+#    #+#             */
/*   Updated: 2015/04/03 14:33:55 by scaussin         ###   ########.fr       */
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
		ft_putstr("0x");
		ft_printf_xx((unsigned int)ptr + i);
		ft_putstr("    ");
		print_hexa(header->size, ptr, i, &j);
		ft_putstr("   ");
		printf_char(header->size, ptr, i, j);
		i += j;
		ft_putchar('\n');
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
			ft_putchar('.');
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
				ft_putchar('0');
			ft_putnbr_xx(c);
		}
		else
			ft_putstr("  ");
		if ((*j + 1) % 2 == 0)
			ft_putchar(' ');
		(*j)++;
	}
}
