/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_forks_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:26:29 by srandria          #+#    #+#             */
/*   Updated: 2024/12/20 10:15:27 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_mutexes(t_philo_d *philo_data, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&(philo_data->mutexes[i]));
}

void	create_mutex_dead_flag(void)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	if (pthread_mutex_init(&p_data->mutex_dead_flag, NULL) != 0)
	{
		destroy_mutexes(p_data, p_data->nb_philos);
		pthread_mutex_destroy(&p_data->mutex_printf);
		exit (1);
	}
}

void	create_mutex_printf(void)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	if (pthread_mutex_init(&p_data->mutex_printf, NULL) != 0)
	{
		destroy_mutexes(p_data, p_data->nb_philos);
		exit (1);
	}
}

void	create_mutex_last_time_eat(void)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	if (pthread_mutex_init(&p_data->mutex_last_time_eat, NULL) != 0)
	{
		destroy_mutexes(p_data, p_data->nb_philos);
		pthread_mutex_destroy(&p_data->mutex_printf);
		pthread_mutex_destroy(&p_data->mutex_dead_flag);
		exit (1);
	}
}

void	create_mutex_data(void)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	if (pthread_mutex_init(&p_data->mutex_data, NULL) != 0)
	{
		destroy_mutexes(p_data, p_data->nb_philos);
		pthread_mutex_destroy(&p_data->mutex_printf);
		pthread_mutex_destroy(&p_data->mutex_dead_flag);
		pthread_mutex_destroy(&p_data->mutex_last_time_eat);
		exit (1);
	}
}
