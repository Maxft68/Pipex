/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:44:59 by mdsiurds          #+#    #+#             */
/*   Updated: 2024/11/13 13:49:30 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	search_set(char c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
	{
		if (set[i] == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		i;
	int		f;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	f = ft_strlen(s1) - 1;
	while (search_set(s1[i], set) == 1)
		i++;
	while (search_set(s1[f], set) == 1)
		f--;
	s2 = ft_substr(s1, i, (f - i) + 1);
	return (s2);
}
