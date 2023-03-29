/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:58:26 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/29 18:57:49 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	_print(long time_ms, int philo, int state)
{
	const char	*print_state;

	if (state == FORK)
		print_state = "has \033[37mtaken a fork\033[0m";
	if (state == EATING)
		print_state = "is \033[33meating\033[0m";
	if (state == SLEEPING)
		print_state = "is \033[34msleeping\033[0m";
	if (state == THINKING)
		print_state = "is \033[35mthinking\033[0m";
	if (state == DIED)
		print_state = "\033[31mdied\033[0m";
	printf("%-6ld \033[1m%-4d\033[0m %s\n", time_ms, philo, print_state);
}

int	print_state(t_properties *properties, t_philo *philo, int state)
{
	long		time_ms;

	pthread_mutex_lock(&(properties->print_mutex));
	if (properties->death)
	{
		restitute_forks(properties, philo);
		pthread_mutex_unlock(&(properties->print_mutex));
		exit(0);
	}
	else if (state == DIED)
		properties->death = 1;		
	time_ms = get_time();
	_print(time_ms, philo->nbr, state);
	pthread_mutex_unlock(&(properties->print_mutex));
	if (state == DIED)
	{
		restitute_forks(properties, philo);
		exit(0);
	}
	return (1);
}
