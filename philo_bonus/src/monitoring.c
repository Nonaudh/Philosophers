#include "../inc/philo_bonus.h"

void    *monitoring(void *data)
{
	t_monitoring *m = data;

	sem_wait(m->sem_data);
	while (current_time(&m->philo->last_meal) < m->time_to_die)
	{
		sem_post(m->sem_data);
		usleep(5000);
		sem_wait(m->sem_data);
	}
	sem_post(m->sem_data);
	sem_wait(m->sem_data);
	m->philo->stop = true;		
	printf("%d %d died\n", current_time(&m->philo->start), m->philo->philo_id);
	sem_post(m->sem_data);
	return (NULL);
}