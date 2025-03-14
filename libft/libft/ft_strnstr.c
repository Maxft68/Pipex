/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:32:38 by mdsiurds          #+#    #+#             */
/*   Updated: 2024/11/15 12:25:40 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	if ((big == NULL || little == NULL) && len == 0)
		return (0);
	while (big[i] && len > i)
	{
		while (big[i] == little[j] && len > i)
		{
			j++;
			i++;
			if (little[j] == '\0')
				return ((char *)(big + i - j));
		}
		i -= j;
		j = 0;
		i++;
	}
	return (NULL);
}
