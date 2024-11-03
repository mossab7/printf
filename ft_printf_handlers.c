#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>

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
		if (!flags.zero_pad || ((flags.width > flags.precision) && flags.precision >= 0))
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

int handle_address(va_list args,t_flags flags)
{
	void *ptr;
	unsigned long n;
	int  total_len;

	ptr = va_arg(args, void *);
	if(!ptr)
		return (handle_string("(nil)",flags));
	n = (unsigned long)ptr;
	flags.hash = 1;
	total_len = handle_width_alignment(n,16,"0123456789abcdef",flags);
	ft_putnbr(n, 16,"0123456789abcdef");
	if (flags.left_align)
		ft_pad(flags.width - total_len, ' ');
	if (flags.precision == 0 && n == 0)
		return (flags.width);
	if (flags.width > total_len)
		return (flags.width);
	return (total_len);
}

int handle_signed_number_specifier(long n,t_flags flags)
{
	unsigned long nb;

	if(n < 0)
	{
		flags.negative = 1;
		n = -n;
	}
	nb = n;
	return (handle_number(nb,10,"0123456789",flags));
}

int	handle_flags(const char **format, va_list args, t_flags flags)
{
	if (**format == 's')
		return (handle_string(va_arg(args, char *), flags));
	else if (**format == 'c')
		return (handle_character(va_arg(args, int), flags));
	else if (**format == 'd' || **format == 'i')
		return (handle_signed_number_specifier(va_arg(args, int),flags));
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
		return (handle_address(args,flags));
	else
		return (handle_error(format));
	return (0);
}

int	handle_format(const char **format, va_list args)
{
	t_flags	flags;

	memset(&flags, 0, sizeof(flags));
	flags.precision = -1;
	while (**format == '-' || **format == '0' || **format == '+'
		|| **format == ' ' || **format == '#')
	{
		if (**format == '-')
			flags.left_align = 1;
		else if (**format == '0')
			flags.zero_pad = 1;
		else if (**format == '+')
			flags.sign = 1;
		else if (**format == ' ')
			flags.space = 1;
		else if (**format == '#')
			flags.hash = 1;
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
