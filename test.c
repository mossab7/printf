#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	i;
	int	j;

	i = ft_printf("[%p]\n",0);
	j = printf("[%p]\n", 0);
	printf("ft_: %d\nor_: %d", i, j);
	return (0);
}
