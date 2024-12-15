/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:06:57 by srandria          #+#    #+#             */
/*   Updated: 2024/12/13 09:36:09 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	are_arguments_positive_numeric(int argc, char **argv)
{
	argv++;
	while (--argc > 0)
	{
		if (!is_positive_numeric(*argv))
			return (0);
		argv++;
	}
	return (1);
}

int	error_args(int argc, char **argv)
{
	(void)argv;
	if (argc == 1)
	{
		err("Error: arguments are required for Philo.");
		return (-1);
	}
	if (are_arguments_positive_numeric(argc, argv) == 0)
	{
		err("Error: positive numeric values are required.");
		return (-1);
	}
	if (argc <= 4)
	{
		err("Error: too few arguments.");
		return (-1);
	}
	if (argc > 6)
	{
		err("Error: Too many arguments provided.");
		return (-1);
	}
	return (0);
}
