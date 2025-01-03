/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulai <ansoulai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:32:01 by ansoulai          #+#    #+#             */
/*   Updated: 2024/06/08 00:36:42 by ansoulai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
	}
	ft_putchar(n % 10 + '0');
}

static void	print_format(char specifier, va_list ap)
{
	if (specifier == 'd' || specifier == 'i')
		ft_putnbr(va_arg(ap, int));
	else
		ft_putchar(specifier);
}

void	ft_printf(char *format, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '\0')
				break ;
			print_format(format[++i], ap);
		}
		else
			ft_putchar(format[i]);
		i++;
	}
	va_end(ap);
}
