/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:35:16 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/31 12:53:01 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_ms(t_properties *properties, t_philo *philo, long sleep_ms)
{
	long	time_ms;
	long	max_ms;

	time_ms = get_time();
	max_ms = properties->time_to_die - (time_ms - philo->last_eat);
	if (sleep_ms < max_ms)
		return (usleep(sleep_ms * 1000), 1);
	else
	{
		usleep(max_ms * 1000);
		return (print_state(properties, philo, DIED));
	}
}

