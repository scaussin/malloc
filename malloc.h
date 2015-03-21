/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 11:59:08 by scaussin          #+#    #+#             */
/*   Updated: 2015/03/20 18:44:54 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include <sys/mman.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define SIZE_H sizeof(struct s_header)

# define TINY 4096
# define SMALL 16384

# define TINY_PAGE (TINY + SIZE_H) * 2//getpagesize()
# define SMALL_PAGE (SMALL + SIZE_H) * 2//getpagesize()

typedef struct		s_header
{
	size_t			size;
	char			free;
	struct s_header	*next;
	struct s_header	*prev;
}					t_header;

typedef struct		s_first_header
{
	t_header		*tiny;
	t_header		*small;
	t_header		*large;
}					t_first_header;

t_first_header		g_first_header = {0, NULL, NULL};

void				*malloc2(size_t size);
int					new_alloc(t_header **last, unsigned int size_alloc, t_header *prev);
void				*get_mem(size_t size, unsigned int size_alloc, t_header **first_header);
void				print_header(t_header *header);
void				show_alloc_mem(void);
int					print_alloc_mem(t_header *first_header);
void				join_header(t_header *prev, t_header *new_h, size_t size);
void				create_header(t_header *tmp, size_t size);
void				free2(void *ptr);
void				merge_header(t_header *first, t_header *second);
void				free_large(t_header *ptr);
void				*move_header(size_t add_size, t_header *header, int move_left);
void				*find_new_size_in_mem(t_header *header, size_t size);
void				*realloc2(void *ptr, size_t size);
int					ft_abs(int i);
int					mem_following(t_header *header);
void				ft_memcpy_reverse(void *dest, const void *src, size_t n);
void				show_alloc_mem_ex(void *ptr);
void				print_hexa(size_t size, void *ptr,  unsigned int i, unsigned int *j);
void				printf_char(size_t size, void *ptr, unsigned int i, unsigned int j);

#endif
