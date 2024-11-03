#include "ft_printf.h"
#include <stdarg.h>

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	// int tmp;
	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			// tmp = count;
			count += handle_format(&format, args);
			// if(tmp > count)
			//     count++;
		}
		else
			count += ft_putchar(*format);
		format++;
	}
	va_end(args);
	return (count);
}
