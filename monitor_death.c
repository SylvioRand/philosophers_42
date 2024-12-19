/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:07:06 by srandria          #+#    #+#             */
/*   Updated: 2024/12/19 19:42:52 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h" 
#include <unistd.h>

static void	reset_loop_index(t_philo_d *p_data, int *i)
{
	if (*i == p_data->nb_philos - 1)
		*i = -1;
	usleep(0);
}

static void	update_dead_flag(t_philo *philo, long time_ms, int i)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	pthread_mutex_lock(&p_data->mutex_dead_flag);
	p_data->dead_flag = 1;
	pthread_mutex_unlock(&p_data->mutex_dead_flag);
	if (p_data->nb_philos == 1)
	{
		pthread_mutex_lock(&p_data->mutex_data);
		if (philo->left_hand)
			pthread_mutex_unlock(philo->l_fork);
		if (philo->right_hand)
			pthread_mutex_unlock(philo->r_fork);
		philo->right_hand = 0;
		philo->left_hand = 0;
		pthread_mutex_unlock(&p_data->mutex_data);
	}
	pthread_mutex_lock(&p_data->mutex_printf);
	printf("\033[31m%ld %d is dead\n\033[0m", time_ms, i);
	pthread_mutex_unlock(&p_data->mutex_printf);
	usleep(0);
}

void	*monitor_death(void *ptr)
{
	t_philo_d	*p_data;
	t_philo		*philos;
	static int	i = -1;
	long		time_ms;

	p_data = get_philo_data_ptr();
	philos = (t_philo *)ptr;
	while (++i < p_data->nb_philos)
	{
		pthread_mutex_lock(&p_data->mutex_last_time_eat);
		time_ms = get_time_in_ms(philos[i].last_time_meal);
		pthread_mutex_unlock(&p_data->mutex_last_time_eat);
		if (time_ms > p_data->time_to_die)
		{
			pthread_mutex_lock(&p_data->mutex_data);
			if (p_data->meals_to_stop != -1
				&& philos[i].nb_meals == p_data->meals_to_stop)
			{
				pthread_mutex_unlock(&p_data->mutex_data);
				return (NULL);
			}
			pthread_mutex_unlock(&p_data->mutex_data);
			update_dead_flag(philos, time_ms, i);
			return (NULL);
		}
		reset_loop_index(p_data, &i);
	}
	return (NULL);
}
