#include "../inc/philo.h"

void	init_id(t_philo *p, int number)
{
	int	i = 0;
	pthread_mutex_t	speak;

	pthread_mutex_init(&speak, NULL);
	while (i < number)
	{
		p[i].id = i + 1;
		p[i].number = number;
		p[i].speak = &speak;
		i++;
	}
}
void	init_forks(t_philo *p, int number)
{
	int	i = 0;

	while (i < number)
	{
		pthread_mutex_init(&p[i].right_fork, NULL);
		i++;
	}

	i = 0;
	while (i < number)
	{
		p[i].left_fork = &p[(i + 1) % number].right_fork;
		i++;
	}
}

void	init_philo(t_philo *p, int number)
{
	init_id(p, number);
	init_forks(p, number);
}