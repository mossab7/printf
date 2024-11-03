#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"


int main(int argc, char *argv[])
{
  int i = ft_printf("[%08.6i]\n", 1);
  int j = printf("[%08.6i]\n", 1);
  printf("ft_: %d\nor_: %d",i,j);
  return 0;
}
