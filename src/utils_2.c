#include "../inc/philo.h"

void    info(void)
{
    ft_putendl_fd("Error\nInvalid argument", 2);
    ft_putendl_fd("./philo number_of_philosophers time_to_die time_to_eat time_to_sleep", 2);
    ft_putendl_fd("[number_of_times_each_philosopher_must_eat]", 2);
}

void	destroy_all_mutex(t_philo *p, int number)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(p->mutex_data);
	free(p->mutex_data);
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
	return(1e3 * (end.tv_sec - start->tv_sec)
		+ 1e-3 * (end.tv_usec - start->tv_usec));
}
