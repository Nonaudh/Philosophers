#include "../inc/philo.h"

void	init_id(t_philo *p, int number)
{
	int	i = 0;

	while (i < number)
	{
		p[i].id = i + 1;
		p[i].number = number;
		i++;
	}
}
void	init_forks(t_philo *p, int number)
{
	int	i = 0;
	t_stick stick;

	if (pthread_mutex_init(&stick.stick, NULL) != 0)
		printf("ERROR\n");
	while (i < number)
	{
		pthread_mutex_init(&p[i].right_fork, NULL);
		p[i].speak = &stick;
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