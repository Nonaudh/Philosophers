#include "../inc/philo.h"

int	check_if_greater_than(long nb, int minimum)
{
	if (nb > INT_MAX || nb < minimum)
		return (1);
	return (0);
}

int	check_if_values_exceeding(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (i != 5)
		{
 			if (check_if_greater_than(ft_atol(argv[i]), 1))
				break;	
		}
		else
		{
			if (check_if_greater_than(ft_atol(argv[i]), 0))
				break;
		}
		i++;
	}
	if (argv[i])
	{
		ft_putendl_fd("Error\nA value exceeds the limits", 2);
		return (1);
	}
	return (0);
}

int	check_if_only_digit(char **argv)
{
	int	i;
	int y;

	i = 1;
	while (argv[i])
	{
		y = 0;
		while (argv[i][y])
		{
			if (!is_digit(argv[i][y]))
			{
				ft_putendl_fd("Error\nOnly digits are allowed", 2);
				return (1);
			}	
			y++;
		}
		i++;
	}
	return (0);
}

int	check_values(char **argv)
{
	if (check_if_only_digit(argv))
		return (1);
	if (check_if_values_exceeding(argv))
		return (1);
	return(0);
}
