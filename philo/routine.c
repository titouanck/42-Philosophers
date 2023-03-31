/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:42:59 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/31 13:54:15 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	t_properties	*properties;
	size_t			i;

	philo = arg;
	properties = philo->properties;
	i = 0;
	while (get_time_ms() < properties->start_ms)
		usleep(philo->id);
	if (philo->id % 2 == 0)
		sleep_us(properties->time_to_eat * 750);
	while (1)
	{
		if (!take_forks(properties, philo))
			return (restitute_forks(properties, philo), NULL);
		if (!just_eat(properties, philo))
			return (restitute_forks(properties, philo), NULL);
		restitute_forks(properties, philo);
		if (!night_time(properties, philo))
			return (NULL);
		if (!deep_thought(properties, philo))
			return (NULL);
		i++;
	}
}
