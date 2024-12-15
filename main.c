/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:59:44 by srandria          #+#    #+#             */
/*   Updated: 2024/12/13 09:48:09 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

pthread_mutex_t mutex;

/*
void	*test(void *arg)
{
	int		i;

	i = 0;
	pthread_mutex_lock(&mutex);
	while (++i <= 50)
	{
		printf("%d\n", i);
	}
	pthread_mutex_unlock(&mutex);
	(void)arg;
	return (NULL);
}

pthread_t	*create_threads(int nb)
{
	int			i;
	int			status;
	pthread_t	*pthreads;

	i = -1;
	pthreads = malloc(sizeof(pthread_t) * nb);
	if (pthreads == NULL)
		return (NULL);
	while (++i < nb)
	{
		status = pthread_create(&pthreads[i], NULL, test, NULL);
		if (status != 0)
		{
			while (i--)
				pthread_join(pthreads[i], NULL);
			exit (1);
		}
	}
	return (pthreads);
}

int	ft_atoi(char *str)
{
	int result = 0;
	int sign = 1;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
        	str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (sign * result);
}

int	main(int argc, char **argv)
{
	int			i;
	int			nb_pthreads;
	pthread_t	*pthreads;
	
	(void)argv;
	i = -1;
	if (argc == 5 || argc == 6)
	{
		nb_pthreads = ft_atoi(argv[1]);
		pthreads = create_threads(nb_pthreads);
		while (++i < nb_pthreads)
			pthread_join(pthreads[i], NULL);
	}
	printf("\n\nFinish\n");
	return (0);
}
*/

int	main(int argc, char *argv[])
{
	t_philo_d	philo_data;

	if (error_args(argc, argv) == -1)
		return (1);
	store_args(argc, argv, &philo_data);
	if (philo_data.nb_philos > 200)
		err("Error: The number of philosophers cannot exceed 200.");
	create_phreads(&philo_data);
	return (0);
}
