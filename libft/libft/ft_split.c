/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:22:32 by mdsiurds          #+#    #+#             */
/*   Updated: 2024/11/15 12:18:07 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_count(char const *s, char c)
{
	int	i;
	int	nb;
	int	inorout;

	i = 0;
	nb = 0;
	inorout = 0;
	while (s[i])
	{
		if (s[i] != c && inorout == 0)
		{
			inorout = 1;
			nb++;
		}
		if (s[i] == c)
			inorout = 0;
		i++;
	}
	return (nb);
}

static char	*str_c_dup(char const *s, int start, int end)
{
	char	*alloc;

	alloc = malloc((end - start + 2) * sizeof(char));
	if (!alloc)
		return (NULL);
	ft_strlcpy(alloc, s + start, end - start + 2);
	return (alloc);
}

static void	ft_free_all(char **array, int a)
{
	while (a >= 0)
	{
		free(array[a]);
		a--;
	}
	free(array);
}

static char	**ft_inter_split(char **array, char const *s, char c)
{
	int	i;
	int	a;
	int	start;

	a = 0;
	i = 0;
	while (a < words_count(s, c))
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i] != 0)
			i++;
		array[a] = str_c_dup(s, start, i - 1);
		if (array[a] == NULL)
		{
			ft_free_all(array, a);
			return (NULL);
		}
		a++;
	}
	array[a] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = malloc((words_count(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	return (ft_inter_split(array, s, c));
}
