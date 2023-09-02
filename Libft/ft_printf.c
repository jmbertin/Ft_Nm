/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <jbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:27:16 by jbertin           #+#    #+#             */
/*   Updated: 2022/11/12 15:15:18 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	printnbr(int nb, int fd, int *len)
{
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		*len = *len + 11;
	}
	else if (nb < 0)
	{
		print_char('-', fd);
		*len = *len + 1;
		nb = -nb;
		printnbr(nb, fd, len);
	}
	else if (nb > 9)
	{
		printnbr(nb / 10, fd, len);
		printnbr(nb % 10, fd, len);
	}
	else
	{
		print_char(nb + 48, fd);
		*len = *len + 1;
	}
}

int	print_hex(unsigned long long adr, char *base)
{
	char	buff[25];
	int		i;
	int		size;

	i = 0;
	if (!adr)
	{
		write(1, "0", 1);
		return (1);
	}
	while (adr)
	{
		buff[i] = base[adr % 16];
		adr = adr / 16;
		i++;
	}
	size = i;
	while (i--)
		write(1, &buff[i], 1);
	return (size);
}

int	print_u(unsigned int adr, char *base)
{
	char	buff[25];
	int		i;
	int		size;

	i = 0;
	if (!adr)
	{
		write(1, "0", 1);
		return (1);
	}
	while (adr)
	{
		buff[i] = base[adr % 10];
		adr = adr / 10;
		i++;
	}
	size = i;
	while (i--)
		write(1, &buff[i], 1);
	return (size);
}

void	ft_exec_print(va_list list, char c, int *ptr_len)
{
	if (c == 'd' || c == 'i')
		printnbr((int)va_arg(list, int), 1, ptr_len);
	else if (c == 'c')
		*ptr_len += print_char((char)va_arg(list, int), 1);
	else if (c == 's')
		*ptr_len += print_str((char *)va_arg(list, char *), 1);
	else if (c == '%')
		*ptr_len += print_char('%', 1);
	else if (c == 'u')
		*ptr_len += print_u((unsigned long long)va_arg(list, int),
				"0123456789");
	else if (c == 'p')
	{
		*ptr_len += print_str("0x", 1);
		*ptr_len += print_hex((unsigned long long)va_arg(list, void *),
				"0123456789abcdef");
	}
	else if (c == 'x')
		*ptr_len += print_hex((unsigned int)va_arg(list, unsigned int),
				"0123456789abcdef");
	else if (c == 'X')
		*ptr_len += print_hex((unsigned int)va_arg(list, unsigned int),
				"0123456789ABCDEF");
}

int	ft_printf(const char *input, ...)
{
	va_list	listparam;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(listparam, input);
	while (input[i])
	{
		if (input[i] == '%')
		{
			ft_exec_print(listparam, input[i + 1], &len);
			i++;
		}
		else
			len += write(1, &input[i], 1);
		i++;
	}
	va_end(listparam);
	return (len);
}
