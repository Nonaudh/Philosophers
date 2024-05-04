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

void    *check_for_dead(void *data)
{
	t_bool	one_dead;
	t_monitoring *m = (t_monitoring *)data;
	int	i;

	one_dead = false;
	i = 0;
	while (!one_dead)
	{
		while (!one_dead && i < m->number)
		{
			if (!m->philo[i].is_eating && current_time(&m->philo[i].last_meal) > m->time_to_die)
			{
				printf("%d %d died\n", current_time(&m->philo[i].start), m->philo[i].id);
				set_all_philo_to_dead(m->philo, m->number);
				one_dead = true;
			}
			i++;
		}
		usleep(5000);
		i = 0;
	}
	return (NULL);
}
void    moni(t_philo *p, t_monitoring *m, pthread_t *monitor, int number)
{
	m->philo = p;
	m->number = number;
	pthread_create(monitor, NULL, check_for_dead, m);
}
