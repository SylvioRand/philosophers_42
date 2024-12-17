/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:03:56 by srandria          #+#    #+#             */
/*   Updated: 2024/12/17 10:00:15 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	get_int_value(char *nb_str)
{
	long long	value;

	value = 0;
	while (*nb_str)
	{
		value = value * 10 + *nb_str - 48;
		if (value > 4294967295)
		{
			err("Error: value exceeds the maximum limit of an unsigned int");
			exit (1);
		}
		nb_str++;
	}
	return (value);
}

void	store_args(int argc, char **argv, t_philo_d *philo_data)
{
	philo_data->nb_philos = get_int_value(argv[1]);
	philo_data->time_to_die = get_int_value(argv[2]);
	philo_data->time_to_eat = get_int_value(argv[3]);
	philo_data->time_to_sleep = get_int_value(argv[4]);
	if (argc == 6)
		philo_data->meals_to_stop = get_int_value(argv[5]);
	else
		philo_data->meals_to_stop = -1;
}
