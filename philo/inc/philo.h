/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:28:11 by ahuge             #+#    #+#             */
/*   Updated: 2024/05/15 18:28:26 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

# define INT_MAX 2147483647

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				philo_id;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	int				number_of_meal;
	t_bool			stop;
	struct timeval	start;
	struct timeval	last_meal;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*mutex_data;
}	t_philo;

typedef struct s_monitoring
{
	pthread_t	thread_id;
	t_philo		*philo;
	int			number;
	int			time_to_die;
}	t_monitoring;

int		main(int argc, char **argv);

int		check_values(char **argv);
int		check_if_only_digit(char **argv);
int		check_if_values_exceeding(char **argv);
int		check_if_value_is_between(long nb, int min, int max);

int		init_philo(t_philo *p, t_monitoring *m, char **argv, int number);
int		init_data_mutex(t_philo *p, int number);
int		init_forks(t_philo *p, int number);
void	init_struct_values(t_philo *p, t_monitoring *m, char **argv, int nb);
int		init_time(t_philo *p, int number);

int		philosophers(t_philo *p, int number);
void	*routine(void *data);
void	wait_for_death(t_philo *p);

void	thinking(t_philo *p);
void	sleeping(t_philo *p);
void	eating(t_philo *p);
void	left_first(t_philo *p);
void	right_first(t_philo *p);

int		monitoring_philo(t_philo *p, t_monitoring *m, int number);
void	*check_for_dead(void *data);
int		philo_still_need_to_eat(t_philo *p, int number);
int		all_philo_are_alive(t_philo *p, int number, int time_to_die);
void	stop_all_philo(t_philo *p, int number);

void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
int		ft_strlen(char *str);
long	ft_atol(const char *nptr);
int		is_digit(char c);

int		time_since(struct timeval *start);
void	destroy_all_mutex(t_philo *p, int number);
int		ft_msleep(int milliseconds, t_bool *stop, pthread_mutex_t *mutex);
void	wait_for_all_threads(t_philo *p, t_monitoring *m, int number);
void	info(void);

#endif
