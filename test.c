#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"


int main(int argc, char *argv[])
{
  int i = ft_printf("[%.5i]\n", 34);
  int j = printf("\n[%.5i]\n", 34);
  printf("ft_: %d\nor_: %d",i,j);
  return 0;
}
