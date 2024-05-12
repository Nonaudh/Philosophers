#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <semaphore.h>

# define INT_MAX 2147483647

typedef enum	e_bool
{
	false,
	true
}	t_bool;

typedef struct s_philo
{
	pthread_t thread_id;
	int philo_id;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_times;
	int number_of_meal;
	t_bool stop;
	struct timeval start;
	struct timeval last_meal;
}	t_philo;

typedef struct s_monitoring
{
	pthread_t thread_id;
	t_philo *philo;
	int	time_to_die;
}	t_monitoring;


#endif
