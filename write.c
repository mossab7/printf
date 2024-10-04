#include "ft_printf.h"
#include <unistd.h>
#include <stdio.h>
void function(long nbr)
{
  printf("%x",18446744073709551615);
}

int main(int argc, char *argv[])
{
  printf("[%*.s]\n",10,"43342");
  ft_printf("[%*.s]\n",10,"43342");
  
}
