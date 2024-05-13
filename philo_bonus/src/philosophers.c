#include "../inc/philo_bonus.h"

void	eating(t_philo *p, sem_t *semaphore_1, sem_t *semaphore_2)
{
	if (sem_wait(semaphore_1))
		ft_putendl_fd("Error sem_wait", 2);
	printf("%d took a fork\n", p->philo_id);
	usleep(5000000);
	if (sem_wait(semaphore_2))
		ft_putendl_fd("Error sem_wait", 2);
	printf("%d is eating\n", p->philo_id);
	ft_msleep(p->time_to_eat, &p->stop);
	if (sem_post(semaphore_2))
		ft_putendl_fd("Error sem_post", 2);
	if (sem_post(semaphore_1))
		ft_putendl_fd("Error sem_post", 2);
}

void	sleeping(t_philo *p)
{
	printf("%d is sleeping\n", p->philo_id);
	ft_msleep(p->time_to_sleep, &p->stop);
}

void	thinking(t_philo *p)
{
	printf("%d is thinking\n", p->philo_id);
}


void    routine_philo(t_philo *p, t_monitoring *m, sem_t *semaphore_1, sem_t *semaphore_2)
{
	int i = 0;
	while (i < 2)
	{
		eating(p, semaphore_1, semaphore_2);
		sleeping(p);
		thinking(p);
		i++;
	}
}

int philosophers_bonus(t_philo *p, t_monitoring *m, int number, sem_t *semaphore_1, sem_t *semaphore_2)
{
	int fork_pid;

	fork_pid = 1;
	while (p->philo_id <= number && fork_pid)
	{
		fork_pid = fork();
		if (fork_pid == -1)
			return (1);
		if (fork_pid == 0)
			routine_philo(p, m, semaphore_1, semaphore_2);
		else
		{
			usleep(50);
			p->philo_id++;
		}
	}
	return (0);
}
