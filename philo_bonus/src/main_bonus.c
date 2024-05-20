/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:28:18 by ahuge             #+#    #+#             */
/*   Updated: 2024/05/20 12:28:19 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo			philo;
	t_monitoring	monitoring;
	int				number;

	if (argc == 5)
	{
		if (check_values(argv))
			return (0);
		number = ft_atol(argv[1]);
		if (init_philo(&philo, &monitoring, argv, number))
			return (1);
		if (philosophers_bonus(&philo, &monitoring, number))
			return (1);
	}
	else
		info();
	return (0);
}
