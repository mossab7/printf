#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>
#define fmt INT_MIN
int	main(int argc, char *argv[])
{
	int	i;
	int	j;

	i = ft_printf("[%-11d]\n",fmt);
	j = printf("[%-11d]\n", fmt);
	printf("ft_: %d\nor_: %d", i, j);
	return (0);
}
