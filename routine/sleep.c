/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:19:22 by srandria          #+#    #+#             */
/*   Updated: 2024/12/19 12:27:36 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philosopher_sleep(t_philo *philo)
{
	t_philo_d		*p_data;
	long			ms;

	p_data = get_philo_data_ptr();
	print_state(philo, "is sleeping\n");
	ms = get_time_in_ms(p_data->start);
	while ((get_time_in_ms(p_data->start)) < ((p_data->time_to_sleep) + ms))
	{
		pthread_mutex_lock(&p_data->mutex_dead_flag);
		if (p_data->dead_flag != 0)
		{
			pthread_mutex_unlock(&p_data->mutex_dead_flag);
			break ;
		}
		pthread_mutex_unlock(&p_data->mutex_dead_flag);
		usleep(1);
	}
	pthread_mutex_lock(&p_data->mutex_dead_flag);
	if (p_data->dead_flag == 1)
	{
		pthread_mutex_unlock(&p_data->mutex_dead_flag);
		return (-1);
	}
	pthread_mutex_unlock(&p_data->mutex_dead_flag);
	return (0);
}
