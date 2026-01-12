/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 02:29:12 by zimbo             #+#    #+#             */
/*   Updated: 2026/01/12 01:19:47 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time();
	while (1)
	{
		elapsed = get_time() - start;
		remaining = time - elapsed;
		if (remaining <= 0)
			break ;
		if (remaining > 100)
			usleep(100 * 1000);
		else
			usleep(remaining * 1000);
	}
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
	long	current_time;

	current_time = get_time();
	if (current_time - philo->last_meal_time > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->death_lock);
		if (!philo->data->someone_died)
		{
			philo->data->someone_died = true;
			pthread_mutex_unlock(&philo->data->death_lock);
			print_status(philo, "died");
		}
		else
		{
			pthread_mutex_unlock(&philo->data->death_lock);
		}
		return (1);
	}
	return (0);
}
