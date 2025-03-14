/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:55:04 by mdsiurds          #+#    #+#             */
/*   Updated: 2024/11/05 16:44:12 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		c2;
	const unsigned char	*s2;

	i = 0;
	c2 = c;
	s2 = s;
	while (i < n)
	{
		if (s2[i] == c2)
			return ((void *)(s2 + i));
		i++;
	}
	return (NULL);
}
