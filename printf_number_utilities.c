#include "libftprintf.h"
void ft_putnbr(long n, int base, char *digits) {
    if (n < 0) {
        ft_putchar('-');
        n = -n;
    }
    if (n >= base) ft_putnbr(n / base, base, digits);
    ft_putchar(digits[n % base]);
}

int ft_numlen(long n, int base) {
    int len = 0;
    if (n == 0) return 1;
    while (n) {
        n /= base;
        len++;
    }
    return len;
}

