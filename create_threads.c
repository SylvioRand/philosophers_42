/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:07:56 by srandria          #+#    #+#             */
/*   Updated: 2024/12/19 11:11:43 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static void	create_odd_threads(t_philo_d *p_data, t_philo *philos)
{
	int	i;
	int	nb_philos;

	i = -1;
	nb_philos = p_data->nb_philos;
	while (++i < p_data->nb_philos)
	{
		if (i % 2 == 0)
		{
			philos[i].id = i;
			if (i == 0)
				philos[i].r_fork = &p_data->mutexes[nb_philos - 1];
			else
				philos[i].r_fork = &p_data->mutexes[i - 1];
			philos[i].l_fork = &p_data->mutexes[i];
			philos[i].left_hand = 0;
			philos[i].right_hand = 0;
			philos[i].nb_meals = 0;
			gettimeofday(&philos[i].last_time_meal, NULL);
			pthread_create(&philos[i].thread, NULL,
				&routine, &philos[i]);
		}
	}
}

static void	create_even_threads(t_philo_d *p_data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < p_data->nb_philos)
	{
		if (i % 2)
		{
			philos[i].id = i;
			philos[i].r_fork = &p_data->mutexes[i - 1];
			philos[i].l_fork = &p_data->mutexes[i];
			philos[i].left_hand = 0;
			philos[i].right_hand = 0;
			philos[i].nb_meals = 0;
			gettimeofday(&philos[i].last_time_meal, NULL);
			pthread_create(&philos[i].thread, NULL,
				&routine, &philos[i]);
		}
	}
}

static void	create_monitor_death(t_philo *philos)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	pthread_create(&p_data->monitor_death, NULL,
		&monitor_death, philos);
}

void	create_phreads(t_philo_d *p_data, t_philo *philos)
{
	gettimeofday(&p_data->start, NULL);
	create_odd_threads(p_data, philos);
	if ((p_data->nb_philos & 1) == 0)
		usleep(50);
	create_even_threads(p_data, philos);
	usleep(100);
	create_monitor_death(philos);
}
