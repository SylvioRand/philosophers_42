/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:20:03 by srandria          #+#    #+#             */
/*   Updated: 2024/12/21 13:12:20 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	ft_sleep(long time)
{
	t_philo_d	*p_data;
	long		ms;

	p_data = get_philo_data_ptr();
	ms = get_time_in_ms(p_data->start);
	while ((get_time_in_ms(p_data->start)) < (time + ms))
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
}

int	philosopher_think(t_philo *philo)
{
	t_philo_d		*p_data;

	p_data = get_philo_data_ptr();
	print_state(philo, "is thinking\n");
	if ((p_data->nb_philos & 1) == 1)
	{
		if (p_data->time_to_eat > p_data->time_to_sleep)
			ft_sleep(p_data->time_to_eat);
		else
			ft_sleep(p_data->time_to_sleep);
	}
	else
		usleep(2);
	pthread_mutex_lock(&p_data->mutex_dead_flag);
	if (p_data->dead_flag)
	{
		pthread_mutex_unlock(&p_data->mutex_dead_flag);
		return (-1);
	}
	pthread_mutex_unlock(&p_data->mutex_dead_flag);
	return (0);
}
