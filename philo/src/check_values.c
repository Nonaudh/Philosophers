/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:28:53 by ahuge             #+#    #+#             */
/*   Updated: 2024/05/15 18:28:55 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_if_value_is_between(long nb, int min, int max)
{
	if (nb > max || nb < min)
		return (1);
	return (0);
}

int	check_if_values_exceeding(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (i == 1 && check_if_value_is_between(ft_atol(argv[i]), 1, 10000))
			break ;
		else if (i < 5 && check_if_value_is_between(ft_atol(argv[i]), 1, INT_MAX))
			break ;
		else if (check_if_value_is_between(ft_atol(argv[i]), 0, INT_MAX))
			break ;
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
	int	y;

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
	return (0);
}
