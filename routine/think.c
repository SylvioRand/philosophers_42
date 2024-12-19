/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:20:03 by srandria          #+#    #+#             */
/*   Updated: 2024/12/19 11:43:23 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <unistd.h>

int	philosopher_think(t_philo *philo)
{
	t_philo_d		*p_data;

	p_data = get_philo_data_ptr();
	print_state(philo, "is thinking\n");
	usleep(10);
	pthread_mutex_lock(&p_data->mutex_dead_flag);
	if (p_data->dead_flag)
	{
		pthread_mutex_unlock(&p_data->mutex_dead_flag);
		return (-1);
	}
	pthread_mutex_unlock(&p_data->mutex_dead_flag);
	return (0);
}
