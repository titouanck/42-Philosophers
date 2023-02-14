/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:58:52 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/03 17:27:35 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philo *philo)
{
	if (philo->nbr % 2 == 0)
	{
		pthread_mutex_lock(&(philo->mutex));
		pthread_mutex_lock(&(philo->next->mutex));
	}
	else
	{
		pthread_mutex_lock(&(philo->next->mutex));
		pthread_mutex_lock(&(philo->mutex));
	}
	if (im_dead(philo))
		return (0);
	printf \
		(WHITE"%-5ld ms :"ENDCL"   %d\thas "WHITE"taken a fork"ENDCL"\n", \
		(philo_gettimeofday() - philo->rules->start_time), philo->nbr);
	return (1);
}

static void	return_forks(t_philo *philo)
{
	if (philo->nbr % 2 != 0)
	{
		pthread_mutex_unlock(&(philo->mutex));
		pthread_mutex_unlock(&(philo->next->mutex));
	}
	else
	{
		pthread_mutex_unlock(&(philo->next->mutex));
		pthread_mutex_unlock(&(philo->mutex));
	}
}

int	just_eat(t_philo *philo)
{
	while (1)
	{
		if (im_dead(philo))
			return (0);
		else if (philo->rules->waitl->next->nbr == philo->nbr)
		{
			if (take_forks(philo))
			{
				if (im_dead(philo))
					return (0);
				back_to_the_end(*(philo->rules));
				philo->last_eat = philo_gettimeofday();
				printf \
					(WHITE"%-5ld ms :"ENDCL"   %d\tis "BLUE" eating"ENDCL"\n", \
					(philo->last_eat - philo->rules->start_time), philo->nbr);
				usleep(philo->rules->time_to_eat);
				philo->meals += 1;
				return_forks(philo);
				break ;
			}
		}
	}
	return (1);
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
