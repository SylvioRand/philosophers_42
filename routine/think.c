/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:20:03 by srandria          #+#    #+#             */
/*   Updated: 2024/12/18 09:20:14 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philosopher_think(t_philo *philo)
{
	t_philo_d		*p_data;

	p_data = get_philo_data_ptr();
	print_state(philo, "is thinking\n");
	usleep(0);
	if (p_data->dead_flag)
		return (-1);
	return (0);
}
