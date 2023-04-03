/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:12:53 by tchevrie          #+#    #+#             */
/*   Updated: 2023/04/03 13:28:04 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	_check_properties(t_properties *properties, int size)
{
	if (properties->number_of_philosophers == ERRNBR \
	|| properties->time_to_die == ERRNBR \
	|| properties->time_to_eat == ERRNBR \
	|| properties->time_to_sleep == ERRNBR \
	|| properties->must_eat == ERRNBR)
		return (0);
	else if (properties->number_of_philosophers < 1 \
	|| properties->time_to_die < 0 \
	|| properties->time_to_eat < 0 \
	|| properties->time_to_sleep < 0 \
	|| (properties->must_eat < 0 && size == 5))
		return (0);
	return (1);
}

static int	_check_mutexes(t_properties *properties)
{
	if (pthread_mutex_init(&(properties->print_mutex), NULL) != 0)
		return (ft_putstr_fd(ERRALLOC, 2), \
		free(properties), \
		0);
	else if (pthread_mutex_init(&(properties->satiety_mutex), NULL) != 0)
		return (ft_putstr_fd(ERRALLOC, 2), \
		pthread_mutex_destroy(&(properties->print_mutex)),
		free(properties), \
		0);
	else if (pthread_mutex_init(&(properties->end_mutex), NULL) != 0)
		return (ft_putstr_fd(ERRALLOC, 2), \
		pthread_mutex_destroy(&(properties->print_mutex)), \
		pthread_mutex_destroy(&(properties->satiety_mutex)),
		free(properties), \
		0);
	else
		return (1);
}

t_properties	*define_properties(char **args, int size)
{
	t_properties	*properties;

	properties = malloc(sizeof(t_properties));
	if (!properties)
		return (ft_putstr_fd(ERRALLOC, 2), NULL);
	properties->end = 0;
	properties->number_of_philosophers = atoi_spe(args[0]);
	properties->time_to_die = atoi_spe(args[1]);
	properties->time_to_eat = atoi_spe(args[2]);
	properties->time_to_sleep = atoi_spe(args[3]);
	properties->hungry_philosophers = properties->number_of_philosophers;
	if (size == 5)
		properties->must_eat = atoi_spe(args[4]);
	else
		properties->must_eat = -1;
	if (!_check_properties(properties, size))
		return (free(properties), ft_putstr_fd(ERRARGS, 2), NULL);
	if (!_check_mutexes(properties))
		return (NULL);
	return (properties);
}

void	free_properties(t_properties *properties)
{
	pthread_mutex_destroy(&(properties->print_mutex));
	pthread_mutex_destroy(&(properties->satiety_mutex));
	pthread_mutex_destroy(&(properties->end_mutex));
	free(properties);
}
