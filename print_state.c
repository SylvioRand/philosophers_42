/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:57:34 by srandria          #+#    #+#             */
/*   Updated: 2024/12/19 18:57:59 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	print_state(t_philo *philo, char *str)
{
	t_philo_d	*p_data;
	long		time_ms;

	p_data = get_philo_data_ptr();
	time_ms = get_time_in_ms(p_data->start);
	pthread_mutex_lock(&p_data->mutex_dead_flag);
	if (p_data->dead_flag == 0)
	{
		pthread_mutex_unlock(&p_data->mutex_dead_flag);
		pthread_mutex_lock(&p_data->mutex_printf);
		printf("%ld %d %s", time_ms, philo->id + 1, str);
		pthread_mutex_unlock(&p_data->mutex_printf);
	}
	else
	{
		pthread_mutex_unlock(&p_data->mutex_dead_flag);
		pthread_mutex_lock(&p_data->mutex_data);
		if (philo->right_hand)
			pthread_mutex_unlock(philo->r_fork);
		if (philo->left_hand)
			pthread_mutex_unlock(philo->l_fork);
		philo->left_hand = 0;
		philo->right_hand = 0;
		pthread_mutex_unlock(&p_data->mutex_data);
		return (-1);
	}
	return (0);
}
