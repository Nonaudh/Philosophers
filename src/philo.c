#include "../inc/philo.h"

void	init_id(t_philo *p, int number)
{
	int	i = 0;

	while (i < number)
	{
		gettimeofday(&p[i].start, NULL);
		gettimeofday(&p[i].last_meal, NULL);
		p[i].is_eating = false;
		p[i].stop = false;
		p[i].id = i + 1;
		p[i].number = number;
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

void	init_speak(t_philo *p, int number)
{
	int	i = 0;
	pthread_mutex_t *speak1 = malloc(sizeof(pthread_mutex_t));
	while (i < number)
	{
		p[i].speak = speak1;
		i++;
	}
}

void	init_philo(t_philo *p, int number)
{
	init_id(p, number);
	init_forks(p, number);
	init_speak(p, number);
}