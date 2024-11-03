#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
typedef struct
{
	int	width;
	int	precision;
	int	zero_pad;
	int	left_align;
	int	sign;
	int	space;
	int	hash;
}		t_flags;

void	*ft_ternary(int condition, void *true_value, void *fals_value);
int		ft_strlen(const char *s);
int		ft_putchar(char c);
void	ft_putstr(char *s);
void	ft_putnbr(long n, int base, char *digits);
int		ft_numlen(long n, int base);
void	ft_pad(int n, char c);
int		handle_string(char *s, t_flags flags);
int		handle_number_alignment(long n, int base, char *digits, t_flags flags);
int		handle_character(char c, t_flags flags);
int		handle_number(long n, int base, char *digits, t_flags flags);
int		handle_flags(const char **format, va_list args, t_flags flags);
int		handle_format(const char **format, va_list args);
int		ft_printf(const char *format, ...);
int		handle_error(const char **format);
int		num_pad_len(long n, int base, t_flags flags, int *pad);
t_flags	handle_conflict(t_flags flgs, const char **format);
#endif // !LIBFTPRINTF_H
