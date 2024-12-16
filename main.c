/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:59:44 by srandria          #+#    #+#             */
/*   Updated: 2024/12/16 19:49:59 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_all_threads(t_philo_d *p_data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < p_data->nb_philos)
		pthread_join(philos[i].thread, NULL);
}

long 	get_time_in_ms(struct timeval start)
{
	(void)start;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo_d	philo_data;
	t_philo		philos[200];

	if (error_args(argc, argv) == -1)
		return (1);
	store_args(argc, argv, &philo_data);
	if (philo_data.nb_philos > 200)
	{
		err("Error: The number of philosophers cannot exceed 200.");
		exit (1);
	}
	create_forks(&philo_data);
	gettimeofday(&philo_data.start, NULL);
	create_phreads(&philo_data, philos);
	join_all_threads(&philo_data, philos);
	return (0);
}
