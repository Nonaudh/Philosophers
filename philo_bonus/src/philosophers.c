#include "../inc/philo_bonus.h"

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
	
void	close_semaphores(t_philo *p)
{
	if (sem_close(p->sem_t_right))
		ft_putendl_fd("Error sem_close 1", 2);
	if (sem_close(p->sem_t_left))
		ft_putendl_fd("Error sem_close 2", 2);
	if (sem_close(p->sem_t_data))
		ft_putendl_fd("Error sem_close 3", 2);
}

int philosophers_bonus(t_philo *p, t_monitoring *m, int number)
{
	int pid;
	int *fork_pid;
	
	pid = 1;
	fork_pid = malloc(sizeof(int) * number);
	if (!fork_pid)
		return (1);
	while (p->philo_id < number && pid)
	{
		p->philo_id++;
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			routine_philo(p, m);
		else
			fork_pid[p->philo_id - 1] = pid;
	}
	if (pid)
		kill_all_child_process(fork_pid, number);
	free(fork_pid);
	close_semaphores(p);
	return (0);
}
