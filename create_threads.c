/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:07:56 by srandria          #+#    #+#             */
/*   Updated: 2024/12/17 19:48:30 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int	philosopher_sleep(t_philo *philo)
{
	t_philo_d		*p_data;
	struct timeval  start;

	p_data = get_philo_data_ptr();
	gettimeofday(&start, NULL);
	print_state(philo, "is sleeping\n");
	while (get_time_in_ms(start) < p_data->time_to_sleep
		&& p_data->dead_flag == 0)
		usleep(10);
	if (p_data->dead_flag == 1)
		return (-1);
	return (0);
}

int	philosopher_think(t_philo *philo)
{
	t_philo_d		*p_data;

	p_data = get_philo_data_ptr();
	print_state(philo, "is thinking\n");
	usleep(10);
	if (p_data->dead_flag)
		return (-1);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	
	philo = (t_philo *)ptr;
	while (1)
	{
		if ((philo->id & 1) == 0)
		{
			if (philosopher_odd_eat(philo) == -1)
				return (NULL);
		}
		else
		{
			if (philosopher_even_eat(philo) == -1)
				return (NULL);
		}
		if (philosopher_sleep(philo) == -1)
			return (NULL);
		if (philosopher_think(philo) == -1)
			return (NULL);
	}
	return (NULL);
}

static void	create_odd_threads(t_philo_d *p_data, t_philo *philos)
{
	int	i;
	int	nb_philos;

	i = -1;
	nb_philos = p_data->nb_philos;
	while (++i < p_data->nb_philos)
	{
		if (i % 2 == 0)
		{
			philos[i].id = i;
			if (i == 0)
				philos[i].r_fork = &p_data->mutexes[nb_philos - 1];
			else
				philos[i].r_fork = &p_data->mutexes[i - 1];
			philos[i].l_fork = &p_data->mutexes[i];
			philos[i].left_hand = 0;
			philos[i].right_hand = 0;
			philos[i].nb_meals = 0;
			gettimeofday(&philos[i].last_time_meal, NULL);
			pthread_create(&philos[i].thread, NULL,
				&routine, &philos[i]);
		}
	}
}

static void	create_even_threads(t_philo_d *p_data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < p_data->nb_philos)
	{
		if (i % 2)
		{
			philos[i].id = i;
			philos[i].r_fork = &p_data->mutexes[i - 1];
			philos[i].l_fork = &p_data->mutexes[i];
			philos[i].left_hand = 0;
			philos[i].right_hand = 0;
			philos[i].nb_meals = 0;
			gettimeofday(&philos[i].last_time_meal, NULL);
			pthread_create(&philos[i].thread, NULL,
				&routine, &philos[i]);
		}
	}
}

void	*monitor_death(void *ptr)
{
	t_philo_d	*p_data;
	t_philo		*philos;
	int			i;
	long		time_ms;

	i = -1;
	p_data = get_philo_data_ptr();
	philos = (t_philo *)ptr;
	while (++i < p_data->nb_philos)
	{
		time_ms = get_time_in_ms(philos[i].last_time_meal);
		if ( time_ms > p_data->time_to_die)
		{
			if (p_data->meals_to_stop != -1 && philos[i].nb_meals == p_data->meals_to_stop)
				return (NULL);
			pthread_mutex_lock(&p_data->mutex_printf);
			p_data->dead_flag = 1;
			printf("%ldms %d is dead\n", time_ms, i);
			pthread_mutex_unlock(&p_data->mutex_printf);
			break ;
		}
		if (i == p_data->nb_philos - 1)
			i = -1;
	}
	return (NULL);
}

static void	create_monitor_death(t_philo *philos)
{
	t_philo_d	*p_data;

	p_data = get_philo_data_ptr();
	pthread_create(&p_data->monitor_death, NULL,
		&monitor_death, philos);
}

void	create_phreads(t_philo_d *p_data, t_philo *philos)
{
	gettimeofday(&p_data->start, NULL);
	create_odd_threads(p_data, philos);
	if ((p_data->nb_philos & 1) == 0)
		usleep(100);
	create_even_threads(p_data, philos);
	usleep(100);
	create_monitor_death(philos);
}
