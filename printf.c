#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "libftprintf.h"
#include <string.h>
int ft_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int count = 0;
    int tmp = 0;
    int precision = 0;

    while (*format)
    {
        if (*format == '%') 
        {
            format++;
            tmp = count;
            count += handle_format(&format, args);
            if(tmp == count)
            {
                const char *start = format;
                while(*format != '%')
                {
                  if(*format == '0' && *(format - 1) == '.')
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
                format = start;
            }
        } 
        else 
            count += ft_putchar(*format);
        format++;
    }

    va_end(args);
    return count;
}

