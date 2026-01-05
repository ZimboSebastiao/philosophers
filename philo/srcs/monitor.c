/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 02:16:58 by zimbo             #+#    #+#             */
/*   Updated: 2026/01/05 02:28:48 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	int		i;
	int		all_full;

	philos = (t_philo *)arg;
	while (1)
	{
		i = -1;
		all_full = 0;
		while (++i < philos->data->num_philos)
		{
			pthread_mutex_lock(&philos->data->meal_lock);
			if (get_time() - philos[i].last_meal_time > philos->data->time_to_die)
			{
				pthread_mutex_unlock(&philos->data->meal_lock);
				pthread_mutex_lock(&philos->data->death_lock);
				philos->data->someone_died = true;
				pthread_mutex_unlock(&philos->data->death_lock);
				print_status(&philos[i], "died");
				return (NULL);
			}
			if (philos->data->num_must_eat != -1 && philos[i].meals_eaten >= philos->data->num_must_eat)
				all_full++;
			pthread_mutex_unlock(&philos->data->meal_lock);
		}
		if (all_full == philos->data->num_philos)
		{
			pthread_mutex_lock(&philos->data->death_lock);
			philos->data->all_ate = true;
			philos->data->someone_died = true;
			pthread_mutex_unlock(&philos->data->death_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}