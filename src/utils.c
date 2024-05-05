#include "../inc/philo.h"

void	wait_for_all_threads(pthread_t *t, pthread_t m, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		pthread_join(t[i], NULL);
		i++;
	}
	pthread_join(m, NULL);
}
void	destroy_all_mutex(t_philo *p, int number)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(p->speak);
	free(p->speak);
	while (i < number)
	{
		pthread_mutex_destroy(&p[i].right_fork);
		i++;
	}
}

int	current_time(struct timeval *start)
{
	struct timeval end;
	gettimeofday(&end, NULL);
	return(time_diff(start, &end));
}

void	check_argv(char **argv)
{
	int	i;
	int y;

	i = 1;
	
	while (argv[i])
	{
		y = 0;
		while (argv[i][y])
		{
			if (!is_digit(argv[i][y]))
			{
				printf("Error\n");
				exit(EXIT_FAILURE);
			}
				
			y++;
		}
		i++;
	}
}

int	is_digit(char c)
{
	return(c >= '0' && c <= '9');
}

long	ft_atol(const char *nptr)
{
	int		i;
	long	x;
	long	y;

	i = 0;
	x = 1;
	y = 0;
	while (nptr[i] == ' ' || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			x = -x;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		y = (y * 10) + nptr[i] - '0';
		i++;
	}
	return (y * x);
}
