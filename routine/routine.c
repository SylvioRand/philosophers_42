/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:21:16 by srandria          #+#    #+#             */
/*   Updated: 2024/12/19 11:44:51 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if ((philo->id & 1) == 0)
		{
			usleep(1);
			if (philosopher_odd_eat(philo) == -1)
				return (NULL);
		}
		else
		{
			usleep(1);
			if (philosopher_even_eat(philo) == -1)
				return (NULL);
		}
		usleep(1);
		if (philosopher_sleep(philo) == -1)
			return (NULL);
		usleep(1);
		if (philosopher_think(philo) == -1)
			return (NULL);
	}
	return (NULL);
}
