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
	int	time_to_eat;
	int	time_to_sleep;
	t_bool stop;
	t_bool is_eating;
	struct timeval start;
	struct timeval last_meal;
	pthread_mutex_t right_fork;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *speak;
}	t_philo;

typedef struct s_monitoring
{
	t_philo *philo;
	int number;
	int	time_to_die;
}	t_monitoring;

void	init_philo(t_philo *p, t_monitoring *m, char **argv, int number);
int 	time_diff(struct timeval *start, struct timeval *end);

void	wait_for_all_threads(pthread_t *t, pthread_t m, int number);
void	destroy_all_mutex(t_philo *p, int number);
int		current_time(struct timeval *start);
void	check_argv(char **argv);
int		is_digit(char c);
long	ft_atol(const char *nptr);

void    moni(t_philo *p, t_monitoring *m, pthread_t *monitor, int number);

#endif