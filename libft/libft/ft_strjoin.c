/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:50:01 by mdsiurds          #+#    #+#             */
/*   Updated: 2024/11/15 12:13:11 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*s1s2;

	if (!s1 || !s2)
		return (NULL);
	s1s2 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s1s2)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		s1s2[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s1s2[i++] = s2[j];
		j++;
	}
	s1s2[i] = '\0';
	return (s1s2);
}
