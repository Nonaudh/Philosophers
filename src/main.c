#include "../inc/philo.h"

void	right_first(t_philo *p)
{
	pthread_mutex_lock(&p->right_fork);
	pthread_mutex_lock(p->access_data);
	if (!p->stop)
		printf("%d %d has taken a fork\n", current_time(&p->start), p->id);
	pthread_mutex_unlock(p->access_data);
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(p->access_data);
	p->is_eating = true;
	if (!p->stop)
		printf("%d %d is eating\n", current_time(&p->start), p->id);
	pthread_mutex_unlock(p->access_data);
	usleep(p->time_to_eat);
	pthread_mutex_lock(p->access_data);
	p->is_eating = false;
	p->number_of_meal++;
	gettimeofday(&p->last_meal, NULL);
	pthread_mutex_unlock(p->access_data);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(&p->right_fork);
}
void	left_first(t_philo *p)
{
	if (!p->left_fork)
	{
		pthread_mutex_lock(&p->right_fork);
		printf("OK\n");
	}
	else
		pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(p->access_data);
	if (!p->stop)
		printf("%d %d has taken a fork\n", current_time(&p->start), p->id);
	if (!p->left_fork)
	{
		printf("KO\n");
		return ;
	}
	pthread_mutex_unlock(p->access_data);
	pthread_mutex_lock(&p->right_fork);
	pthread_mutex_lock(p->access_data);
	p->is_eating = true;
	if (!p->stop)
		printf("%d %d is eating\n", current_time(&p->start), p->id);
	pthread_mutex_unlock(p->access_data);
	usleep(p->time_to_eat);
	pthread_mutex_lock(p->access_data);
	p->is_eating = false;
	p->number_of_meal++;
	gettimeofday(&p->last_meal, NULL);
	pthread_mutex_unlock(p->access_data);
	pthread_mutex_unlock(&p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}


void	eating(t_philo *p)
{
	if (p->id % 2 == 0)
		right_first(p);
	else
		left_first(p);
}

void	sleeping(t_philo *p)
{
	pthread_mutex_lock(p->access_data);
	if (!p->stop)
		printf("%d %d is sleeping\n", current_time(&p->start), p->id);
	pthread_mutex_unlock(p->access_data);
	usleep(p->time_to_sleep);
}

void	thinking(t_philo *p)
{
 	pthread_mutex_lock(p->access_data);
	if (!p->stop)
		printf("%d %d is thinking\n", current_time(&p->start), p->id);
	pthread_mutex_unlock(p->access_data);
}

void	*routine(void *p)
{
	t_philo *tmp = (t_philo *)p;
	t_bool stop;

	pthread_mutex_lock(tmp->access_data);
	stop = tmp->stop;
	pthread_mutex_unlock(tmp->access_data);
	while (!stop)
	{
		eating(tmp);
		pthread_mutex_lock(tmp->access_data);
		stop = tmp->stop;
		pthread_mutex_unlock(tmp->access_data);
		if (!stop)
			sleeping(tmp);
		pthread_mutex_lock(tmp->access_data);
		stop = tmp->stop;
		pthread_mutex_unlock(tmp->access_data);
		if (!stop)
			thinking(tmp);
		pthread_mutex_lock(tmp->access_data);
		stop = tmp->stop;
		pthread_mutex_unlock(tmp->access_data);
	}
	return (NULL);
}

void	philo(t_philo *p, pthread_t *t, int number)
{
	int	i = 0;

	while (i < number)
	{
		pthread_create(&t[i], NULL, routine, &p[i]);
		usleep(50);
		i++;
	}
}

int time_diff(struct timeval *start, struct timeval *end)
{
	return (1e3 * (end->tv_sec - start->tv_sec)
		+ 1e-3 * (end->tv_usec - start->tv_usec));
}

int	main(int argc, char **argv)
{
	int	number = atol(argv[1]);
	pthread_t *t;
	t_philo *p;
	pthread_t monitor;
	t_monitoring monitoring;

	if (argc == 5 || argc == 6)
	{
		check_argv(argv);
		p = malloc(sizeof(t_philo) * number);
		t = malloc(sizeof(pthread_t) * number);
		init_philo(p, &monitoring, argv, number);
		moni(p, &monitoring, &monitor, number);
		philo(p, t, number);
		wait_for_all_threads(t, monitor, number);
		destroy_all_mutex(p, number);
		free(t);
		free(p);
	}
	else
	{
		printf("Error\n\n./philo number_of_philosophers time_to_die time_to_eat time_to_sleep\n[number_of_times_each_philosopher_must_eat]\n");
	}
	return (0);
}
