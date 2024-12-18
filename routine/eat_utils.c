/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:03:55 by srandria          #+#    #+#             */
/*   Updated: 2024/12/18 09:05:28 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lock_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	philo->left_hand = 1;
}

void	lock_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	philo->right_hand = 1;
}

void	unlock_right_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	philo->right_hand = 0;
	usleep(0);
}

void	unlock_left_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	philo->left_hand = 0;
	usleep(0);
}
