/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:24:05 by srandria          #+#    #+#             */
/*   Updated: 2024/12/17 16:34:36 by srandria         ###   ########.fr       */
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


typedef enum e_state {
    THINKING,
    EATING,
    SLEEPING
} t_state;

typedef struct s_philo
{
	int				id;
	struct timeval	last_time_meal;
	int				nb_meals;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				left_hand;
	int				right_hand;
	int				end;
}	t_philo;

typedef struct s_philo_d
{
	int				nb_philos;
	struct timeval	start;
	int				dead_flag;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_stop;
	pthread_t		monitor_death;
	pthread_mutex_t	mutexes[200];
	pthread_mutex_t	mutex_printf;
}	t_philo_d;

int			error_args(int argc, char **argv);
int			ft_strlen(char *s);
void		err(char *s);
int			is_positive_numeric(char *token);
void		store_args(int argc, char **argv, t_philo_d *philo_data);
void		create_phreads(t_philo_d *p_data, t_philo *philos);
void		ft_putstr(char *str);
void		create_forks(t_philo_d *philo_data);
void		ft_putnbr(int nb);
long		get_time_in_ms(struct timeval start);
t_philo_d	*get_philo_data_ptr(void);
int			print_state(t_philo *philo, char *str);
int			philosopher_odd_eat(t_philo *philo);
int			philosopher_even_eat(t_philo *philo);

#endif
