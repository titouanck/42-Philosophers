/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:58:52 by tchevrie          #+#    #+#             */
/*   Updated: 2023/01/31 17:51:32 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philo *philo)
{
	pthread_mutex_t	mutex;
	
	pthread_mutex_init(&mutex, NULL);
	while (1)
	{
		if (im_dead(philo))
			return (pthread_mutex_destroy(&mutex), 0);
		else if (philo->eat <= philo->rules->round->eat \
		&& philo->fork && philo->next && philo->next->fork)
			break ;
	}
	if (philo->fork && philo->next && philo->next->fork)
	{
		pthread_mutex_lock(&mutex);
		philo->fork = 0;
		philo->next->fork = 0;
		pthread_mutex_unlock(&mutex);
		pthread_mutex_destroy(&mutex);
		if (im_dead(philo))
			return (0);
		printf \
			(WHITE"%-5ld ms :"ENDCL"   %d\thas "WHITE"taken a fork"ENDCL"\n", \
			(philo_gettimeofday() - philo->rules->start_time), philo->nbr);
	}
	else
	{
		pthread_mutex_destroy(&mutex);
		if (im_dead(philo))
			return (0);
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
	philo->rules->round->philos += 1;
	if (philo->rules->round->philos == philo->rules->number_of_philosophers)
	{
		philo->rules->round->eat += 1;
		philo->rules->round->philos = 0;
	}
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
}

int	just_eat(t_philo *philo)
{
	{
		if (!take_forks(philo))
			return (0);
		if (im_dead(philo))
			return (0);
		philo->last_eat = philo_gettimeofday();
		printf \
			(WHITE"%-5ld ms :"ENDCL"   %d\tis "BLUE" eating"ENDCL"\n", \
			(philo->last_eat - philo->rules->start_time), philo->nbr);
		usleep(philo->rules->time_to_eat);
		philo->eat += 1;
		return_forks(philo);
		return (1);
	}
}

int	just_sleep(t_philo *philo)
{
	int	wait;

	if (im_dead(philo))
		return (0);
	printf \
		(WHITE"%-5ld ms :"ENDCL"   %d\tis "GREEN" sleeping"ENDCL"\n", \
		(philo_gettimeofday() - philo->rules->start_time), philo->nbr);
	if (((philo_gettimeofday() - philo->last_eat) + (philo->rules->time_to_sleep / 1000)) > philo->rules->time_to_die)
	{
		wait = philo->rules->time_to_die - (philo_gettimeofday() - philo->last_eat);
		if (wait < 0)
			wait = 0;
		usleep((wait + 1) * 1000);
		im_dead(philo);
		return (0);
	}
	else
	{
		usleep(philo->rules->time_to_sleep);
		return (1);
	}
}

int	just_think(t_philo *philo)
{
	if (im_dead(philo))
		return (0);
	printf \
		(WHITE"%-5ld ms :"ENDCL"   %d\tis "MAGENTA" thinking"ENDCL"\n", \
		(philo_gettimeofday() - philo->rules->start_time), philo->nbr);
	return (1);
}
