/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:19:22 by srandria          #+#    #+#             */
/*   Updated: 2024/12/18 09:27:16 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philosopher_sleep(t_philo *philo)
{
	t_philo_d		*p_data;
	struct timeval	start;

	p_data = get_philo_data_ptr();
	gettimeofday(&start, NULL);
	print_state(philo, "is sleeping\n");
	while (get_time_in_ms(start) < p_data->time_to_sleep
		&& p_data->dead_flag == 0)
		usleep(0);
	if (p_data->dead_flag == 1)
		return (-1);
	return (0);
}