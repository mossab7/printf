#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>

#define fmt "[%%kk%%ll%%%d]\n"
#define value 12

int main() 
{
	int i = ft_printf(fmt,value);
	int j = printf(fmt,value);
	ft_printf("%d\n%d",i,j);
	//ft_printf("ft_: %d\n or_: %d",j,i);
	//fflush(stdout);
    	return 0;
}

