/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:59:44 by srandria          #+#    #+#             */
/*   Updated: 2024/12/16 10:22:30 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo_d	philo_data;

	if (error_args(argc, argv) == -1)
		return (1);
	store_args(argc, argv, &philo_data);
	if (philo_data.nb_philos > 200)
	{
		err("Error: The number of philosophers cannot exceed 200.");
		exit (1);
	}
	create_forks(&philo_data);
	printf("\n\nat the end");
	create_phreads(&philo_data);
	return (0);
}
