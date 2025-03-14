/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:58:04 by mdsiurds          #+#    #+#             */
/*   Updated: 2024/11/28 09:31:12 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa(unsigned int x, int capital)
{
	int		i;
	char	*hex_low;
	char	*hex_upp;

	i = 1;
	hex_low = "0123456789abcdef";
	hex_upp = "0123456789ABCDEF";
	if (x >= 16)
		i += ft_hexa((x / 16), capital);
	if (capital == 1)
		ft_putchar(hex_low[x % 16]);
	else if (capital == 2)
		ft_putchar(hex_upp[x % 16]);
	return (i);
}
