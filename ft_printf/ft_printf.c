/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:53:08 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/04/22 19:22:42 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

int	ft_putstr(char *str)
{
	int	i = 0;
	int	count = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		count += write(1, &str[i], 1);	
		i++;
	}
	return (count);
}

int	ft_putnbr(int nbr)
{
	int	count = 0;
	char	c;

	if (nbr == -2147483648)
	{
		count += ft_putstr("−2147483648");
		return (count);
	}
	if (nbr < 0)
	{	
		count += write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr > 9)
	{ 
		count += ft_putnbr(nbr / 10);			
	}
	c =  nbr % 10 + '0';
	count += write(1, &c, 1);
	return (count);
}

int	 ft_hex(unsigned int nbr)
{
	int	count = 0;
	char *base = "0123456789abcdef";

	if (nbr >= 16)
		count += ft_hex(nbr / 16);		
	count += write(1, &base[nbr % 16], 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int	count = 0;
	int	i = 0;
	va_list list;

	va_start(list,format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 's')
				count += ft_putstr(va_arg(list, char *));
			else if (format[i] == 'd')
				count += ft_putnbr(va_arg(list, int));
			else if (format[i] == 'x')
				count += ft_hex(va_arg(list, unsigned int));
			else 
				count += write(1, &format[i], 1);
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(list);
	return (count);
}

int	main(void)
{	
	int	saida_nbr = ft_printf("number %d\n", -42);
	int	saida_nbr_origin = printf("number %d\n", -42);
	printf ("%i\n", saida_nbr);
	printf ("%i\n", saida_nbr_origin);
	return (0);
}

