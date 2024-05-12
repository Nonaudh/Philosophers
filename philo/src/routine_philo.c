#include "../inc/philo.h"

void	right_first(t_philo *p)
{
	pthread_mutex_lock(&p->right_fork);
	pthread_mutex_lock(p->mutex_data);
	if (!p->stop)
		printf("%d %d has taken a fork\n", current_time(&p->start), p->philo_id);
	pthread_mutex_unlock(p->mutex_data);
	if (!p->left_fork)
	{
		wait_for_death(p);
		return ;
	}	
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(p->mutex_data);
	gettimeofday(&p->last_meal, NULL);
	p->is_eating = true;
	if (!p->stop)
		printf("%d %d is eating\n", current_time(&p->start), p->philo_id);
	pthread_mutex_unlock(p->mutex_data);
	ft_msleep(p->time_to_eat, &p->stop);
	pthread_mutex_lock(p->mutex_data);
	p->is_eating = false;
	p->number_of_meal++;
	pthread_mutex_unlock(p->mutex_data);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(&p->right_fork);
}
void	left_first(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(p->mutex_data);
	if (!p->stop)
		printf("%d %d has taken a fork\n", current_time(&p->start), p->philo_id);
	pthread_mutex_unlock(p->mutex_data);
	pthread_mutex_lock(&p->right_fork);
	pthread_mutex_lock(p->mutex_data);
	gettimeofday(&p->last_meal, NULL);
	p->is_eating = true;
	if (!p->stop)
		printf("%d %d is eating\n", current_time(&p->start), p->philo_id);
	pthread_mutex_unlock(p->mutex_data);
	ft_msleep(p->time_to_eat, &p->stop);
	pthread_mutex_lock(p->mutex_data);
	p->is_eating = false;
	p->number_of_meal++;
	pthread_mutex_unlock(p->mutex_data);
	pthread_mutex_unlock(&p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

void	eating(t_philo *p)
{
	if (!p->left_fork || p->philo_id % 2 == 0)
		right_first(p);
	else
		left_first(p);
}

void	sleeping(t_philo *p)
{
	pthread_mutex_lock(p->mutex_data);
	if (!p->stop)
		printf("%d %d is sleeping\n", current_time(&p->start), p->philo_id);
	pthread_mutex_unlock(p->mutex_data);
	ft_msleep(p->time_to_sleep, &p->stop);
}

void	thinking(t_philo *p)
{
 	pthread_mutex_lock(p->mutex_data);
	if (!p->stop)
		printf("%d %d is thinking\n", current_time(&p->start), p->philo_id);
	pthread_mutex_unlock(p->mutex_data);
}
