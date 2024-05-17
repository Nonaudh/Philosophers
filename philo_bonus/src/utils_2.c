#include "../inc/philo_bonus.h"

void    info(void)
{
	ft_putendl_fd("Error\nInvalid arguments", 2);
	ft_putstr_fd("./philo number_of_philosophers ", 2);
	ft_putendl_fd("time_to_die time_to_eat time_to_sleep", 2);
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
