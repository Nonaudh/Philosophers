/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:28:12 by ahuge             #+#    #+#             */
/*   Updated: 2024/05/20 12:28:14 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	init_struct_values(t_philo *p, t_monitoring *m, char **argv)
{
	if (gettimeofday(&p->start, NULL))
		return (1);
	if (gettimeofday(&p->last_meal, NULL))
		return (1);
	p->philo_id = 0;
	m->time_to_die = ft_atol(argv[2]);
	p->time_to_eat = ft_atol(argv[3]);
	p->time_to_sleep = ft_atol(argv[4]);
	p->stop = false;
	m->philo = p;
	return (0);
}

int	init_semaforks(t_philo *p, int number)
{
	int	nb_of_right_forks;
	int	nb_of_left_forks;

	nb_of_right_forks = number_of_semaphore_1(number);
	nb_of_left_forks = number_of_semaphore_2(number);
	p->sem_t_right = sem_open("sem_right", O_CREAT, 0644, nb_of_right_forks);
	if (!p->sem_t_right)
		return (1);
	if (sem_unlink("sem_right"))
		return (1);
	if (number != 1)
	{
		p->sem_t_left = sem_open("sem_left", O_CREAT, 0644, nb_of_left_forks);
		if (!p->sem_t_left)
			return (1);
		if (sem_unlink("sem_left"))
			return (1);
	}
	else
		p->sem_t_left = NULL;
	return (0);
}

int	init_sem_data(t_philo *p, t_monitoring *m)
{
	p->sem_t_data = sem_open("sem_data", O_CREAT, 0644, 1);
	if (!p->sem_t_data)
		return (1);
	m->sem_t_data = p->sem_t_data;
	if (sem_unlink("sem_data"))
		return (1);
	return (0);
}

int	init_philo(t_philo *p, t_monitoring *m, char **argv, int number)
{
	if (init_struct_values(p, m, argv))
		return (1);
	if (init_semaforks(p, number))
		return (1);
	if (init_sem_data(p, m))
		return (1);
	return (0);
}
