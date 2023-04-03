/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:42:59 by tchevrie          #+#    #+#             */
/*   Updated: 2023/04/03 13:43:18 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	t_properties	*properties;

	philo = arg;
	properties = philo->properties;
	while (get_time_ms() < properties->start_ms)
		usleep(philo->id);
	if (philo->id % 2 == 0)
		sleep_us(properties->time_to_eat * 750);
	while (1)
	{
		if (!take_forks(properties, philo))
			return (restitute_forks(philo), NULL);
		if (!just_eat(properties, philo))
			return (restitute_forks(philo), NULL);
		restitute_forks(philo);
		if (!night_time(properties, philo))
			return (NULL);
		if (!deep_thought(properties, philo))
			return (NULL);
	}
}

void	*lonely_routine(void *arg)
{
	t_philo			*philo;
	t_properties	*properties;

	philo = arg;
	properties = philo->properties;
	if (properties->number_of_philosophers == 1)
	while (get_time_ms() < properties->start_ms)
		usleep(philo->id);
	pthread_mutex_lock(philo->left_fork.mutex);
	philo->left_fork.holder = 1;
	if (!print_state(properties, philo, L_FORK))
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&(properties->end_mutex));
		if (properties->end)
			break ;
		pthread_mutex_unlock(&(properties->end_mutex));
		usleep(250);
	}
	pthread_mutex_unlock(&(properties->end_mutex));
	pthread_mutex_unlock(philo->left_fork.mutex);
	return (NULL);
}
