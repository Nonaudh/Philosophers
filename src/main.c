#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_philo *philo;
	t_monitoring monitoring;
	int	number;

	if (argc == 5 || argc == 6)
	{
		if (check_values(argv))
			return (1);
		number = ft_atol(argv[1]);
		philo = malloc(sizeof(t_philo) * number);
		if (!philo)
			return (1);
		if (init_philo(philo, &monitoring, argv, number))
			return (1);
		if (philosophers(philo, number))
			return (1);
		if (moni(philo, &monitoring, number))
			return (1);
		int	i = 0;
		while (i < number)
		{
			pthread_join(philo->thread_id, NULL); //////
			i++;
		}
		pthread_join(monitoring.thread_id, NULL);
		destroy_all_mutex(philo, number);
		free(philo);
	}
	else
		info();
	return (0);
}
