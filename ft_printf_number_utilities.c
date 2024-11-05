/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number_utilities.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:11:57 by mbouhia           #+#    #+#             */
/*   Updated: 2024/11/05 16:04:31 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(unsigned long n, unsigned int base, char *digits)
{
	if (n >= base)
		ft_putnbr(n / base, base, digits);
	ft_putchar(digits[n % base]);
}

int	ft_numlen(unsigned long n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}

int	num_pad_len(unsigned long n, int base, t_flags flags, int *pad)
{
	int	len;
	int	sign;
	int	prefix;
	int	total_len;

	len = ft_numlen(n, base);
	if (n == 0 && flags.precision >= 0)
		len = 0;
	sign = *(int *)ft_ternary((flags.negative || flags.sign || flags.space),
			&(int){1}, &(int){0});
	prefix = *(int *)ft_ternary((flags.hash && base == 16 && n != 0), &(int){2},
			&(int){0});
	*pad = *(int *)ft_ternary((flags.precision > len), &(int){flags.precision
			- len}, &(int){0});
	total_len = len + sign + prefix + *pad;
	return (total_len);
}

int	handle_error(const char **format)
{
	int	count;

	count = 0;
	count += ft_putchar('%');
	while (**format)
	{
		if (**format == '%')
			break ;
		count += ft_putchar(**format);
		(*format)++;
	}
	return (count);
}

t_flags	handle_conflict(t_flags flags, const char **format)
{
	if (**format == '.')
	{
		flags.precision = 0;
		(*format)++;
		while (**format >= '0' && **format <= '9')
		{
			flags.precision = flags.precision * 10 + (**format - '0');
			(*format)++;
		}
	}
	if (flags.left_align)
		flags.zero_pad = 0;
	if (flags.sign && flags.space)
		flags.space = 0;
	if (flags.width < 0)
	{
		flags.width = -flags.width;
		flags.left_align = 1;
	}
	return (flags);
}
