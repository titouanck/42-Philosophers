/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:11:38 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/01 12:45:06 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	im_dead(t_philo *philo)
{
	long	time;

	time = philo_gettimeofday();
	if (philo->rules->end)
		return (1);
	else if ((time - philo->last_eat) > philo->rules->time_to_die)
	{
		philo->rules->end = philo->nbr;
		usleep(1000);
		printf \
				(WHITE"%-5ld ms :"ENDCL"   %d\t"RED"died"ENDCL"\n", \
				((time + 1) - philo->rules->start_time), philo->nbr);
		return (1);
	}
	else
		return(0);
}