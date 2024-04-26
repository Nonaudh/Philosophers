#include "../inc/philo.h"

void	init_data(t_data *d, char **argv)
{
	d->number_of_philo = check(ft_atol(argv[1]));
	d->philo = malloc(sizeof(t_philo) * (d->number_of_philo + 1));
	d->time_to_die = check(ft_atol(argv[2]));
	d->time_to_eat = check(ft_atol(argv[3]));
	d->time_to_sleep = check(ft_atol(argv[4]));
}
void	init_philo(t_data *d)
{
	
}

int	main(int argc, char **argv)
{
	t_data data;

	init_data(&data, argv);
	init_philo(&data);
	//philo(data);
	//clean_struct(data);
}