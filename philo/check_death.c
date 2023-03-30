/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:43:32 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/31 01:43:37 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_properties *properties, t_philo *philo)
{
	long	time_ms;

	time_ms = get_time();
	if (properties->death)
	{
		restitute_forks(properties, philo);
		return (0);
	}
	return (1);
}
