#include "ft_printf.h"

void ft_putnbr(long n, int base, char *digits) 
{
    if (n < 0) 
    {
        n = -n;
    }
    if (n >= base) 
        ft_putnbr(n / base, base, digits);
    ft_putchar(digits[n % base]);
}

int ft_numlen(long n, int base) 
{
    int len = 0;
    if (n == 0) return 1;
    while (n) 
    {
        n /= base;
        len++;
    }
    return (len);
}

int num_pad_len(long n, int base,t_flags flags,int *pad)
{
    int len;
    int sign;
    int prefix;
    int total_len;

    len = ft_numlen(n, base);
    sign = *(int *)ft_ternary((n < 0 || flags.sign || flags.space), &(int){1}, &(int){0});
    prefix = *(int *)ft_ternary((flags.hash && base == 16 && n != 0), &(int){2}, &(int){0});
    *pad = *(int *)ft_ternary((flags.precision > len), &(int){flags.precision - len}, &(int){0});
    total_len = len + sign + prefix + *pad;

    return total_len;
}

int handle_error(const char *format)
{
    const char *start;
    int precision;
    int count;

    precision = 0;
    count = 0;
    start = format;
    while(*format != '%')
    {
        if((*format == '0' && *(format - 1) == '.') || (*format == 's' && *(format - 1) == '%'))
              precision = 1; 
        format--;
    }
    if(!precision)
    { 
        count += ft_putchar(*format++);
        while(*format && format <= start)
            count += ft_putchar(*format++);
        format--;
    }
    return (count);
}

t_flags handle_conflict(t_flags flags,const char **format,va_list args)
{ 
    if (**format == '.')
    {
        (*format)++;
        if(**format == '*')
        {
            flags.precision = va_arg(args,int);
            (*format)++;
        }
        else 
        {
            flags.precision = 0;
            while (**format >= '0' && **format <= '9')
            {
                flags.precision = flags.precision * 10 + (**format - '0');
                (*format)++;
            }
        }
    }
    if(flags.left_align)
      flags.zero_pad = 0;
    if(flags.sign && flags.space)
      flags.space = 0;
    if(flags.width < 0)
    {
      flags.width = -flags.width;
      flags.left_align = 1;
    }
  return flags;
}
