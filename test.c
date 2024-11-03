#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	i;
	int	j;

	i = ft_printf("[%p]\n",(void *)(INT_MIN));
	j = printf("[%p]\n", (void *)(INT_MIN));
	printf("ft_: %d\nor_: %d", i, j);
	return (0);
}
