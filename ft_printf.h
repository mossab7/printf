/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:19:20 by mbouhia           #+#    #+#             */
/*   Updated: 2024/11/03 20:19:22 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_flags
{
	int	width;
	int	precision;
	int	zero_pad;
	int	left_align;
	int	sign;
	int	space;
	int	hash;
	int	negative;
}		t_flags;

void	*ft_ternary(int condition, void *true_value, void *fals_value);
int		ft_strlen(const char *s);
int		ft_putchar(char c);
void	ft_putstr(char *s);
void	ft_putnbr(unsigned long n, unsigned int base, char *digits);
int		ft_numlen(unsigned long n, int base);
void	ft_pad(int n, char c);
int		handle_address(va_list args, t_flags flags);
int		handle_signed_number_specifier(long n, t_flags flags);
int		handle_string(char *s, t_flags flags);
void	set_flags(char flag, t_flags *flags);
void	*ft_memset(void *s, int c, size_t n);
int		handle_number_alignment(long n, int base, char *digits, t_flags flags);
int		handle_character(char c, t_flags flags);
int		handle_number(unsigned long n, int base, char *digits, t_flags flags);
int		handle_flags(const char **format, va_list args, t_flags flags);
int		handle_format(const char **format, va_list args);
int		ft_printf(const char *format, ...);
int		handle_error(const char **format);
int		num_pad_len(long n, int base, t_flags flags, int *pad);
t_flags	handle_conflict(t_flags flgs, const char **format);
#endif
