#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>
#define fmt (void *)(INT_MIN)
int	main(int argc, char *argv[])
{
	int	i;
	int	j;

	i = ft_printf("[%p]\n",fmt);
	j = printf("[%p]\n", fmt);
	printf("ft_: %d\nor_: %d", i, j);
	return (0);
}
