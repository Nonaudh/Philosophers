#include "../inc/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo philo;
	t_monitoring monitoring;
	int	number;

	if (argc == 5)
	{
		if (check_values(argv))
			return (1);
		number = ft_atol(argv[1]);
		if (init_philo(&philo, &monitoring, argv))
			return (1);
		if (philosophers_bonus(&philo, &monitoring, number))
			return (1);
	}
	else
		info();
	return (0);
}
