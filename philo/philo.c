/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:17:41 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/31 12:51:42 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_properties	*_init(int argc, char **argv, t_philo **philos_ptr, pthread_t **threads_ptr)
{
	t_properties	*properties;
	t_philo			*philos;
	pthread_t		*threads;

	properties = define_properties(argv + 1, argc - 1);
	if (!properties)
		return (NULL);
	philos = generate_philos(properties, properties->number_of_philosophers);
	if (!philos)
		return (free(properties), NULL);
	if (properties->number_of_philosophers == 1)
	{
		philos->next = NULL;
		philos->prev = NULL;
	}
	threads = thread_philos(properties->number_of_philosophers);
	if (!threads)
		return (free(properties), free_philos(philos), NULL);
	*philos_ptr = philos;
	*threads_ptr = threads;
	return (properties);
}

int	philo(int argc, char **argv)
{
	t_properties	*properties;
	t_philo			*philos;
	pthread_t		*threads;
	t_philo			*philosopher;
	size_t			i;

	properties = _init(argc, argv, &philos, &threads);
	if (!properties)
		return (1);
	philosopher = philos;
	i = 0;
	get_time();
	while (i < properties->number_of_philosophers)
	{
		pthread_create(threads + i, NULL, routine, philosopher);
		philosopher = philosopher->next;
		i++;
	}
	// properties->start = 1;
	philosopher = philos;
	i = 0;
	while (i < properties->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&(properties->print_mutex));
	pthread_mutex_destroy(&(properties->checkdeath_mutex));
	return (free(properties), free_philos(philos), free(threads), 0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_putstr_fd(ERRARGS, 2), 1);
	else
		return (philo(argc, argv));
}
