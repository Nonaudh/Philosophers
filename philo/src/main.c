/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:29:10 by ahuge             #+#    #+#             */
/*   Updated: 2024/05/15 18:29:12 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_monitoring	monitoring;
	int				number;

	if (argc == 5 || argc == 6)
	{
		if (check_values(argv))
			return (1);
		number = ft_atol(argv[1]);
		philo = malloc(sizeof(t_philo) * number);
		if (!philo)
			return (1);
		if (init_philo(philo, &monitoring, argv, number))
			return (1);
		if (philosophers(philo, number))
			return (1);
		if (monitoring_philo(philo, &monitoring, number))
			return (1);
		wait_for_all_threads(philo, &monitoring, number);
		destroy_all_mutex(philo, number);
		free(philo);
	}
	else
		info();
	return (0);
}
