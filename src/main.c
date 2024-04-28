#include "../inc/philo.h"

void	init_data(t_data *d, char **argv)
{
	int	i;

	i = 0;
	d->number_of_philo = check(ft_atol(argv[1]));
	d->time_to_die = check(ft_atol(argv[2]));
	d->time_to_eat = check(ft_atol(argv[3]));
	d->time_to_sleep = check(ft_atol(argv[4]));
	d->philo = malloc(sizeof(t_philo) * d->number_of_philo);
	d->forks = malloc(sizeof(pthread_mutex_t) * d->number_of_philo);
	while (i < d->number_of_philo)
	{
		pthread_mutex_init(&d->forks[i], NULL);
		i++;
	}
}

void	init_monitoring(t_data *d, t_monitoring *m)
{
	m->one_dead = false;
	m->number_of_philo = d->number_of_philo;
	m->philo = d->philo;
}

void	copy_data(t_data *d, t_philo *p)
{
	p->time_to_die = d->time_to_die;
	p->time_to_eat = d->time_to_eat;
	p->time_to_sleep = d->time_to_sleep;
	p->is_eating = false;
	p->last_meal = 0;
	p->stop = false;
}


void	init_philo(t_data *d)
{
	int	i;
	t_monitoring monitoring;

	i = 0;
	init_monitoring(d, &monitoring);
	while (i < d->number_of_philo)
	{
		copy_data(d, &d->philo[i]);
		d->philo[i].number = i + 1;
		d->philo[i].left_fork = &d->forks[i];
		d->philo[i].right_fork = &d->forks[(i + 1) % d->number_of_philo];
		//pthread_create(&d->philo[i].philo_thread, NULL, routine, &d->philo[i]);
		//usleep(50);
		i++;
	}
	i = 0;
	while (i < d->number_of_philo)
	{
		pthread_create(&d->philo[i].philo_thread, NULL, routine, &d->philo[i]);
		usleep(50);
		i++;
	}
}

void	wait_for_thread(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->number_of_philo)
	{
		pthread_join(d->philo[i].philo_thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data data;

	init_data(&data, argv);
	init_philo(&data);
	wait_for_thread(&data);
	//philo(data);
	//clean_struct(data);
}