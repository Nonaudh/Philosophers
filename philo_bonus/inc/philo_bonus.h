/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:29:58 by ahuge             #+#    #+#             */
/*   Updated: 2024/05/20 12:35:49 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_philo
{
	sem_t			*sem_t_right;
	sem_t			*sem_t_left;
	sem_t			*sem_t_data;
	int				philo_id;
	int				time_to_eat;
	int				time_to_sleep;
	t_bool			stop;
	struct timeval	start;
	struct timeval	last_meal;
}	t_philo;

typedef struct s_monitoring
{
	sem_t	*sem_t_data;
	t_philo	*philo;
	int		time_to_die;
}	t_monitoring;

int		main(int argc, char **argv);

int		check_values(char **argv);
int		check_if_only_digit(char **argv);
int		check_if_values_exceeding(char **argv);
int		check_if_value_is_between(long nb, int min, int max);

int		init_philo(t_philo *p, t_monitoring *m, char **argv, int number);
int		init_semaforks(t_philo *p, int number);
int		init_struct_values(t_philo *p, t_monitoring *m, char **argv);
int		init_sem_data(t_philo *p, t_monitoring *m);

int		philosophers_bonus(t_philo *p, t_monitoring *m, int number);
void	close_semaphores(t_philo *p);
void	kill_all_child_process(int *fork_pid, int number);
void	*monitoring(void *data);
void	wait_for_death(t_philo *p);

int		routine_philo(t_philo *p, t_monitoring *m);
void	thinking(t_philo *p);
void	sleeping(t_philo *p);
void	eating(t_philo *p);

void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
int		ft_strlen(char *str);
long	ft_atol(const char *nptr);
int		is_digit(char c);

int		time_since(struct timeval *start);
int		ft_msleep(int milliseconds, t_bool *stop);
void	info(void);
int		number_of_semaphore_2(int number);
int		number_of_semaphore_1(int number);

#endif
