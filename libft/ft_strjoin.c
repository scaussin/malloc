/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 17:18:00 by scaussin          #+#    #+#             */
/*   Updated: 2015/02/19 13:34:21 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		len1;
	int		len2;
	int		i;
	int		j;

	i = 0;
	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		str = (char *)malloc((sizeof(char) * (len1 + len2)) + 1);
		if (str == NULL)
			return (NULL);
		j = 0;
		while (j < len1)
			str[i++] = s1[j++];
		j = 0;
		while (j < len2)
			str[i++] = s2[j++];
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
