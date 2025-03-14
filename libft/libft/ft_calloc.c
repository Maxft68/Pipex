/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:00:10 by mdsiurds          #+#    #+#             */
/*   Updated: 2024/11/13 14:03:20 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*alloc;
	size_t	i;

	if ((nmemb == 0 || size == 0))
		return (malloc(0));
	if (size > __SIZE_MAX__ / nmemb)
		return (NULL);
	alloc = malloc(nmemb * size);
	i = 0;
	if (!alloc)
		return (NULL);
	while (i < size * nmemb)
	{
		alloc[i] = 0;
		i++;
	}
	return (alloc);
}
