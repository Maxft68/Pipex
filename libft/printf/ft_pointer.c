/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:01:36 by mdsiurds          #+#    #+#             */
/*   Updated: 2024/11/30 11:19:57 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pointer(unsigned long long x)
{
	int			i;
	static int	in_or_out;
	char		*hex;

	if (x == 0)
		return (ft_putstr("(nil)"));
	i = 1;
	in_or_out = 0;
	hex = "0123456789abcdef";
	if (x >= 16)
		i += ft_pointer(x / 16);
	if (in_or_out == 0)
	{
		write(1, "0x", 2);
		i += 2;
	}
	in_or_out = 1;
	ft_putchar(hex[x % 16]);
	return (i);
}
