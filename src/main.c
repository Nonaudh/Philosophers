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
		philosophers(philo, number);
		moni(philo, &monitoring, number);
		pthread_join(monitoring.thread_id, NULL);
		destroy_all_mutex(philo, number);
		free(philo);
	}
	else
		info();
	return (0);
}
