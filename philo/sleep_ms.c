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

void	sleep_us(unsigned long sleep_us)
{
	long	wake_up_time_us;

	wake_up_time_us = get_time_us() + sleep_us;
	while (get_time_us() < wake_up_time_us)
		usleep(500);
}

void	sleep_ms(unsigned long sleep_ms)
{
	long	wake_up_time_ms;

	wake_up_time_ms = get_time_ms() + sleep_ms;
	while (get_time_ms() < wake_up_time_ms)
		usleep(500);
}

