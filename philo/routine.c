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

	philo = arg;
	properties = philo->properties;
	// while (!properties->start)
	// 	usleep(10);
	if (philo->nbr % 2 == 0)
		sleep_ms(properties, philo, properties->time_to_sleep);
	while (1)
	{
		if (!take_forks(properties, philo))
			return (restitute_forks(properties, philo), NULL);
		if (!just_eat(properties, philo))
			return (restitute_forks(properties, philo), NULL);
		restitute_forks(properties, philo);
		if (!night_time(properties, philo))
			return (NULL);
		if (!print_state(properties, philo, THINKING))
			return (NULL);
	}
}
