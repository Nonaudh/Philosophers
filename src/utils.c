#include "../inc/philo.h"

void	wait_for_all_threads(pthread_t *t, pthread_t m, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		pthread_join(t[i], NULL);
		i++;
	}
	pthread_join(m, NULL);
}
void	destroy_all_mutex(t_philo *p, int number)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(p[0].speak);
	while (i < number)
	{
		pthread_mutex_destroy(&p[i].right_fork);
		i++;
	}
}

int	current_time(struct timeval *start)
{
	struct timeval end;
	gettimeofday(&end, NULL);
	return(time_diff(start, &end));
}
