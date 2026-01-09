/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:32:50 by zimbo             #+#    #+#             */
/*   Updated: 2026/01/08 23:38:09 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_must_eat = -1;
	if (argc == 6)
		data->num_must_eat = ft_atoi(argv[5]);
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		printf("Error: Arguments should be based on positive numbers.\n");
		return (0);
	}
	return (1);
}

static int	init_forks(t_data *data, pthread_mutex_t **forks)
{
	int	i;

	*forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!*forks)
		return (0);
	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_init(&(*forks)[i], NULL);
	return (1);
}

static int	init_philosophers(t_data *data, t_philo **philos,
				pthread_mutex_t *forks)
{
	int		i;
	long	current_time;

	*philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philos)
		return (0);
	current_time = get_time();
	data->start_time = current_time;
	i = -1;
	while (++i < data->num_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal_time = current_time;
		(*philos)[i].data = data;
		(*philos)[i].left_fork = &forks[i];
		(*philos)[i].right_fork = &forks[(i + 1) % data->num_philos];
	}
	return (1);
}

int	init_data(t_data *data, t_philo **philos, pthread_mutex_t **forks)
{
	data->someone_died = false;
	data->all_ate = false;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	if (!init_forks(data, forks))
		return (0);
	if (!init_philosophers(data, philos, *forks))
	{
		free(*forks);
		return (0);
	}
	return (1);
}
