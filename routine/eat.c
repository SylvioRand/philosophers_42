/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:08:46 by srandria          #+#    #+#             */
/*   Updated: 2024/12/19 11:35:58 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

static int	deadlock_manager(t_philo *philo)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	pthread_mutex_lock(&p_data->mutex_dead_flag);
	if (p_data->dead_flag)
	{
		pthread_mutex_unlock(&p_data->mutex_dead_flag);
		if (philo->right_hand)
			pthread_mutex_unlock(philo->r_fork);
		if (philo->left_hand)
			pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_lock(&p_data->mutex_data);
		philo->left_hand = 0;
		philo->right_hand = 0;
		pthread_mutex_unlock(&p_data->mutex_data);
		pthread_mutex_unlock(&p_data->mutex_dead_flag);
		return (-1);
	}
	pthread_mutex_unlock(&p_data->mutex_dead_flag);
	return (0);
}

void	manage_eating_time(t_philo *philo)
{
	t_philo_d		*p_data;
	struct timeval	last_time_meal;

	p_data = get_philo_data_ptr();
	pthread_mutex_lock(&p_data->mutex_last_time_eat);
	last_time_meal = philo->last_time_meal;
	pthread_mutex_unlock(&p_data->mutex_last_time_eat);
	while (get_time_in_ms(last_time_meal) < p_data->time_to_eat)
	{
		pthread_mutex_lock(&p_data->mutex_dead_flag);
		if (p_data->dead_flag != 0)
		{
			pthread_mutex_unlock(&p_data->mutex_dead_flag);
			return ;
		}
		pthread_mutex_unlock(&p_data->mutex_dead_flag);
		usleep(0);
	}

}

int	philosopher_odd_eat(t_philo *philo)
{
	t_philo_d		*p_data;

	p_data = get_philo_data_ptr();
	lock_left_fork(philo);
	if (print_state(philo, "has taken a fork\n") == -1)
		return (-1);
	lock_right_fork(philo);
	if (p_data->nb_philos == 1)
		return (-1);
	if (print_state(philo, "has taken a fork\n") == -1)
		return (-1);
	if (deadlock_manager(philo) == -1)
		return (-1);
	if (print_state(philo, "\033[32mis eating\n\033[0m") == -1)
		return (-1);
	pthread_mutex_lock(&p_data->mutex_last_time_eat);
	gettimeofday(&philo->last_time_meal, NULL);
	pthread_mutex_unlock(&p_data->mutex_last_time_eat);
	pthread_mutex_lock(&p_data->mutex_data);
	if (p_data->meals_to_stop != -1)
		philo->nb_meals++;
	pthread_mutex_unlock(&p_data->mutex_data);
	manage_eating_time(philo);
	unlock_left_fork(philo);
	unlock_right_fork(philo);
	pthread_mutex_lock(&p_data->mutex_data);
	if (p_data->meals_to_stop != -1 && philo->nb_meals == p_data->meals_to_stop)
	{
		pthread_mutex_unlock(&p_data->mutex_data);
		return (-1);
	}
	pthread_mutex_unlock(&p_data->mutex_data);
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
	if (print_state(philo, "\033[32mis eating\n\033[0m") == -1)
		return (-1);
	pthread_mutex_lock(&p_data->mutex_last_time_eat);
	gettimeofday(&philo->last_time_meal, NULL);
	pthread_mutex_unlock(&p_data->mutex_last_time_eat);
	pthread_mutex_lock(&p_data->mutex_data);
	if (p_data->meals_to_stop != -1)
		philo->nb_meals++;
	pthread_mutex_unlock(&p_data->mutex_data);
	manage_eating_time(philo);
	unlock_right_fork(philo);
	unlock_left_fork(philo);
	pthread_mutex_lock(&p_data->mutex_data);
	if (p_data->meals_to_stop != -1 && philo->nb_meals == p_data->meals_to_stop)
	{
		pthread_mutex_unlock(&p_data->mutex_data);
		return (-1);
	}
	pthread_mutex_unlock(&p_data->mutex_data);
	return (0);
}
