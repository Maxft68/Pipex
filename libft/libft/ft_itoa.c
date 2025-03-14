/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:08:26 by mdsiurds          #+#    #+#             */
/*   Updated: 2024/11/25 18:37:47 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*special_n(int n)
{
	char	*s;

	s = "";
	if (n == -2147483648)
	{
		s = malloc(12 * sizeof(char));
		if (!s)
			return (NULL);
		ft_strlcpy(s, "-2147483648", 12);
		return (s);
	}
	s = malloc(2 * sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, "0", 2);
	return (s);
}

static int	count_char(int n)
{
	int	j;
	int	new;

	j = 0;
	new = n;
	while (new != 0)
	{
		new = new / 10;
		j++;
	}
	return (j);
}

static int	to_minus(int *n)
{
	*n *= -1;
	return (1);
}

char	*ft_itoa(int n)
{
	int		index[3];
	char	*s;

	index[2] = 0;
	if (n == -2147483648 || n == 0)
		return (special_n(n));
	index[0] = 0;
	if (n < 0)
		index[2] = to_minus(&n);
	index[0] = count_char(n);
	s = malloc((index[0] + 1 + index[2]) * sizeof(char));
	if (!s)
		return (NULL);
	index[1] = (index[0] + index[2]) - 1;
	while (index[1] >= 0 + index[2])
	{
		s[index[1]] = n % 10 + '0';
		n /= 10;
		index[1] -= 1;
	}
	if (index[2] == 1)
		s[0] = '-';
	s[index[0] + index[2]] = '\0';
	return (s);
}
