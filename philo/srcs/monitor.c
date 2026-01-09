/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 02:16:58 by zimbo             #+#    #+#             */
/*   Updated: 2026/01/08 22:44:25 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_full(t_philo *philos, int *all_full)
{
	if (philos->data->num_must_eat != -1
		&& philos->meals_eaten >= philos->data->num_must_eat)
		(*all_full)++;
	return (0);
}

static int	check_single_philo(t_data *data, t_philo *philos,
	int i, int *all_full)
{
	int	died;

	pthread_mutex_lock(&data->meal_lock);
	died = check_philo_death(&philos[i]);
	if (!died)
		check_all_full(&philos[i], all_full);
	pthread_mutex_unlock(&data->meal_lock);
	return (died);
}

static int	check_all_philos(t_data *data, t_philo *philos, int *all_full)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (check_single_philo(data, philos, i, all_full))
			return (1);
	}
	return (0);
}

static int	handle_all_full(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	data->all_ate = true;
	data->someone_died = true;
	pthread_mutex_unlock(&data->death_lock);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*data;
	int		all_full;

	philos = (t_philo *)arg;
	data = philos->data;
	while (1)
	{
		all_full = 0;
		if (check_all_philos(data, philos, &all_full))
			return (NULL);
		if (all_full == data->num_philos && handle_all_full(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
