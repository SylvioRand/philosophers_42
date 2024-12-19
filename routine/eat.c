/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:08:46 by srandria          #+#    #+#             */
/*   Updated: 2024/12/19 19:29:05 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

static void	manage_eating_time(void)
{
	t_philo_d		*p_data;
	long			ms;

	p_data = get_philo_data_ptr();
	ms = get_time_in_ms(p_data->start);
	while ((get_time_in_ms(p_data->start)) < ((p_data->time_to_eat) + ms))
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

static void	increment_meal_count(t_philo *philo)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	usleep (1);
	pthread_mutex_lock(&p_data->mutex_data);
	if (p_data->meals_to_stop != -1)
		philo->nb_meals++;
	pthread_mutex_unlock(&p_data->mutex_data);
}

static int	is_max_meals_reached(t_philo *philo)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	usleep(1);
	pthread_mutex_lock(&p_data->mutex_data);
	if (p_data->meals_to_stop != -1 && philo->nb_meals == p_data->meals_to_stop)
	{
		pthread_mutex_unlock(&p_data->mutex_data);
		return (1);
	}
	pthread_mutex_unlock(&p_data->mutex_data);
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
	if (p_data->nb_philos == 1)
		return (-1);
	if (print_state(philo, "has taken a fork\n") == -1)
		return (-1);
	if (print_state(philo, "\033[32mis eating\n\033[0m") == -1)
		return (-1);
	pthread_mutex_lock(&p_data->mutex_last_time_eat);
	gettimeofday(&philo->last_time_meal, NULL);
	pthread_mutex_unlock(&p_data->mutex_last_time_eat);
	increment_meal_count(philo);
	manage_eating_time();
	unlock_left_fork(philo);
	unlock_right_fork(philo);
	if (is_max_meals_reached(philo))
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
	if (p_data->nb_philos == 1)
		return (-1);
	if (print_state(philo, "has taken a fork\n") == -1)
		return (-1);
	if (print_state(philo, "\033[32mis eating\n\033[0m") == -1)
		return (-1);
	pthread_mutex_lock(&p_data->mutex_last_time_eat);
	gettimeofday(&philo->last_time_meal, NULL);
	pthread_mutex_unlock(&p_data->mutex_last_time_eat);
	increment_meal_count(philo);
	manage_eating_time();
	unlock_right_fork(philo);
	unlock_left_fork(philo);
	if (is_max_meals_reached(philo))
		return (-1);
	return (0);
}
