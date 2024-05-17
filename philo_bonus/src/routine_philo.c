#include "../inc/philo_bonus.h"

void	eating(t_philo *p, sem_t *sem_forks[2])
{
	if (sem_wait(sem_forks[0]))
		ft_putendl_fd("Error sem_wait", 2);
	if (sem_wait(p->sem_data))
		ft_putendl_fd("Error sem_wait", 2);
	if (!p->stop)
		printf("%d %d has taken a fork\n", current_time(&p->start), p->philo_id);
	if (sem_post(p->sem_data))
		ft_putendl_fd("Error sem_post", 2);
	if (sem_wait(sem_forks[1]))
		ft_putendl_fd("Error sem_wait", 2);
	sem_wait(p->sem_data);
	if (!p->stop)
		printf("%d %d has taken a fork\n", current_time(&p->start), p->philo_id);
	gettimeofday(&p->last_meal, NULL);
	if (!p->stop)
		printf("%d %d is eating\n", current_time(&p->start), p->philo_id);
	sem_post(p->sem_data);
	ft_msleep(p->time_to_eat, &p->stop);
	if (sem_post(sem_forks[1]))
		ft_putendl_fd("Error sem_post", 2);
	if (sem_post(sem_forks[0]))
		ft_putendl_fd("Error sem_post", 2);
}

void	sleeping(t_philo *p)
{
	sem_wait(p->sem_data);
	if (!p->stop)
		printf("%d %d is sleeping\n", current_time(&p->start), p->philo_id);
	sem_post(p->sem_data);
	ft_msleep(p->time_to_sleep, &p->stop);
}

void	thinking(t_philo *p)
{
	sem_wait(p->sem_data);
	if (!p->stop)
		printf("%d %d is thinking\n", current_time(&p->start), p->philo_id);
	sem_post(p->sem_data);
}

void    init_sem_data_name(t_monitoring *m, int id)
{
    int i;

    i = 0;
    while (i < 4)
    {
        m->sem_name[i] = id + 48;
		i++;
    }
    m->sem_name[i] = 0;
}

int    routine_philo(t_philo *p, t_monitoring *m, sem_t *sem_forks[2])
{
	int i = 0;
	pthread_t thread_id;

	// while (i < 4)
	// {
	// 	m->sem_name[i] = p->philo_id + 48;
	// 	i++;
	// }
	// m->sem_name[i] = 0;
    init_sem_data_name(m, p->philo_id);
	m->sem_data = sem_open(m->sem_name, O_CREAT | O_EXCL, 0644, 1);
	if (sem_unlink(m->sem_name))
		ft_putendl_fd("Error sem_unlink 1", 2);
	p->sem_data = m->sem_data;
	m->philo = p;	
	pthread_create(&thread_id, NULL, monitoring, m);
	while (!p->stop)
	{
		if (!p->stop)
			eating(p, sem_forks);
		if (!p->stop)
			sleeping(p);
		if (!p->stop)
			thinking(p);
	}
	sem_close(m->sem_data);
	pthread_join(thread_id, NULL);
	return (0);
}
