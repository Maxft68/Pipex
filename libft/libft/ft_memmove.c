/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:37:19 by mdsiurds          #+#    #+#             */
/*   Updated: 2024/10/25 18:13:25 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	j;
	char	*s;
	char	*d;

	d = (char *)dest;
	s = (char *)src;
	j = 0;
	if (!dest && !src)
		return (NULL);
	if (s > d)
	{
		while (j < n)
		{
			d[j] = s[j];
			j++;
		}
	}
	else
	{
		while (n--)
			d[n] = s[n];
	}
	return (dest);
}
