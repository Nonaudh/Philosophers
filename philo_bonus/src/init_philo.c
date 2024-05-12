#include "../inc/philo_bonus.h"

int	init_time(t_philo *p, int number)
{
	if (gettimeofday(&p->start, NULL))
		return (1);
	if (gettimeofday(&p->last_meal, NULL))
		return (1);
	return (0);
}

void	init_struct_values(t_philo *p, t_monitoring *m, char **argv, int number)
{
	int	i = 0;

	m->time_to_die = ft_atol(argv[2]);
	p->time_to_eat = (ft_atol(argv[3]));
	p->time_to_sleep = (ft_atol(argv[4]));
	p->number_of_meal = 0;
	p->stop = false;
	if (argv[5])
		p->must_eat_times = (ft_atol(argv[5]));
	else
		p->must_eat_times = -1;
}

int	init_philo(t_philo *p, t_monitoring *m, char **argv, int number)
{
	if (init_time(p, number))
		return (1);
	init_struct_values(p, m, argv, number);

	return (0);
}