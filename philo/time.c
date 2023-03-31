/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:37:27 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/29 16:40:30 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_time(t_properties *properties)
{
	struct timeval	tv;

	if (!properties || gettimeofday(&tv, NULL) != 0)
		return (0);
	properties->start_ms = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) \
							+ 1 + properties->number_of_philosophers / 10);
	return (1);
}

long	get_time_us(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000000) + tv.tv_usec);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
