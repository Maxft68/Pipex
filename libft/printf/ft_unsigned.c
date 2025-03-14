/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:00:35 by mdsiurds          #+#    #+#             */
/*   Updated: 2024/11/28 09:27:59 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned(unsigned int n)
{
	int	j;

	j = 1;
	if (n > 9)
	{
		j += ft_unsigned(n / 10);
	}
	ft_putchar(n % 10 + '0');
	return (j);
}
