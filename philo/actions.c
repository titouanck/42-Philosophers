/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:41:40 by tchevrie          #+#    #+#             */
/*   Updated: 2023/04/25 13:11:19 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	restitute_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (philo->right_fork.holder)
			pthread_mutex_unlock(philo->right_fork.mutex);
		philo->right_fork.holder = 0;
		if (philo->left_fork.holder)
			pthread_mutex_unlock(philo->left_fork.mutex);
		philo->left_fork.holder = 0;
	}
	else
	{
		if (philo->left_fork.holder)
			pthread_mutex_unlock(philo->left_fork.mutex);
		philo->left_fork.holder = 0;
		if (philo->right_fork.holder)
			pthread_mutex_unlock(philo->right_fork.mutex);
		philo->right_fork.holder = 0;
	}
}

int	take_forks(t_properties *properties, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork.mutex);
		philo->left_fork.holder = 1;
		if (!print_state(properties, philo, L_FORK))
			return (0);
		pthread_mutex_lock(philo->right_fork.mutex);
		philo->right_fork.holder = 1;
		if (!print_state(properties, philo, R_FORK))
			return (0);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork.mutex);
		philo->right_fork.holder = 1;
		if (!print_state(properties, philo, R_FORK))
			return (0);
		pthread_mutex_lock(philo->left_fork.mutex);
		philo->left_fork.holder = 1;
		if (!print_state(properties, philo, L_FORK))
			return (0);
	}
	return (1);
}

int	just_eat(t_properties *properties, t_philo *philo)
{
	if (++philo->meals == properties->must_eat)
	{
		pthread_mutex_lock(&(properties->satiety_mutex));
		properties->hungry_philosophers -= 1;
		pthread_mutex_unlock(&(properties->satiety_mutex));
	}
	if (!print_state(properties, philo, EATING))
		return (0);
	pthread_mutex_lock(&(philo->last_eat_mutex));
	philo->last_eat = get_time_ms();
	pthread_mutex_unlock(&(philo->last_eat_mutex));
	sleep_ms(properties->time_to_eat, properties);
	return (1);
}

int	night_time(t_properties *properties, t_philo *philo)
{
	if (!print_state(properties, philo, SLEEPING))
		return (0);
	sleep_ms(properties->time_to_sleep, properties);
	return (1);
}

int	deep_thought(t_properties *properties, t_philo *philo)
{
	if (!print_state(properties, philo, THINKING))
		return (0);
	if (properties->time_to_think)
		sleep_us(properties->time_to_think, properties);
	return (1);
}
