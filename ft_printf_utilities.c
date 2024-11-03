#include "ft_printf.h"
#include <stdarg.h>

void	*ft_ternary(int condition, void *true_value, void *fals_value)
{
	if (condition)
		return (true_value);
	return (fals_value);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

void	ft_putstr(char *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}

void	ft_pad(int n, char c)
{
	while (n-- > 0)
		ft_putchar(c);
}
