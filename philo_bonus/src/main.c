#include "../inc/philo_bonus.h"


int	main(int argc, char **argv)
{
	t_philo philo;
	t_monitoring monitoring;
	int	number;

	if (argc == 5 || argc == 6)
	{
		if (check_values(argv))
			return (1);
		number = ft_atol(argv[1]);
		if (init_philo(&philo, &monitoring, argv, number));
	
	}
	else
		info();
	return (0);
}
