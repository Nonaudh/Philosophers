/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:39:52 by ahuge             #+#    #+#             */
/*   Updated: 2024/05/20 12:39:54 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	*monitoring(void *data)
{
	t_monitoring	*m;

	m = data;
	sem_wait(m->sem_t_data);
	while (time_since(&m->philo->last_meal) < m->time_to_die)
	{
		sem_post(m->sem_t_data);
		usleep(5000);
		sem_wait(m->sem_t_data);
	}
	m->philo->stop = true;
	printf("%d %d died\n", time_since(&m->philo->start), m->philo->philo_id);
	sem_post(m->sem_t_data);
	return (NULL);
}
