#ifndef PHILO_H
#define PHILO_H

#include <string.h> // memset
#include <stdio.h>
#include <sys/types.h> // fork - waitpid
#include <sys/wait.h> // waitpid
#include <unistd.h> // fork - write - usleep 
#include <stdlib.h>
#include <sys/time.h> // gettimeofday
#include <pthread.h>
#include <errno.h>
// semaphore
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

typedef struct s_philo
{
	int	id;
	int	nb_meals;

}		t_philo;

typedef	struct s_philo_d
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_stop;
	pthread_t		threads[200];
	pthread_mutex_t	mutex[200];
}			t_philo_d;

int		error_args (int argc, char **argv);
int		ft_strlen (char *s);
void	err(char *s);
int		is_positive_numeric(char *token);
void	store_args(int argc, char **argv, t_philo_d *philo_data);
void	create_phreads(t_philo_d *philo_data);
void	ft_putstr(char *str);

#endif
