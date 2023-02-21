/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:15:02 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/21 15:43:36 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	time_initialisation(t_properties *properties, t_philo *first)
{
	t_philo	*current;

	properties->start = get_current_time();
	if (properties->start == -1)
		return (0);
	current = first;
	while (current)
	{
		current->last_eat = properties->start;
		current = current->next;
		if (current == first)
			break ;
	}
	return (1);
}
