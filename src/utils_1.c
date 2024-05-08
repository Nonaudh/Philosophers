#include "../inc/philo.h"


int	is_digit(char c)
{
	return(c >= '0' && c <= '9');
}

long	ft_atol(const char *nptr)
{
	int		i;
	long	x;
	long	y;

	i = 0;
	x = 1;
	y = 0;
	while (nptr[i] == ' ' || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			x = -x;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		y = (y * 10) + nptr[i] - '0';
		i++;
	}
	return (y * x);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putendl_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}
