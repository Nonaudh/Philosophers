#include "../inc/philo.h"

void    info(void)
{
	ft_putendl_fd("Error\nInvalid arguments", 2);
	ft_putendl_fd("./philo number_of_philosophers time_to_die time_to_eat time_to_sleep", 2);
	ft_putendl_fd("[number_of_times_each_philosopher_must_eat]", 2);
}

void	destroy_all_mutex(t_philo *p, int number)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(p->mutex_data))
		ft_putendl_fd("Error pthread_mutex_destroy", 2);
	free(p->mutex_data);
	while (i < number)
	{
		if (pthread_mutex_destroy(&p[i].right_fork))
			ft_putendl_fd("Error pthread_mutex_destroy", 2);
		i++;
	}
}

void	wait_for_all_threads(t_philo *p, t_monitoring *m, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		if (pthread_join(p[i].thread_id, NULL))
			ft_putendl_fd("Error pthread_join", 2);
		i++;
	}
	if (pthread_join(m->thread_id, NULL))
		ft_putendl_fd("Error pthread_join", 2);
}

int	ft_msleep(int milliseconds, t_bool *stop)
{
	struct timeval start;

	if (gettimeofday(&start, NULL))
		ft_putendl_fd("Error gettimeoftheday", 2);
	while (!(*stop) && current_time(&start) < milliseconds)
		usleep(500);
	return (0);
}

int	current_time(struct timeval *start)
{
	struct timeval end;
	if (gettimeofday(&end, NULL))
		ft_putendl_fd("Error gettimeoftheday", 2);
	return(1e3 * (end.tv_sec - start->tv_sec)
		+ 1e-3 * (end.tv_usec - start->tv_usec));
}
