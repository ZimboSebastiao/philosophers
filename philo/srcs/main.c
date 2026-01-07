/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:29:51 by zimbo             #+#    #+#             */
/*   Updated: 2026/01/07 02:26:13 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (argc < 5 || argc > 6)
	{
		printf("Use: %s num_philos time_to_die
			time_to_eat time_to_sleep ", argv[0]);
		printf("[num_must_eat]\n");
		return (1);
	}
	if (!parse_args(argc, argv, &data))
		return (1);
	if (!init_data(&data, &philos, &forks))
		return (1);
	create_threads(&data, philos);
	cleanup(&data, philos, forks);
	return (0);
}
