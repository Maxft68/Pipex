/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:13:58 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/02/18 18:06:15 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] != (char)c)
			i--;
		else
			return ((char *)&s[i]);
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}
