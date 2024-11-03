/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:11:45 by mbouhia           #+#    #+#             */
/*   Updated: 2024/11/03 20:13:18 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>

int	handle_precision_alignment(int total_len, size_t pad, t_flags flags)
{
	int	precision_len;

	if (!flags.left_align && flags.zero_pad && flags.precision == -1)
		ft_pad(flags.width - total_len, '0');
	else if (!flags.left_align && flags.zero_pad)
	{
		if (flags.width - flags.precision < total_len)
			ft_pad(flags.width - total_len - flags.precision, '0');
	}
	precision_len = flags.precision - total_len;
	if (precision_len > 0)
		ft_pad(precision_len, '0');
	ft_pad(pad, '0');
	if (precision_len > 0)
		return (total_len + precision_len);
	return (total_len);
}

int	handle_width_alignment(long n, int base, char *digits, t_flags flags)
{
	int	total_len;
	int	pad;

	total_len = num_pad_len(n, base, flags, &pad);
	if (!flags.left_align)
	{
		if (!flags.zero_pad || ((flags.width > flags.precision)
				&& flags.precision >= 0))
			ft_pad(flags.width - total_len, ' ');
	}
	if (flags.negative)
		ft_putchar('-');
	else if (flags.sign)
		ft_putchar('+');
	else if (flags.space)
		ft_putchar(' ');
	if (flags.hash && base == 16 && n != 0)
		ft_putstr((char *)ft_ternary(digits[10] == 'a', "0x", "0X"));
	return (handle_precision_alignment(total_len, pad, flags));
}

int	handle_number(unsigned long n, int base, char *digits, t_flags flags)
{
	int	total_len;

	total_len = handle_width_alignment(n, base, digits, flags);
	if (n != 0 || flags.precision == -1)
		ft_putnbr(n, base, digits);
	if (flags.left_align)
		ft_pad(flags.width - total_len, ' ');
	if (flags.precision == 0 && n == 0)
		return (flags.width);
	if (flags.width > total_len)
		return (flags.width);
	return (total_len);
}

int	handle_address(va_list args, t_flags flags)
{
	void			*ptr;
	unsigned long	n;
	int				total_len;

	ptr = va_arg(args, void *);
	if (!ptr)
		return (handle_string("(nil)", flags));
	n = (unsigned long)ptr;
	flags.hash = 1;
	total_len = handle_width_alignment(n, 16, "0123456789abcdef", flags);
	ft_putnbr(n, 16, "0123456789abcdef");
	if (flags.left_align)
		ft_pad(flags.width - total_len, ' ');
	if (flags.precision == 0 && n == 0)
		return (flags.width);
	if (flags.width > total_len)
		return (flags.width);
	fflush(stdout);
	return (total_len);
}

int	handle_signed_number_specifier(long n, t_flags flags)
{
	unsigned long	nb;

	if (n < 0)
	{
		flags.negative = 1;
		n = -n;
	}
	nb = n;
	return (handle_number(nb, 10, "0123456789", flags));
}
