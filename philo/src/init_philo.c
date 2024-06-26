/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:29:03 by ahuge             #+#    #+#             */
/*   Updated: 2024/05/15 18:29:05 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_time(t_philo *p, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		if (gettimeofday(&p[i].start, NULL))
			return (1);
		if (gettimeofday(&p[i].last_meal, NULL))
			return (1);
		i++;
	}
	return (0);
}

void	init_struct_values(t_philo *p, t_monitoring *m, char **argv, int number)
{
	int	i;
	int	time_eating;
	int	time_sleeping;
	int	must_eat_times;

	i = 0;
	m->time_to_die = ft_atol(argv[2]);
	time_eating = (ft_atol(argv[3]));
	time_sleeping = (ft_atol(argv[4]));
	if (argv[5])
		must_eat_times = (ft_atol(argv[5]));
	else
		must_eat_times = -1;
	while (i < number)
	{
		p[i].time_to_eat = time_eating;
		p[i].time_to_sleep = time_sleeping;
		p[i].must_eat_times = must_eat_times;
		p[i].number_of_meal = 0;
		p[i].stop = false;
		p[i].philo_id = i + 1;
		i++;
	}
}

int	init_forks(t_philo *p, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		if (pthread_mutex_init(&p[i].right_fork, NULL))
			return (1);
		i++;
	}
	i = 0;
	while (i < number)
	{
		if (number > 1)
			p[i].left_fork = &p[(i + 1) % number].right_fork;
		else
			p[i].left_fork = NULL;
		i++;
	}
	return (0);
}

int	init_data_mutex(t_philo *p, int number)
{
	int				i;
	pthread_mutex_t	*mutex_data;

	i = 0;
	mutex_data = malloc(sizeof(pthread_mutex_t));
	if (!mutex_data)
		return (1);
	if (pthread_mutex_init(mutex_data, NULL))
		return (1);
	while (i < number)
	{
		p[i].mutex_data = mutex_data;
		i++;
	}
	return (0);
}

int	init_philo(t_philo *p, t_monitoring *m, char **argv, int number)
{
	if (init_time(p, number))
		return (1);
	init_struct_values(p, m, argv, number);
	if (init_forks(p, number))
		return (1);
	if (init_data_mutex(p, number))
		return (1);
	return (0);
}
