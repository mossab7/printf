#include "ft_printf.h"

int alligment()


int handle_unsigned_numbers(va_list args, t_flags flags)
{
    unsigned long nb;
    int total_len;

    nb = va_args(args,unsigned long);
    total_len = ft_numlen(nb,) + ((flags.hash && nb != 0) * 2);
    alligment(flags,RIGHT,total_len);

}

int handle_format(char **format, va_list args, t_flags flags)
{
    int         i;
    t_handlers  handlers
    
    handlers[]
    {
        {'i',handle_signed_number},
        {'d',handle_signed_number},
        {'u',handle_unsigned_number},
        {'x',handle_unsigned_number},
        {'X',handle_unsigned_number},
        {'p',handle_unsugned_number},
        {'s',handle_string},
        {'c',handle_character}
        {'\0',NULL}
    };

    i = 0;
    while(handlers[i].flag)
    {
        if(handlers[i].flag == **format)
        {
            handlers[i].handlers(resolve(args,flags),flags)
        }   
    }
}