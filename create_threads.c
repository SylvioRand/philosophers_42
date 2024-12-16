/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:07:56 by srandria          #+#    #+#             */
/*   Updated: 2024/12/16 10:20:01 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*odd_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	(void)philo;
	write (1, "\nodd", 5);
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

static void	create_odd_threads(t_philo_d *p_data)
{
	int	i;
	int	nb_philos;

	i = -1;
	nb_philos = p_data->nb_philos;
	while (++i < p_data->nb_philos)
	{
		if (i % 2 == 0)
		{
			p_data->philos[i].id = i;
			if (i == 0)
				p_data->philos[i].r_fork = &p_data->mutexes[nb_philos - 1];
			else
				p_data->philos[i].r_fork = &p_data->mutexes[i - 1];
			p_data->philos[i].l_fork = &p_data->mutexes[i];
			p_data->philos[i].nb_meals = 0;
			pthread_create(&p_data->philos[i].thread, NULL,
				&odd_routine, &p_data->philos[i]);
		}
	}
}

static void	create_even_threads(t_philo_d *p_data)
{
	int	i;

	i = -1;
	while (++i < p_data->nb_philos)
	{
		if (i % 2)
		{
			p_data->philos[i].id = i;
			p_data->philos[i].r_fork = &p_data->mutexes[i - 1];
			p_data->philos[i].l_fork = &p_data->mutexes[i];
			p_data->philos[i].nb_meals = 0;
			pthread_create(&p_data->philos[i].thread, NULL,
				&even_routine, &p_data->philos[i]);
		}
	}
}

void	create_phreads(t_philo_d *p_data)
{
	create_odd_threads(p_data);
	if ((p_data->nb_philos & 1) == 0)
	{
		usleep(100);
		write (1, "\npause", 6);
	}
	create_even_threads(p_data);
}
