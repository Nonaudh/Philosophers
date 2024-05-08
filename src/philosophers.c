#include "../inc/philo.h"

void	wait_for_death(t_philo *p)
{
	pthread_mutex_lock(p->mutex_data);
	while (!p->stop)
	{
		pthread_mutex_unlock(p->mutex_data);
		usleep(500);
		pthread_mutex_lock(p->mutex_data);
	}
	pthread_mutex_unlock(p->mutex_data);
	pthread_mutex_unlock(&p->right_fork);
}

void	*routine(void *data)
{
	t_philo *p = (t_philo *)data;
	t_bool stop;

	pthread_mutex_lock(p->mutex_data);
	stop = p->stop;
	pthread_mutex_unlock(p->mutex_data);
	while (!stop)
	{
		eating(p);
		pthread_mutex_lock(p->mutex_data);
		stop = p->stop;
		pthread_mutex_unlock(p->mutex_data);
		if (!stop)
			sleeping(p);
		pthread_mutex_lock(p->mutex_data);
		stop = p->stop;
		pthread_mutex_unlock(p->mutex_data);
		if (!stop)
			thinking(p);
		pthread_mutex_lock(p->mutex_data);
		stop = p->stop;
		pthread_mutex_unlock(p->mutex_data);
	}
	return (NULL);
}

int	philosophers(t_philo *p, int number)
{
	int	i = 0;

	while (i < number)
	{
		if (pthread_create(&p[i].thread_id, NULL, routine, &p[i]))
			return (1);
		if (pthread_detach(p[i].thread_id))
			return (1);
		usleep(50);
		i++;
	}
	return (0);
}
