/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:20:47 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/01 13:01:09 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*alloc;
	size_t	l;

	l = ft_strlen(s);
	alloc = malloc((l + 1) * sizeof(char));
	if (!alloc)
		return (NULL);
	ft_strlcpy(alloc, s, l + 1);
	return (alloc);
}
