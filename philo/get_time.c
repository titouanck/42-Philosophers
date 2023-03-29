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

long	get_time(void)
{
	static long		start_ms;
	long			time_ms;
	struct timeval	tv;

	if (!start_ms)
	{
		if (gettimeofday(&tv, NULL) != 0)
			return (-1);
		start_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		return (0);
	}
	else
	{
		if (gettimeofday(&tv, NULL) != 0)
			return (-1);
		time_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		time_ms -= start_ms;
		return (time_ms);
	}
}
