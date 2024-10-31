#include "ft_printf.h"
#include <stdio.h>
int handle_string(char *s, t_flags flags) 
{
    if (!s) 
    {
       if(flags.precision == -1 || flags.precision >= 6)
        {
          handle_string("(null)",flags);
          return 6;
        }
        else if(flags.precision >= 0)
        {
            handle_string("",flags);
            return flags.precision;
        }
       return -1;
    } 
    int len = ft_strlen(s);
    if (flags.precision >= 0 && flags.precision < len) 
        len = flags.precision;
    if (!flags.left_align) 
        ft_pad(flags.width - len, ' ');
    write(1, s, len);
    if (flags.left_align) 
        ft_pad(flags.width - len, ' ');
    return *(int *)ft_ternary((flags.width > len), &flags.width, &len);
}

int handle_character(char c, t_flags flags) 
{
    if (!flags.left_align) 
        ft_pad(flags.width - 1, ' ');
    ft_putchar(c);
    if (flags.left_align) 
        ft_pad(flags.width - 1, ' ');
    return *(int *)ft_ternary((flags.width > 1), &flags.width, &(int){1});
}

int handle_number(long n, int base, char *digits, t_flags flags) 
{
    int total_len;
    int pad;
     
    total_len = num_pad_len(n,base,flags,&pad);
    if (!flags.left_align && !flags.zero_pad)
        ft_pad(flags.width - total_len, ' ');
    if (n < 0) 
        ft_putchar('-');
    else if (flags.sign) 
        ft_putchar('+');
    else if (flags.space) 
        ft_putchar(' ');
    if (flags.hash && base == 16 && n != 0)
    {
        if(digits[10] == 'a')
            ft_putstr("0x");
        else 
            ft_putstr("0X");
    }
    if (!flags.left_align && flags.zero_pad)
        ft_pad(flags.width - total_len, '0');
    ft_pad(pad, '0');
    ft_putnbr(n, base, digits);
    if (flags.left_align) 
        ft_pad(flags.width - total_len, ' ');
    return *(int *)ft_ternary((flags.width > total_len), &flags.width, &total_len);
}

int handle_flags(const char **format,va_list args,t_flags flags)
{
    if (**format == 's')
        return handle_string(va_arg(args, char *), flags);
    else if (**format == 'c')
        return handle_character(va_arg(args, int), flags);
    else if (**format == 'd' || **format == 'i')
        return handle_number(va_arg(args, int), 10, "0123456789", flags);
    else if (**format == 'u')
        return handle_number(va_arg(args, unsigned int), 10, "0123456789", flags);
    else if (**format == 'x')
        return handle_number(va_arg(args, unsigned int), 16, "0123456789abcdef", flags);
    else if (**format == 'X')
        return handle_number(va_arg(args, unsigned int), 16, "0123456789ABCDEF", flags);
    else if (**format == 'p') 
    {
        void *ptr;
        ptr = va_arg(args,void*);
        if(!ptr)
          return handle_string(("(nil)"),flags);
        flags.hash = 1;
        return handle_number(((unsigned long)ptr), 16, "0123456789abcdef", flags);
    }
    else 
        return handle_error(format);
    return 0;
}

int handle_format(const char **format, va_list args) 
{
    t_flags flags;
    
    memset(&flags,0,sizeof(flags));
    flags.precision = -1;
    while (**format == '-' || **format == '0' || **format == '+' || **format == ' ' || **format == '#')
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
    flags = handle_conflict(flags,format);
    return handle_flags(format,args,flags);
}

