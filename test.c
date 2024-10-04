#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

void func(long n)
{
  printf("%lx",n);
}


int main(int argc, char *argv[])
{
  char *str = "hello world";
  int n = 42;
  ft_printf("\n%p\n",str);
  ft_printf("\n%p\n",(void *)-1);
  ft_printf("%2131w",n);
  //printf("\n%lx\n",ULONG_MAX);
  return 0;
}
