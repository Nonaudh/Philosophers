/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:28:55 by ahuge             #+#    #+#             */
/*   Updated: 2024/05/20 12:28:57 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	number_of_semaphore_1(int number)
{
	if (number % 2 == 0)
		return (number / 2);
	return ((number + 1) / 2);
}

int	number_of_semaphore_2(int number)
{
	if (number % 2 == 0)
		return (number / 2);
	return ((number - 1) / 2);
}

void	info(void)
{
	ft_putendl_fd("Error\nInvalid arguments", 2);
	ft_putstr_fd("./philo number_of_philosophers ", 2);
	ft_putendl_fd("time_to_die time_to_eat time_to_sleep", 2);
}

int	ft_msleep(int milliseconds, t_bool *stop)
{
	struct timeval	start;

	if (gettimeofday(&start, NULL))
		ft_putendl_fd("Error gettimeoftheday", 2);
	while (!(*stop) && time_since(&start) < milliseconds)
		usleep(500);
	return (0);
}

int	time_since(struct timeval *start)
{
	struct timeval	end;

	if (!start)
		return (1);
	if (gettimeofday(&end, NULL))
		ft_putendl_fd("Error gettimeoftheday", 2);
	return (1e3 * (end.tv_sec - start->tv_sec)
		+ 1e-3 * (end.tv_usec - start->tv_usec));
}
