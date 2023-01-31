/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:11:38 by tchevrie          #+#    #+#             */
/*   Updated: 2023/01/31 17:55:23 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	im_dead(t_philo *philo)
{
	long	time;

	time = philo_gettimeofday();
	if (philo->rules->end == 1)
		return (1);
	else if ((time - philo->last_eat) > philo->rules->time_to_die)
	{
		philo->rules->end = 1;
		usleep(1000);
		printf \
				(WHITE"%-5ld ms :"ENDCL"   %d\t"RED"died"ENDCL"\n", \
				(time - philo->rules->start_time + 1), philo->nbr);
		return (1);
	}
	else
		return(0);
}