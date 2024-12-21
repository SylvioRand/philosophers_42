/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:03:55 by srandria          #+#    #+#             */
/*   Updated: 2024/12/21 13:12:10 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lock_left_fork(t_philo *philo)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&p_data->mutex_data);
	philo->left_hand = 1;
	pthread_mutex_unlock(&p_data->mutex_data);
}

void	lock_right_fork(t_philo *philo)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	if (p_data->nb_philos == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_lock(&p_data->mutex_data);
		philo->left_hand = 0;
		pthread_mutex_unlock(&p_data->mutex_data);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&p_data->mutex_data);
	philo->right_hand = 1;
	pthread_mutex_unlock(&p_data->mutex_data);
}

void	unlock_right_fork(t_philo *philo)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(&p_data->mutex_data);
	philo->right_hand = 0;
	pthread_mutex_unlock(&p_data->mutex_data);
	usleep(0);
}

void	unlock_left_fork(t_philo *philo)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(&p_data->mutex_data);
	philo->left_hand = 0;
	pthread_mutex_unlock(&p_data->mutex_data);
	usleep(0);
}
