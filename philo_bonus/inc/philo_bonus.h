#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define INT_MAX 2147483647

typedef enum	e_bool
{
	false,
	true
}	t_bool;

typedef struct s_philo
{
	sem_t	*sem_data;
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
	char	sem_name[5];
	sem_t	*sem_data;
}	t_monitoring;

int	main(int argc, char **argv);

int	check_values(char **argv);
int	check_if_only_digit(char **argv);
int	check_if_values_exceeding(char **argv);
int	check_if_value_is_between(long nb, int min, int max);

int	init_philo(t_philo *p, t_monitoring *m, char **argv);
void	init_struct_values(t_philo *p, t_monitoring *m, char **argv);
int	init_time(t_philo *p);

int philosophers_bonus(t_philo *p, t_monitoring *m, int number);
void    *monitoring(void *data);

int    routine_philo(t_philo *p, t_monitoring *m, sem_t *sem_forks[2]);

void	ft_putendl_fd(char *str, int fd);
int	ft_strlen(char *str);
long	ft_atol(const char *nptr);
int	is_digit(char c);

int	current_time(struct timeval *start);
int	ft_msleep(int milliseconds, t_bool *stop);
void    info(void);


#endif
