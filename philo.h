/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:24:05 by srandria          #+#    #+#             */
/*   Updated: 2024/12/16 19:41:17 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <bits/pthreadtypes.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <errno.h>
// semaphore
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

typedef struct s_philo_d t_philo_d;

typedef enum e_state {
    THINKING,
    EATING,
    SLEEPING
} t_state;

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				end;
	t_philo_d		*philo_data;
}	t_philo;

struct s_philo_d
{
	int				nb_philos;
	struct timeval	start;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_stop;
	pthread_mutex_t	mutexes[201];
};

int		error_args(int argc, char **argv);
int		ft_strlen(char *s);
void	err(char *s);
int		is_positive_numeric(char *token);
void	store_args(int argc, char **argv, t_philo_d *philo_data);
void	create_phreads(t_philo_d *p_data, t_philo *philos);
void	ft_putstr(char *str);
void	create_forks(t_philo_d *philo_data);
long 	get_time_in_ms(struct timeval start);

#endif
