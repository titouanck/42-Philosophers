/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:41:40 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/31 01:42:00 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	restitute_forks(t_properties *properties, t_philo *philo)
{
	if (philo->nbr % 2 == 0)
	{
		if (philo->right_fork_hodler)
			pthread_mutex_unlock(&philo->next->fork);
		philo->right_fork_hodler = 0;
		if (philo->left_fork_hodler)
			pthread_mutex_unlock(&philo->fork);
		philo->left_fork_hodler = 0;
	}
	else
	{
		if (philo->left_fork_hodler)
			pthread_mutex_unlock(&philo->fork);
		philo->left_fork_hodler = 0;
		if (philo->right_fork_hodler)
			pthread_mutex_unlock(&philo->next->fork);
		philo->right_fork_hodler = 0;
	}
}

int	take_forks(t_properties *properties, t_philo *philo)
{
	if (philo->nbr % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		philo->left_fork_hodler = 1;
		if (!check_death(properties, philo) || !print_state(properties, philo, FORK))
			return (0);
		pthread_mutex_lock(&philo->next->fork);
		philo->right_fork_hodler = 1;
		if (!check_death(properties, philo) || !print_state(properties, philo, FORK))
			return (0);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		philo->right_fork_hodler = 1;
		if (!check_death(properties, philo) || !print_state(properties, philo, FORK))
			return (0);
		pthread_mutex_lock(&philo->fork);
		philo->left_fork_hodler = 1;
		if (!check_death(properties, philo) || !print_state(properties, philo, FORK))
			return (0);
	}
	return (1);
}

int	just_eat(t_properties *properties, t_philo *philo)
{
	if (!print_state(properties, philo, EATING))
		return (0);
	philo->last_eat = get_time();
	if (!sleep_ms(properties, philo, properties->time_to_eat))
		return (0);
	return (1);
}

int	night_time(t_properties *properties, t_philo *philo)
{
	if (!print_state(properties, philo, SLEEPING) \
	|| !sleep_ms(properties, philo, properties->time_to_sleep))
		return (0);
	return (1);
}
