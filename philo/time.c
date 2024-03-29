/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:37:27 by tchevrie          #+#    #+#             */
/*   Updated: 2023/04/25 13:20:37 by tchevrie         ###   ########.fr       */
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

long long	get_time_us(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000000) + tv.tv_usec);
}

long long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	sleep_us(unsigned long long sleep_us, t_properties *properties)
{
	long long	wake_up_time_us;

	wake_up_time_us = get_time_us() + sleep_us;
	while (get_time_us() < wake_up_time_us)
	{
		pthread_mutex_lock(&(properties->end_mutex));
		if (properties->end)
		{
			pthread_mutex_unlock(&(properties->end_mutex));
			break ;
		}
		else
			pthread_mutex_unlock(&(properties->end_mutex));
		usleep(500);
	}
}

void	sleep_ms(unsigned long long sleep_ms, t_properties *properties)
{
	long long	wake_up_time_ms;

	wake_up_time_ms = get_time_ms() + sleep_ms;
	while (get_time_ms() < wake_up_time_ms)
	{
		pthread_mutex_lock(&(properties->end_mutex));
		if (properties->end)
		{
			pthread_mutex_unlock(&(properties->end_mutex));
			break ;
		}
		else
			pthread_mutex_unlock(&(properties->end_mutex));
		usleep(500);
	}
}
