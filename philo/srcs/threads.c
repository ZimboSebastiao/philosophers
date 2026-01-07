/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:54:11 by zimbo             #+#    #+#             */
/*   Updated: 2026/01/07 02:31:50 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_data *data, t_philo *philos)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	while (++i < data->num_philos)
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
	pthread_create(&monitor, NULL, monitor_routine, philos);
	pthread_join(monitor, NULL);
	i = -1;
	while (++i < data->num_philos)
		pthread_join(philos[i].thread, NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_lock);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_lock);
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}
