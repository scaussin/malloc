/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 11:58:13 by scaussin          #+#    #+#             */
/*   Updated: 2015/03/24 18:21:09 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_header(t_header *header)
{
	size_t	i;
//	ft_printf("sizeof t_header : %d\nTINY_PAGE : %d\n", SIZE_H, TINY_PAGE);
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
		i = 0;
		while (i < header->size)
		{
			if (ft_isprint(*((char *)((void *)header + SIZE_H + i))))
				ft_putchar(*((char *)((void *)header + SIZE_H + i)));
			i++;
		}
		// write(1, header + 1, header->size);
		ft_printf("\nnext : %p\nprev : %p\n", header->next, header->prev);
		header = header->next;
		ft_printf("------------------------------------");
	}
	ft_printf("\n------------------------------------\n\n");
}

/*int		main()
{
	char	*str;
	str = malloc(sizeof(*str) * 4096);
	ft_memset(str, 'a', 4096);
	str[4095] = '\0';

	char	*str2;
	str2 = malloc(sizeof(*str2) * 3000);
	ft_memset(str2, 'b', 3000);
	str2[2999] = '\0';

	char	*str3;
	str3 = malloc(sizeof(*str3) * 3000);
	ft_memset(str3, 'c', 3000);
	str3[2999] = '\0';

	char	*str4;
	str4 = malloc(sizeof(*str4) * 1000);
	ft_memset(str4, 'd', 1000);
	str4[999] = '\0';

	char	*str5;
	str5 = malloc(sizeof(*str5) * 30);
	ft_memset(str5, 'e', 30);
	str5[29] = '\0';

	char	*str6;
	str6 = malloc(sizeof(*str6) * 16384);
	ft_memset(str6, 'f', 16384);
	str6[16383] = '\0';

	char	*str7;
	str7 = malloc(sizeof(*str7) * 5000000);
	ft_memset(str7, 'f', 500);
	str7[4999999] = '\0';

	char	*str8;
	str8 = malloc(sizeof(*str8) * 8000000);
	ft_memset(str8, 'f', 800);
	str8[7999999] = '\0';

	print_header(g_first_header.tiny);
	print_header(g_first_header.small);
	print_header(g_first_header.large);
	show_alloc_mem();
	free(str);
	free(str2);
	free(str3);
	free(str4);
	free(str5);
	free(str6);
	free(str7);
	free(str8);
	print_header(g_first_header.tiny);
	print_header(g_first_header.small);
	print_header(g_first_header.large);*/

	/*char	**str;

	str = malloc(sizeof(char *) * 4);
	str[0] = malloc(sizeof(char) * 10);
	str[1] = malloc(sizeof(char) * 10);
	str[2] = malloc(sizeof(char) * 10);
	str[3] = malloc(sizeof(char) * 20000);
	ft_memset(str[0], 'a', 9);
	ft_memset(str[1], 'b', 9);
	ft_memset(str[2], 'c', 9);
	ft_memset(str[3], 'd', 9);
	str[0][9] = '\0';
	str[1][9] = '\0';
	str[2][9] = '\0';
	str[3][9] = '\0';

	print_header(g_first_header.tiny);
	print_header(g_first_header.large);

	//free(str[2]);
	str[2] = realloc(str[2], 30000);

	print_header(g_first_header.tiny);
	print_header(g_first_header.large);

	show_alloc_mem();
	//show_alloc_mem_ex(str[2]);
	return (0);
}*/

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

void	*find_new_size_in_mem(t_header *header, size_t size)
{
	size_t	add_size;
	void	*new_mem;

	add_size = ft_abs(size - header->size);
	if (header->prev && header->prev->free && mem_following(header->prev) &&
		header->prev->size + SIZE_H >= add_size)
		return (move_header(add_size, header->prev, 1));
	if (header->next && header->next->free && mem_following(header) &&
		header->next->size + SIZE_H >= add_size)
		return (move_header(add_size, header, 0));
	if (header->size <= SMALL)
	{
		free((void *)header + SIZE_H);
		ft_printf("OK\n");
		new_mem = malloc(size);
		ft_memcpy(new_mem, ((void *)header + SIZE_H), header->size);
	}
	else
	{
		new_mem = malloc(size);
		ft_memcpy(new_mem, ((void *)header + SIZE_H), header->size);
		free((void *)header + SIZE_H);
	}
	return (new_mem);
}

