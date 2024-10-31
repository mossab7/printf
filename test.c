#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"


int main(int argc, char *argv[])
{
  int i = printf("\n[%4.s]\n",NULL);
  int j = ft_printf("\n[%4.s]\n",NULL);
  ft_printf("ft_: %d\nor_: %d",i,j);
  return 0;
}
