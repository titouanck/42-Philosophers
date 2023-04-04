/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:45:50 by tchevrie          #+#    #+#             */
/*   Updated: 2023/04/04 11:42:03 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	_check_last_eat(t_properties *properties, t_philo *philo)
{
	pthread_mutex_lock(&(philo->last_eat_mutex));
	if (get_time_ms() - philo->last_eat >= properties->time_to_die)
	{
		pthread_mutex_unlock(&(philo->last_eat_mutex));
		print_state(properties, philo, DIED);
		return (0);
	}
	pthread_mutex_unlock(&(philo->last_eat_mutex));
	return (1);
}

void	check_death(t_properties *properties, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < properties->number_of_philosophers)
		{
			pthread_mutex_lock(&(properties->end_mutex));
			if (properties->end)
			{
				pthread_mutex_unlock(&(properties->end_mutex));
				return ;
			}
			else
				pthread_mutex_unlock(&(properties->end_mutex));
			if (!_check_last_eat(properties, philo))
				return ;
			i++;
		}
		usleep(1);
	}
}
