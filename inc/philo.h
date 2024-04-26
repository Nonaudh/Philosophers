#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t *philo_thread;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	pthread_mutex_t right_fork;
	pthread_mutex_t left_fork;
}	t_philo;

typedef struct s_data
{
	int number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	t_philo *philo;
}	t_data;

long	ft_atol(const char *nptr);
int	check(long nb);

#endif