/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:26:29 by srandria          #+#    #+#             */
/*   Updated: 2024/12/16 10:21:40 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

static void	destroy_mutexes(t_philo_d *philo_data, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&(philo_data->mutexes[i]));
}

void	create_forks(t_philo_d *philo_data)
{
	int				i;
	pthread_mutex_t	*mutexes;

	i = -1;
	mutexes = philo_data->mutexes;
	while (++i < philo_data->nb_philos)
	{
		if (pthread_mutex_init(&mutexes[i], NULL) != 0 || i == 100)
		{
			destroy_mutexes(philo_data, i);
			exit (1);
		}
	}
}