#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	i;
	int	j;

	i = ft_printf("[%08.i]\n", 1);
	j = printf("[%08.i]\n", 1);
	printf("ft_: %d\nor_: %d", i, j);
	return (0);
}
