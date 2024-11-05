/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:11:26 by mbouhia           #+#    #+#             */
/*   Updated: 2024/11/05 16:05:18 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

int	handle_string(char *s, t_flags flags)
{
	int	len;

	if (!s)
	{
		if (flags.precision == -1 || flags.precision >= 6)
		{
			handle_string("(null)", flags);
			return (6);
		}
		else if (flags.precision >= 0)
		{
			handle_string("", flags);
			return (flags.width);
		}
		return (-1);
	}
	len = ft_strlen(s);
	if (flags.precision >= 0 && flags.precision < len)
		len = flags.precision;
	if (!flags.left_align)
		ft_pad(flags.width - len, ' ');
	write(1, s, len);
	if (flags.left_align)
		ft_pad(flags.width - len, ' ');
	return (*(int *)ft_ternary((flags.width > len), &flags.width, &len));
}

int	handle_character(char c, t_flags flags)
{
	if (!flags.left_align)
		ft_pad(flags.width - 1, ' ');
	ft_putchar(c);
	if (flags.left_align)
		ft_pad(flags.width - 1, ' ');
	return (*(int *)ft_ternary((flags.width > 1), &flags.width, &(int){1}));
}

int	handle_flags(const char **format, va_list args, t_flags flags)
{
	if (**format == 's')
		return (handle_string(va_arg(args, char *), flags));
	else if (**format == 'c')
		return (handle_character(va_arg(args, int), flags));
	else if (**format == 'd' || **format == 'i')
		return (handle_signed_number_specifier(va_arg(args, int), flags));
	else if (**format == 'u')
		return (handle_number(va_arg(args, unsigned int), 10, "0123456789",
				flags));
	else if (**format == 'x')
		return (handle_number(va_arg(args, unsigned int), 16,
				"0123456789abcdef", flags));
	else if (**format == 'X')
		return (handle_number(va_arg(args, unsigned int), 16,
				"0123456789ABCDEF", flags));
	else if (**format == 'p')
		return (handle_address(args, flags));
	else
		return (handle_error(format));
	return (0);
}

int	handle_format(const char **format, va_list args)
{
	t_flags	flags;

	ft_memset(&flags, 0, sizeof(flags));
	flags.precision = -1;
	while (**format == '-' || **format == '0' || **format == '+'
		|| **format == ' ' || **format == '#')
	{
		set_flags(**format, &flags);
		(*format)++;
	}
	while (**format >= '0' && **format <= '9')
	{
		flags.width = flags.width * 10 + (**format - '0');
		(*format)++;
	}
	flags = handle_conflict(flags, format);
	return (handle_flags(format, args, flags));
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += handle_format(&format, args);
			if (*format == '\0')
				break ;
		}
		else
			count += ft_putchar(*format);
		format++;
	}
	va_end(args);
	return (count);
}
