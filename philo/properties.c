/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:52:13 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/21 15:44:01 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_properties(t_properties *properties, int size)
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
	properties->time_to_die *= 1000;
	properties->time_to_eat *= 1000;
	properties->time_to_sleep *= 1000;
	return (1);
}

t_properties	*define_properties(char **args, int size)
{
	t_properties	*properties;

	properties = malloc(sizeof(t_properties));
	if (!properties)
		return (ft_putstr_fd(ERRALLOC, 2), NULL);
	properties->number_of_philosophers = ft_atoi_check(args[0]);
	properties->time_to_die = ft_atoi_check(args[1]);
	properties->time_to_eat = ft_atoi_check(args[2]);
	properties->time_to_sleep = ft_atoi_check(args[3]);
	if (size == 5)
		properties->must_eat = ft_atoi_check(args[4]);
	else
		properties->must_eat = -1;
	if (!check_properties(properties, size))
		return (free(properties), ft_putstr_fd(ERRARGS, 2), NULL);
	return (properties);
}
