#include "../inc/philo.h"

void	right_first(t_philo *p)
{
	pthread_mutex_lock(&p[0].right_fork);
	printf("%d %d lock_right\n", current_time(&p->start), p->id);
	pthread_mutex_lock(p[0].left_fork);
	//printf("%d lock_left\n", p->id);
	p->is_eating = true;
	printf("%d %d eat\n", current_time(&p->start), p->id);
	usleep(500000);
	gettimeofday(&p->last_meal, NULL);
	p->is_eating = false;
	pthread_mutex_unlock(p[0].left_fork);
	//printf("%d unlock_left\n", p->id);
	pthread_mutex_unlock(&p[0].right_fork);
	//printf("%d unlock_right\n", p->id);
}
void	left_first(t_philo *p)
{
	pthread_mutex_lock(p[0].left_fork);
	printf("%d %d lock_left\n", current_time(&p->start), p->id);
	pthread_mutex_lock(&p[0].right_fork);
	//printf("%d lock_right\n", p->id);
	p->is_eating = true;
	printf("%d %d eat\n", current_time(&p->start), p->id);
	usleep(500000);
	gettimeofday(&p->last_meal, NULL);
	p->is_eating = false;
	pthread_mutex_unlock(&p[0].right_fork);
	//printf("%d unlock_right\n", p->id);
	pthread_mutex_unlock(p[0].left_fork);
	//printf("%d unlock_left\n", p->id);
}


void	eating(t_philo *p)
{
	if (p[0].id % 2 == 0)
		right_first(p);
	else
		left_first(p);
}

void	sleeping(t_philo *p)
{
	pthread_mutex_lock(p[0].speak);
	printf("%d %d sleep\n", current_time(&p->start), p[0].id);
	pthread_mutex_unlock(p[0].speak);
	usleep(200000);
}

void	thinking(t_philo *p)
{
 	pthread_mutex_lock(p[0].speak);
	printf("%d %d think\n", current_time(&p->start), p[0].id);
	pthread_mutex_unlock(p[0].speak);
}

void	*routine(void *p)
{
	t_philo *tmp = (t_philo *)p;

	while (!tmp->stop)
	{
		eating(tmp);
		sleeping(tmp);
		thinking(tmp);
	}
	return (NULL);
}

void	philo(t_philo *p, pthread_t *t, int number)
{
	int	i = 0;

	while (i < number)
	{
		pthread_create(&t[i], NULL, routine, &p[i]);
		usleep(500);
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
	int	number = 10;
	pthread_t *t = malloc(sizeof(pthread_t) * number);
	t_philo *p = malloc(sizeof(t_philo) * number);
	pthread_t monitor;
	t_monitoring monitoring;

	init_philo(p, number);
	moni(p, &monitoring, &monitor, number);
	philo(p, t, number);
	wait_for_all_threads(t, monitor, number);
	destroy_all_mutex(p, number);
	free(t);
	free(p);
	//usleep(50000);
	//gettimeofday(&end, NULL);
	//printf("time; %d ms\n", time_diff(&start, &end));
	//gettimeofday(&start, NULL);
	//usleep(25000);
	//usleep(25000);
	//gettimeofday(&end, NULL);
	//printf("time; %d ms\n", time_diff(&start, &end));
	return (0);
}
