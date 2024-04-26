#include "../inc/philo.h"

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

int	check(long nb)
{
	if(nb > 2147483647)
		return (-1);
	if (nb < 0)
		return (-2);
	return (nb);
}