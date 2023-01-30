/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:58:52 by tchevrie          #+#    #+#             */
/*   Updated: 2023/01/30 13:30:59 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philo *philo)
{
	pthread_mutex_t	mutex;
	
	pthread_mutex_init(&mutex, NULL);
	while (1)
		if (philo->fork && philo->next && philo->next->fork)
			break ;
	if (philo->fork && philo->next && philo->next->fork)
	{
		pthread_mutex_lock(&mutex);
		philo->fork = 0;
		philo->next->fork = 0;
		pthread_mutex_unlock(&mutex);
		printf("%-4d has "WHITE"taken a fork"ENDCL"\n", philo->nbr);
		pthread_mutex_destroy(&mutex);
	}
	else
	{
		pthread_mutex_destroy(&mutex);
		return (take_forks(philo));	
	}
	return (1);
}

static void	return_forks(t_philo *philo)
{
	pthread_mutex_t	mutex;
	
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	philo->fork = 1;
	if (philo->next)
		philo->next->fork = 1;
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
}

int	just_eat(t_philo *philo)
{
	{
		if (!take_forks(philo))
			return (0);
		printf("%-4d is "BLUE" eating"ENDCL"\n", philo->nbr);
		usleep(philo->rules->time_to_eat);
		return_forks(philo);
		philo->eat += 1;
		return (1);
	}
}

void	just_sleep(t_philo *philo)
{
	printf("%-4d is "GREEN" sleeping"ENDCL"\n", philo->nbr);
	usleep(philo->rules->time_to_sleep);
	philo->sleep += 1;
}

void	just_think(t_philo *philo)
{
	printf("%-4d is "MAGENTA" thinking"ENDCL"\n", philo->nbr);
}
