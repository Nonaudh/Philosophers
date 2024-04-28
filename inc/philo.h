#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef enum	e_bool
{
	false,
	true
}	t_bool;

typedef struct s_philo
{
	pthread_t philo_thread;
	int	number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int last_meal;
	t_bool is_eating;
	t_bool	stop;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
}	t_philo;

typedef struct s_monitoring
{
	t_bool one_dead;
	int number_of_philo;
	t_philo *philo;
}	t_monitoring;

typedef struct s_data
{
	int number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	t_philo *philo;
	pthread_mutex_t *forks;
}	t_data;

long	ft_atol(const char *nptr);
int		check(long nb);

void	*routine(void *p);

#endif