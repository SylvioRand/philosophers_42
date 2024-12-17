/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:08:46 by srandria          #+#    #+#             */
/*   Updated: 2024/12/17 19:44:46 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

int	deadlock_manager(t_philo *philo)
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

int	philosopher_odd_eat(t_philo *philo)
{
	t_philo_d		*p_data;

	p_data = get_philo_data_ptr();
	lock_left_fork(philo);
	if (print_state(philo, "has taken fork\n") == -1)
		return (-1);
	lock_right_fork(philo);
	if (print_state(philo, "has taken fork\n") == -1)
		return (-1);
	if (deadlock_manager(philo) == -1)
		return (-1);
	gettimeofday(&philo->last_time_meal, NULL);
	if (print_state(philo, "is_eating\n") == -1)
		return (-1);
	if (p_data->meals_to_stop != -1)
		philo->nb_meals++;
	while (get_time_in_ms(philo->last_time_meal) < p_data->time_to_eat
		&& p_data->dead_flag == 0)
		usleep(1);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	usleep(10);
	philo->right_hand = 0;
	philo->left_hand = 0;
	if (p_data->meals_to_stop != -1 && philo->nb_meals == p_data->meals_to_stop)
		return (-1);
	return (0);
}

int	philosopher_even_eat(t_philo *philo)
{
	t_philo_d		*p_data;

	p_data = get_philo_data_ptr();
	lock_right_fork(philo);
	if (print_state(philo, "has taken fork\n") == -1)
		return (-1);
	lock_left_fork(philo);
	if (print_state(philo, "has taken fork\n") == -1)
		return (-1);
	if (deadlock_manager(philo) == -1)
		return (-1);
	gettimeofday(&philo->last_time_meal, NULL);
	if (print_state(philo, "is_eating\n") == -1)
		return (-1);
	if (p_data->meals_to_stop != -1)
		philo->nb_meals++;
	while (get_time_in_ms(philo->last_time_meal) < p_data->time_to_eat
		&& p_data->dead_flag == 0)
		usleep(1);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	usleep(10);
	philo->right_hand = 0;
	philo->left_hand = 0;
	usleep(1);
	if (p_data->meals_to_stop != -1 && philo->nb_meals == p_data->meals_to_stop)
		return (-1);
	return (0);
}
