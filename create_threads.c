/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 09:07:56 by srandria          #+#    #+#             */
/*   Updated: 2024/12/13 09:52:00 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*thread_routine(void *value)
{
	(void)value;
	write (1,"\nreate_thread", 13);
	return (NULL);
}

void	create_phreads(t_philo_d *philo_data)
{
	int	i;

	i = -1;
	while (++i < philo_data->nb_philos)
	{
		philo_data->threads[i] = pthread_create(&philo_data->threads[i],
			NULL, thread_routine, NULL);
		// nedd to add errore management if error on creating threadk
	}
}
