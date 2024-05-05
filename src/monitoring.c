#include "../inc/philo.h"

void	set_all_philo_to_dead(t_philo *p, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		p[i].stop = true;
		i++;
	}
}

t_bool	all_philo_are_alive(t_philo *p, int number, int time_to_die)
{
	int	i;

	i = 0;
	while (i < number && (p[i].is_eating || current_time(&p[i].last_meal) < time_to_die))
	{
		i++;
	}
	if (i == number)
		return (true);
	printf("%d %d DIED !!\n", current_time(&p[i].last_meal), p[i].id);
	return (false);
}

t_bool	philo_still_need_to_eat(t_philo *p, int number, int must_eat_times)
{
	int	i;

	i = 0;
	while (i < number && p[i].number_of_meal <= must_eat_times)
	{
		i++;
	}
	if (i == number)
		return (true);
	return(false);
}

void    *check_for_dead(void *data)
{
	t_monitoring *m = (t_monitoring *)data;
	int	i;

	i = 0;
	while (all_philo_are_alive(m->philo, m->number, m->time_to_die) 
		&& (m->philo->must_eat_times == -1 
		|| philo_still_need_to_eat(m->philo, m->number, m->philo->must_eat_times)))
	{
		usleep(5000);
	}
	set_all_philo_to_dead(m->philo, m->number);
	return(NULL);
}
void    moni(t_philo *p, t_monitoring *m, pthread_t *monitor, int number)
{
	m->philo = p;
	m->number = number;
	pthread_create(monitor, NULL, check_for_dead, m);
}
