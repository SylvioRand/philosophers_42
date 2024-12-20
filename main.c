/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:59:44 by srandria          #+#    #+#             */
/*   Updated: 2024/12/20 09:50:24 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_all_threads(t_philo_d *p_data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < p_data->nb_philos)
		pthread_join(philos[i].thread, NULL);
	pthread_join(p_data->monitor_death, NULL);
}

long	get_time_in_ms(struct timeval start)
{
	struct timeval	current;
	long			seconds;
	long			microseconds;

	gettimeofday(&current, NULL);
	seconds = current.tv_sec - start.tv_sec;
	microseconds = current.tv_usec - start.tv_usec;
	return ((seconds * 1000) + (microseconds / 1000));
}

t_philo_d	*get_philo_data_ptr(void)
{
	static t_philo_d	philo_data;

	return (&philo_data);
}

int	main(int argc, char *argv[])
{
	t_philo_d	*philo_data;
	t_philo		philos[200];

	philo_data = get_philo_data_ptr();
	if (error_args(argc, argv) == -1)
		return (1);
	store_args(argc, argv, philo_data);
	if (philo_data->nb_philos > 200)
	{
		err("Error: The number of philosophers cannot exceed 200.");
		exit (1);
	}
	philo_data->dead_flag = 0;
	create_forks(philo_data);
	create_phreads(philo_data, philos);
	join_all_threads(philo_data, philos);
	return (0);
}
