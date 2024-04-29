#include "../inc/philo.h"

void	eating(t_philo *p)
{
	pthread_mutex_lock(&p->right_fork);
	printf("%d right fork\n", p->number);
	pthread_mutex_lock(p->left_fork);
	printf("%d left fork\n", p->number);
	printf("%d eating\n", p->number);
	usleep(p->time_to_eat);
	pthread_mutex_unlock(&p->right_fork);
	printf("%d right drop\n", p->number);
	pthread_mutex_unlock(p->left_fork);
	printf("%d left drop\n", p->number);
}
void	sleeping(t_philo *p)
{
	printf("%d sleeping\n", p->number);
	usleep(p->time_to_sleep);
}
void	thinking(t_philo *p)
{
	printf("%d thinking\n", p->number);
}

void	*routine(void *p)
{
	//t_philo *tmp;

	//tmp = p;
	int i = 0;
	while (i < 3)//!p->stop)
	{
		//if (tmp->number == 1)
			eating(p);
		sleeping(p);
		thinking(p);
		i++;
	}
	return (NULL);
}