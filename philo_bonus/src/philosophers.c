#include "../inc/philo_bonus.h"

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
}

int	init_semaforks(sem_t *sem_forks[2], int number)
{
	int number_1 = number_of_semaphore_1(number);
	int number_2 = number_of_semaphore_2(number);

	sem_forks[0] = sem_open("sem_1", O_CREAT | O_EXCL, 0644, number_1);
	sem_forks[1] = sem_open("sem_2", O_CREAT | O_EXCL, 0644, number_2);
	if (sem_unlink("sem_1"))
		return (1);
	if (sem_unlink("sem_2"))
		return (1);
	return (0);
}

void	close_semaforks(sem_t *sem_forks[2])
{
	if (sem_close(sem_forks[0]))
		ft_putendl_fd("Error sem_close 1", 2);
	if (sem_close(sem_forks[1]))
		ft_putendl_fd("Error sem_close 2", 2);
}

int philosophers_bonus(t_philo *p, t_monitoring *m, int number)
{
	int *fork_pid;
	sem_t	*sem_forks[2];
	int pid;

	pid = 1;
	fork_pid = malloc(sizeof(int) * number);
	if (!fork_pid)
		return (1);
	if (init_semaforks(sem_forks, number))
		return (1);
	while (p->philo_id < number && pid)
	{
		p->philo_id++;
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			routine_philo(p, m, sem_forks);
		else
			fork_pid[p->philo_id - 1] = pid;
	}
	if (pid)
		kill_all_child_process(fork_pid, number);
	free(fork_pid);
	close_semaforks(sem_forks);
	return (0);
}
