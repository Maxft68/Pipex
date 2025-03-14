/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:09:02 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/01 13:05:44 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	search_next_sign(char c, va_list lst)
{
	if (c == 'c')
		return (ft_putchar(va_arg(lst, int)));
	else if (c == '%')
		return (ft_putchar('%'));
	else if (c == 's')
		return (ft_putstr(va_arg(lst, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(lst, int)));
	else if (c == 'u')
		return (ft_unsigned(va_arg(lst, unsigned int)));
	else if (c == 'p')
		return (ft_pointer(va_arg(lst, unsigned long long)));
	else if (c == 'x')
		return (ft_hexa(va_arg(lst, unsigned int), 1));
	else if (c == 'X')
		return (ft_hexa(va_arg(lst, unsigned long long), 2));
	return (-1);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count_principal;
	int		val;
	va_list	lst;

	count_principal = 0;
	i = 0;
	va_start(lst, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			val = search_next_sign(str[i], lst);
			if (val == -1)
				return (-1);
			else
				count_principal += val;
		}
		else
			count_principal += ft_putchar(str[i]);
		i++;
	}
	va_end(lst);
	return (count_principal);
}

/* #include <stdio.h>

int main()
{
	printf("%d\n", printf("hello\n% "));
	ft_printf("%d\n", ft_printf("hello\n% "));
} */