/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:46:01 by mdsiurds          #+#    #+#             */
/*   Updated: 2024/11/15 12:17:13 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		j;
	const char	*s;
	char		*d;

	d = (char *)dest;
	s = (const char *)src;
	j = 0;
	while (j < n)
	{
		d[j] = s[j];
		j++;
	}
	return (dest);
}
