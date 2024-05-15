#include "../inc/philo_bonus.h"

void	eating(t_philo *p, sem_t *semaphore[2])
{
	if (sem_wait(semaphore[0]))
		ft_putendl_fd("Error sem_wait", 2);
	if (!p->stop)
		printf("%d %d has taken a fork\n", current_time(&p->start), p->philo_id);
	if (sem_wait(semaphore[1]))
		ft_putendl_fd("Error sem_wait", 2);
	gettimeofday(&p->last_meal, NULL);
	if (!p->stop)
		printf("%d %d is eating\n", current_time(&p->start), p->philo_id);
	ft_msleep(p->time_to_eat, &p->stop);
	if (sem_post(semaphore[1]))
		ft_putendl_fd("Error sem_post", 2);
	if (sem_post(semaphore[0]))
		ft_putendl_fd("Error sem_post", 2);
}

void	sleeping(t_philo *p)
{
	if (!p->stop)
		printf("%d %d is sleeping\n", current_time(&p->start), p->philo_id);
	ft_msleep(p->time_to_sleep, &p->stop);
}

void	thinking(t_philo *p)
{
	if (!p->stop)
		printf("%d %d is thinking\n", current_time(&p->start), p->philo_id);
}


void    routine_philo(t_philo *p, t_monitoring *m, sem_t *semaphore[2])
{
	int i = 0;
	pthread_t thread_id;

	m->philo = p;
	pthread_create(&thread_id, NULL, monitoring, m);
	pthread_detach(thread_id);
	while (!p->stop)
	{
		if (!p->stop)
			eating(p, semaphore);
		if (!p->stop)
			sleeping(p);
		if (!p->stop)
			thinking(p);
	}
}

int	number_of_semaphore_1(int number)
{
	if (number % 2 == 0)
		return (number / 2);
	return ((number + 1) / 2);
}

int	number_of_semaphore_2(int number)
{
	if (number % 2 == 0)
		return (number / 2);
	return ((number - 1) / 2);
}


void	kill_all_child_process(int *fork_pid, int number)
{
	int	i;

	i = 0;
	waitpid(0, NULL, 0);
	while (i < number)
	{
		kill(fork_pid[i], SIGKILL);
		i++;
	}
	//kill(0, SIGKILL);
}

int philosophers_bonus(t_philo *p, t_monitoring *m, int number)
{
	int *fork_pid = malloc(sizeof(int) * number);
	sem_t	*semaphore[2];
	int pid;

	int number_1 = number_of_semaphore_1(number);
	int number_2 = number_of_semaphore_2(number);

	semaphore[0] = sem_open("sem_1", O_CREAT | O_EXCL, 0644, number_1);
	semaphore[1] = sem_open("sem_2", O_CREAT | O_EXCL, 0644, number_2);
	if (sem_unlink("sem_1"))
		ft_putendl_fd("Error sem_unlink 1", 2);
	if (sem_unlink("sem_2"))
		ft_putendl_fd("Error sem_unlink 1", 2);
	fork_pid[p->philo_id - 1] = 1;
	t_bool ok = true;
	while (p->philo_id <= number && ok)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			routine_philo(p, m, semaphore);
			ok = false;
		}
		else
		{
			fork_pid[p->philo_id - 1] = pid;
			p->philo_id++;
		}
			
	}
	if (pid)
		kill_all_child_process(fork_pid, number);
	free(fork_pid);
	if (sem_close(semaphore[0]))
		ft_putendl_fd("Error sem_close 1", 2);
	if (sem_close(semaphore[1]))
		ft_putendl_fd("Error sem_close 2", 2);
	return (0);
}
