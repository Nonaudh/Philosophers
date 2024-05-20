/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:28:41 by ahuge             #+#    #+#             */
/*   Updated: 2024/05/20 12:28:42 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	eating(t_philo *p)
{
	sem_wait(p->sem_t_right);
	sem_wait(p->sem_t_data);
	if (!p->stop)
		printf("%d %d has taken a fork\n", time_since(&p->start), p->philo_id);
	sem_post(p->sem_t_data);
	if (!p->sem_t_left)
	{
		wait_for_death(p);
		return ;
	}
	sem_wait(p->sem_t_left);
	sem_wait(p->sem_t_data);
	if (!p->stop)
		printf("%d %d has taken a fork\n", time_since(&p->start), p->philo_id);
	gettimeofday(&p->last_meal, NULL);
	if (!p->stop)
		printf("%d %d is eating\n", time_since(&p->start), p->philo_id);
	sem_post(p->sem_t_data);
	ft_msleep(p->time_to_eat, &p->stop);
	sem_post(p->sem_t_left);
	sem_post(p->sem_t_right);
}

void	sleeping(t_philo *p)
{
	sem_wait(p->sem_t_data);
	if (!p->stop)
		printf("%d %d is sleeping\n", time_since(&p->start), p->philo_id);
	sem_post(p->sem_t_data);
	ft_msleep(p->time_to_sleep, &p->stop);
}

void	thinking(t_philo *p)
{
	sem_wait(p->sem_t_data);
	if (!p->stop)
		printf("%d %d is thinking\n", time_since(&p->start), p->philo_id);
	sem_post(p->sem_t_data);
}

int	routine_philo(t_philo *p, t_monitoring *m)
{
	pthread_t	thread_id;

	pthread_create(&thread_id, NULL, monitoring, m);
	while (!p->stop)
	{
		if (!p->stop)
			eating(p);
		if (!p->stop)
			sleeping(p);
		if (!p->stop)
			thinking(p);
	}
	pthread_join(thread_id, NULL);
	return (0);
}
