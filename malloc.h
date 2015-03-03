/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 11:59:08 by scaussin          #+#    #+#             */
/*   Updated: 2015/03/03 16:27:50 by scaussin         ###   ########.fr       */
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

typedef struct	s_header
{
	size_t			size;
	char			free;
	struct s_header	*next;
	struct s_header	*prev;
}				t_header;

typedef struct	s_first_header
{
	t_header	*tiny;
	t_header	*small;
	t_header	*large;
}				t_first_header;

t_first_header g_first_header = {0, NULL, NULL};

void		*malloc2(size_t size);
void		*get_tiny(size_t size);
void		gen_tiny(t_header **last);
void		print_header(t_header *header);

#endif
