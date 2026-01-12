/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 02:05:01 by zimbo             #+#    #+#             */
/*   Updated: 2026/01/12 01:13:57 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a left fork");
	if (philo->data->num_philos == 1)
	{
		while (1)
		{
			pthread_mutex_lock(&philo->data->meal_lock);
			if (get_time() - philo->last_meal_time >= philo->data->time_to_die)
			{
				pthread_mutex_unlock(&philo->data->meal_lock);
				break ;
			}
			pthread_mutex_unlock(&philo->data->meal_lock);
			usleep(100);
		}
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a right fork");
}

void	eat(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	if (philo->data->num_philos > 1)
		pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
}
