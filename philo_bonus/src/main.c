#include "../inc/philo_bonus.h"

void	wait_for_all_process(void)
{
	while (waitpid(-1, NULL, 0) > 0)
	;
}

int	main(int argc, char **argv)
{
	t_philo philo;
	t_monitoring monitoring;
	sem_t	*semaphore_1;
	sem_t	*semaphore_2;
	int	number;

	if (argc == 5)
	{
		if (check_values(argv))
			return (1);
		number = ft_atol(argv[1]);
		//number = 2;
		semaphore_1 = sem_open("sem_1", O_CREAT | O_EXCL, 0644, number / 2);
		semaphore_2 = sem_open("sem_2", O_CREAT | O_EXCL, 0644, number / 2);
		if (init_philo(&philo, &monitoring, argv, NULL))
			return (1);
		if (philosophers_bonus(&philo, &monitoring, number, semaphore_1, semaphore_2))
			return (1);
		wait_for_all_process();
	}
	else
		info();
	if (sem_unlink("sem_1"))
		ft_putendl_fd("Error sem_unlink 1", 2);
	else
		ft_putendl_fd("sem_unlink ok 1", 2);
	if (sem_close(semaphore_1))
		ft_putendl_fd("Error sem_close 1", 2);
	else
		ft_putendl_fd("sem_close ok 1", 2);

	if (sem_unlink("sem_2"))
		ft_putendl_fd("Error sem_unlink 2", 2);
	else
		ft_putendl_fd("sem_unlink ok 2", 2);
	if (sem_close(semaphore_2))
		ft_putendl_fd("Error sem_close 2", 2);
	else
		ft_putendl_fd("sem_close ok 2", 2);
	return (0);
}
