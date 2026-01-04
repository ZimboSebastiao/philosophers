#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	long			start_time;
	bool			someone_died;
	bool			all_ate;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_lock;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_timee;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

int		parse_args(int argc, char **argv, t_data *data);
int		init_data(t_data *data, t_philo *philos, pthread_mutex_t **forks);
void	create_threads(t_data *data, t_philo *philos);
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg),

long	get_time(void);
void	ft_sleep(long time);
void	print_status(t_philo *philo, char *status);
void	cleanup(t_data *data, t_philo *philos, pthread_mutex_t *forks);

void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	think(t_philo *philo);

#endif