/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:07:56 by srandria          #+#    #+#             */
/*   Updated: 2024/12/16 19:49:56 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
#include <pthread.h>
#include <unistd.h>

void	print_state(t_philo_d *p_data, t_state state, int id)
{
	long	time_ms;

	time_ms = get_time_in_ms(p_data->start);

	if (state == THINKING)
	{
	}
	else if (state == EATING)
	{}
	else if (state == THINKING)
	{}
}

void	*odd_routine(void *ptr)
{
	t_philo	*philo;
	
	philo = (t_philo *)ptr;
	(void)philo;
	write (1, "\nodd", 5);
	while (1)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);

	}
	return (NULL);
}

void	*even_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	(void)philo;
	write (1, "\neven", 5);
	return (NULL);
}

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
			philos[i].nb_meals = 0;
			pthread_create(&philos[i].thread, NULL,
				&odd_routine, &philos[i]);
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
			philos[i].nb_meals = 0;
			pthread_create(&philos[i].thread, NULL,
				&even_routine, &philos[i]);
		}
	}
}

void	create_phreads(t_philo_d *p_data, t_philo *philos)
{
	create_odd_threads(p_data, philos);
	if ((p_data->nb_philos & 1) == 0)
		usleep(100);
	create_even_threads(p_data, philos);
}
