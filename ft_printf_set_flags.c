/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_set_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:12:09 by mbouhia           #+#    #+#             */
/*   Updated: 2024/11/03 20:13:44 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = (unsigned char)c;
		n--;
		ptr++;
	}
	return (s);
}

void	set_flags(char flag, t_flags *flags)
{
	if (flag == '-')
		flags->left_align = 1;
	else if (flag == '0')
		flags->zero_pad = 1;
	else if (flag == '+')
		flags->sign = 1;
	else if (flag == ' ')
		flags->space = 1;
	else if (flag == '#')
		flags->hash = 1;
}
