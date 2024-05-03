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
	int id;
	int	number;
	t_bool stop;
	t_bool is_eating;
	struct timeval start;
	pthread_mutex_t right_fork;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *speak;
}	t_philo;

typedef struct s_monitoring
{
	t_philo *philo;
	struct timeval end;
}	t_monitoring;

void	init_philo(t_philo *p, int number);

void	wait_for_all_threads(pthread_t *t, int number);
void	destroy_all_mutex(t_philo *p, int number);

#endif