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

typedef struct s_stick
{
	pthread_mutex_t stick;
}	t_stick;

typedef struct s_philo
{
	int id;
	int	number;
	pthread_mutex_t right_fork;
	pthread_mutex_t *left_fork;
	t_stick *speak;
}	t_philo;

void	init_philo(t_philo *p, int number);

void	wait_for_all_threads(pthread_t *t, int number);
void	destroy_all_mutex(t_philo *p, int number);

#endif