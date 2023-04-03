/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:14:28 by tchevrie          #+#    #+#             */
/*   Updated: 2023/04/03 13:41:27 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_t	*allocate_threads(int number_of_philosophers)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * number_of_philosophers);
	if (!threads)
		return (ft_putstr_fd(ERRALLOC, 2), NULL);
	return (threads);
}

int	create_threads(t_properties *properties, t_philo *philo, \
	pthread_t *threads)
{
	int	i;
	int	r;

	r = 1;
	i = 0;
	while (i < properties->number_of_philosophers)
	{
		pthread_mutex_lock(&(philo->last_eat_mutex));
		philo->last_eat = properties->start_ms;
		pthread_mutex_unlock(&(philo->last_eat_mutex));
		if (properties->number_of_philosophers == 1)
		{
			if (pthread_create(threads + i, NULL, lonely_routine, philo) != 0)
				r = 0;
		}
		else
		{
			if (pthread_create(threads + i, NULL, routine, philo) != 0)
				r = 0;
		}
		philo = philo->next;
		i++;
	}
	return (r);
}

int	join_threads(t_properties *properties, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < properties->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (1);
}