void	*move_header(size_t add_size, t_header *header, int move_left)
{
	t_header	save_header_next;
	size_t		size_tmp;

	header->free = 0;
	if (add_size >= header->next->size)
		merge_header(header);
	else
	{
		size_tmp = header->next->size;
		header->next->size = header->size - add_size;
		header->size = size_tmp + add_size;
		header->next->free = 1;
		ft_memcpy(&save_header_next, header->next, SIZE_H);
		if (move_left)
			ft_memcpy((void *)header + SIZE_H, (void *)header->next + SIZE_H, size_tmp);
		ft_memcpy((void *)header + SIZE_H + header->size, &save_header_next, SIZE_H);
		header->next = (void *)header + SIZE_H + header->size;
		if (header->next->next)
			header->next->next->prev = header->next;
	}
	return ((void *)header + SIZE_H);
}

void	ft_memcpy_reverse(void *dest, const void *src, size_t n)
{
	while (n > 0)
	{
		((char *)dest)[n - 1] = ((char *)src)[n - 1];
		n--;
	}
}

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

void	free(void *ptr)
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

void	free_large(t_header *ptr)
{
	if (ptr->prev)
		ptr->prev->next = ptr->next;
	else
		g_first_header.large = ptr->next;
	if (ptr->next)
		ptr->next->prev = ptr->prev;
	munmap(ptr, ptr->size + SIZE_H);
}

void	merge_header(t_header *header)
{
	if (header && header->next)
	{
		header->size += header->next->size + SIZE_H;
		header->next = header->next->next;
		if (header->next)
			header->next->prev = header;
	}
}

void	*malloc(size_t size)
{
	ft_printf("%d\n", size);
	if (size <= TINY)
		return (get_mem(size, TINY_PAGE, &(g_first_header.tiny)));
	else if (size <= SMALL)
		return (get_mem(size, SMALL_PAGE, &(g_first_header.small)));
	else
		return (get_mem(size, size + SIZE_H, &(g_first_header.large)));
}

void	join_header(t_header *prev, t_header *new_h, size_t size)
{
	t_header *tmp;

	tmp = prev->next;
	prev->next = new_h;
	new_h->size = prev->size - size - SIZE_H;
	new_h->free = 1;
	new_h->prev = prev;
	new_h->next = tmp;
	new_h->next->prev = new_h;
	prev->size = size;
}

void	create_header(t_header *tmp, size_t size)
{
	tmp->free = 0;
	if (tmp->next)
	{
		if (tmp->size - size >= SIZE_H)
			join_header(tmp, (t_header *)((void *)tmp + size + SIZE_H), size);
	}
	else
	{
		if (size <= SMALL)
		{
			tmp->next = (t_header *)((void *)tmp + size + SIZE_H);
			tmp->next->size = tmp->size - size - SIZE_H;
			tmp->next->free = 1;
			tmp->next->prev = tmp;
		}
		tmp->size = size;
	}
}

void	*get_mem(size_t size, unsigned int size_alloc, t_header **first_header)
{
	t_header	*tmp;
	t_header	*last;

	if (!(*first_header))
	{
		if (!new_alloc(first_header, size_alloc, NULL))
			return (0);
		return (get_mem(size, size_alloc, first_header));
	}
	tmp = *first_header;
	while (tmp)
	{
		if (tmp->free && (tmp->size >= size + SIZE_H ||
			(tmp->size >= size && tmp->next)))
		{
			create_header(tmp, size);
			return (tmp + 1);
		}
		last = tmp;
		tmp = tmp->next;
	}
	if (!new_alloc(&(last->next), size_alloc, last))
		return (0);
	return (get_mem(size, size_alloc, first_header));
}

int		new_alloc(t_header **last, unsigned int size_alloc, t_header *prev)
{
	if (!(*last = (t_header*)mmap(0, size_alloc, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (0);
	if (size_alloc <= SMALL)
		(*last)->size = size_alloc - SIZE_H;
	else
		(*last)->size = size_alloc;
	(*last)->free = 1;
	(*last)->next = NULL;
	(*last)->prev = prev;
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

void	show_alloc_mem(void)
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
