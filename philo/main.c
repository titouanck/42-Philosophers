/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:17:41 by tchevrie          #+#    #+#             */
/*   Updated: 2023/04/03 13:38:39 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_properties	*_init(int argc, char **argv, t_philo **philos_ptr, \
	pthread_t **threads_ptr)
{
	t_properties	*properties;
	t_philo			*philos;
	pthread_t		*threads;

	properties = define_properties(argv + 1, argc - 1);
	if (!properties)
		return (NULL);
	if (properties->must_eat == 0)
		return (free_properties(properties), NULL);
	philos = generate_philos(properties, properties->number_of_philosophers);
	if (!philos)
		return (free_properties(properties), NULL);
	threads = allocate_threads(properties->number_of_philosophers);
	if (!threads)
		return (free_properties(properties), free_philos(philos), NULL);
	*philos_ptr = philos;
	*threads_ptr = threads;
	properties->time_to_think = 0;
	if (properties->time_to_eat == 0 && properties->time_to_sleep == 0)
		properties->time_to_think = 100;
	else if (properties->number_of_philosophers % 2 != 0)
		properties->time_to_think = ((properties->time_to_eat * 2) - properties->time_to_sleep) * 1000;
	if (properties->time_to_think < 0)
		properties->time_to_think = 0;
	return (properties);
}

int	philo(int argc, char **argv)
{
	t_properties	*properties;
	t_philo			*philos;
	pthread_t		*threads;

	properties = _init(argc, argv, &philos, &threads);
	if (!properties)
		return (1);
	init_time(properties);
	if (create_threads(properties, philos, threads))
		check_death(properties, philos);
	else
	{
		pthread_mutex_lock(&(properties->end_mutex));
		properties->end = 1;
		pthread_mutex_unlock(&(properties->end_mutex));
	}
	join_threads(properties, threads);
	free_properties(properties);
	free_philos(philos);
	free(threads);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_putstr_fd(ERRARGS, 2), 1);
	else
		return (philo(argc, argv));
}
