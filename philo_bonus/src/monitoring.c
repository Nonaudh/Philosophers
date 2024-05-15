#include "../inc/philo_bonus.h"

void    *monitoring(void *data)
{
	t_monitoring *m = data;

	while (current_time(&m->philo->last_meal) < m->time_to_die)
		usleep(5000);		
	printf("%d %d died\n", current_time(&m->philo->start), m->philo->philo_id);
	m->philo->stop = true;
	return (NULL);
}