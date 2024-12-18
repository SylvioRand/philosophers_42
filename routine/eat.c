/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:08:46 by srandria          #+#    #+#             */
/*   Updated: 2024/12/18 09:06:41 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

static int	deadlock_manager(t_philo *philo)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	if (p_data->dead_flag)
	{
		if (philo->right_hand)
			pthread_mutex_unlock(philo->r_fork);
		if (philo->left_hand)
			pthread_mutex_unlock(philo->l_fork);
		philo->left_hand = 0;
		philo->right_hand = 0;
		return (-1);
	}
	return (0);
}

int	philosopher_odd_eat(t_philo *philo)
{
	t_philo_d		*p_data;

	p_data = get_philo_data_ptr();
	lock_left_fork(philo);
	if (print_state(philo, "has taken a fork\n") == -1)
		return (-1);
	lock_right_fork(philo);
	if (print_state(philo, "has taken a fork\n") == -1)
		return (-1);
	if (deadlock_manager(philo) == -1)
		return (-1);
	gettimeofday(&philo->last_time_meal, NULL);
	if (print_state(philo, "\033[32mis eating\n\033[0m") == -1)
		return (-1);
	if (p_data->meals_to_stop != -1)
		philo->nb_meals++;
	while (get_time_in_ms(philo->last_time_meal) < p_data->time_to_eat
		&& p_data->dead_flag == 0)
		usleep(0);
	unlock_left_fork(philo);
	unlock_right_fork(philo);
	if (p_data->meals_to_stop != -1 && philo->nb_meals == p_data->meals_to_stop)
		return (-1);
	return (0);
}

int	philosopher_even_eat(t_philo *philo)
{
	t_philo_d		*p_data;

	p_data = get_philo_data_ptr();
	lock_right_fork(philo);
	if (print_state(philo, "has taken a fork\n") == -1)
		return (-1);
	lock_left_fork(philo);
	if (print_state(philo, "has taken a fork\n") == -1)
		return (-1);
	if (deadlock_manager(philo) == -1)
		return (-1);
	gettimeofday(&philo->last_time_meal, NULL);
	if (print_state(philo, "\033[32mis eating\n\033[0m") == -1)
		return (-1);
	if (p_data->meals_to_stop != -1)
		philo->nb_meals++;
	while (get_time_in_ms(philo->last_time_meal) < p_data->time_to_eat
		&& p_data->dead_flag == 0)
		usleep(0);
	unlock_right_fork(philo);
	unlock_left_fork(philo);
	if (p_data->meals_to_stop != -1 && philo->nb_meals == p_data->meals_to_stop)
		return (-1);
	return (0);
}
