/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 02:29:12 by zimbo             #+#    #+#             */
/*   Updated: 2026/01/07 02:49:38 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_sec / 1000);
}

void	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

void	print_status(t_philo *philo, char *status)
{
	long	time;

	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->death_lock);
	if (!philo->data->someone_died || status[0] == 'd')
	{
		time = get_time() - philo->data->start_time;
		printf("%ld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->death_lock);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	cleanup(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	if (forks)
	{
		i = -1;
		while (++i < data->num_philos)
			pthread_mutex_destroy(&forks[i]);
		free(forks);
	}
	if (philos)
		free(philos);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	pthread_mutex_destroy(&data->meal_lock);
}

int	check_philo_death(t_philo *philo)
{
	if (get_time() - philo->last_meal_time > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->meal_lock);
		pthread_mutex_lock(&philo->data->death_lock);
		philo->data->someone_died = true;
		pthread_mutex_unlock(&philo->data->death_lock);
		print_status(philo, "died");
		return (1);
	}
	return (0);
}
