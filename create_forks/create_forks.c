/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:11:54 by srandria          #+#    #+#             */
/*   Updated: 2024/12/20 10:12:10 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	create_forks(t_philo_d *philo_data)
{
	int				i;
	pthread_mutex_t	*mutexes;

	i = -1;
	mutexes = philo_data->mutexes;
	while (++i < philo_data->nb_philos)
	{
		if (pthread_mutex_init(&mutexes[i], NULL) != 0)
		{
			destroy_mutexes(philo_data, i);
			exit (1);
		}
	}
	create_mutex_printf();
	create_mutex_dead_flag();
	create_mutex_last_time_eat();
	create_mutex_data();
}
