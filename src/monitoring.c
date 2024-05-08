#include "../inc/philo.h"

void	stop_all_philo(t_philo *p, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		pthread_mutex_lock(p->mutex_data);
		p[i].stop = true;
		pthread_mutex_unlock(p->mutex_data);
		i++;
	}
}

int	all_philo_are_alive(t_philo *p, int number, int time_to_die)
{
	int	i;

	i = 0;
	pthread_mutex_lock(p->mutex_data);
	while (i < number && (p[i].is_eating || current_time(&p[i].last_meal) < time_to_die))
	{
		pthread_mutex_unlock(p->mutex_data);
		i++;
		pthread_mutex_lock(p->mutex_data);
	}
	pthread_mutex_unlock(p->mutex_data);
	if (i == number)
		return (1);
	printf("%d %d died\n", current_time(&p[i].start), p[i].philo_id);
	return (0);
}

int	philo_still_need_to_eat(t_philo *p, int number, int must_eat_times)
{
	int	i;

	i = 0;
	pthread_mutex_lock(p->mutex_data);
	while (i < number && p[i].number_of_meal <= must_eat_times)
	{
		pthread_mutex_unlock(p->mutex_data);
		i++;
		pthread_mutex_lock(p->mutex_data);
	}
	pthread_mutex_unlock(p->mutex_data);
	if (i == number)
		return (1);
	return(0);
}

void    *check_for_dead(void *data)
{
	t_monitoring *m = (t_monitoring *)data;

	if (m->philo->must_eat_times != 0)
	{
		while (all_philo_are_alive(m->philo, m->number, m->time_to_die) 
			&& (m->philo->must_eat_times == -1 
			|| philo_still_need_to_eat(m->philo, m->number, m->philo->must_eat_times)))
		{
			usleep(5000);
		}
	}
	stop_all_philo(m->philo, m->number);
	return(NULL);
}
int	moni(t_philo *p, t_monitoring *m, int number)
{
	m->philo = p;
	m->number = number;
	if (pthread_create(&m->thread_id, NULL, check_for_dead, m))
		return (1);
	return (0);
}
