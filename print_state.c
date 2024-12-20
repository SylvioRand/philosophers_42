/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:57:34 by srandria          #+#    #+#             */
/*   Updated: 2024/12/20 10:20:31 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	manage_data_race(t_philo *philo)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	pthread_mutex_lock(&p_data->mutex_data);
	if (philo->right_hand)
		pthread_mutex_unlock(philo->r_fork);
	if (philo->left_hand)
		pthread_mutex_unlock(philo->l_fork);
	philo->left_hand = 0;
	philo->right_hand = 0;
	pthread_mutex_unlock(&p_data->mutex_data);
}

int	print_state(t_philo *philo, char *str)
{
	t_philo_d	*p_data;
	long		time_ms;

	p_data = get_philo_data_ptr();
	time_ms = get_time_in_ms(p_data->start);
	pthread_mutex_lock(&p_data->mutex_printf);
	pthread_mutex_lock(&p_data->mutex_dead_flag);
	if (p_data->dead_flag == 0)
	{
		pthread_mutex_unlock(&p_data->mutex_dead_flag);
		printf("%ld %d %s", time_ms, philo->id + 1, str);
	}
	else
	{
		pthread_mutex_unlock(&p_data->mutex_dead_flag);
		manage_data_race(philo);
		pthread_mutex_unlock(&p_data->mutex_printf);
		return (-1);
	}
	pthread_mutex_unlock(&p_data->mutex_printf);
	return (0);
}
