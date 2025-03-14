/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:19:04 by mdsiurds          #+#    #+#             */
/*   Updated: 2024/11/28 19:07:16 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...)__attribute__((format(printf, 1, 2)));
int		ft_putchar(char c);
int		ft_putstr(char *str);
size_t	ft_strlen(const char *s);
int		ft_unsigned(unsigned int x);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_printf(const char *str, ...);
int		ft_putnbr(int n);
int		ft_pointer(unsigned long long x);
int		ft_hexa(unsigned int x, int capital);

#endif