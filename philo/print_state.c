/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:58:26 by tchevrie          #+#    #+#             */
/*   Updated: 2023/04/04 11:35:26 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#ifndef VISUALIZER

static void	_print(long long time_elapsed_ms, int philo_id, int state)
{
	const char	*print_state;

	if (state == L_FORK || state == R_FORK)
		print_state = "has \033[37mtaken a fork\033[0m";
	if (state == EATING)
		print_state = "is  \033[33meating\033[0m";
	if (state == SLEEPING)
		print_state = "is  \033[34msleeping\033[0m";
	if (state == THINKING)
		print_state = "is  \033[35mthinking\033[0m";
	if (state == DIED)
		print_state = "\033[31mdied\033[0m";
	printf("%-6lld \033[1m%-4d\033[0m %s\n", \
	time_elapsed_ms, philo_id, print_state);
}

#endif

#ifdef VISUALIZER

static void	_print(long long time_elapsed_ms, int philo_id, int state)
{
	const char	*print_state;

	if (state == L_FORK || state == R_FORK)
		print_state = "has taken a fork";
	if (state == EATING)
		print_state = "is eating";
	if (state == SLEEPING)
		print_state = "is sleeping";
	if (state == THINKING)
		print_state = "is thinking";
	if (state == DIED)
		print_state = "died";
	printf("%lld %d %s\n", time_elapsed_ms, philo_id, print_state);
}

#endif

static int	_check_end(t_properties *properties, t_philo *philo, int state)
{
	pthread_mutex_lock(&(properties->end_mutex));
	if (properties->end)
	{
		pthread_mutex_unlock(&(properties->end_mutex));
		if (state != DIED)
			restitute_forks(philo);
		return (pthread_mutex_unlock(&(properties->print_mutex)), 0);
	}
	pthread_mutex_unlock(&(properties->end_mutex));
	pthread_mutex_lock(&(properties->satiety_mutex));
	if (!properties->hungry_philosophers && state != EATING)
	{
		pthread_mutex_unlock(&(properties->satiety_mutex));
		pthread_mutex_lock(&(properties->end_mutex));
		properties->end = 1;
		pthread_mutex_unlock(&(properties->end_mutex));
		return (pthread_mutex_unlock(&(properties->print_mutex)), 0);
	}
	pthread_mutex_unlock(&(properties->satiety_mutex));
	return (1);
}

static void	_print_death(t_properties *properties, t_philo *philo, \
			long long time_elapsed_ms)
{
	pthread_mutex_lock(&(properties->end_mutex));
	properties->end = 1;
	pthread_mutex_unlock(&(properties->end_mutex));
	_print(time_elapsed_ms, philo->id, DIED);
	pthread_mutex_unlock(&(properties->print_mutex));
}

int	print_state(t_properties *properties, t_philo *philo, int state)
{
	long long		current_time_ms;
	long long		time_elapsed_ms;

	pthread_mutex_lock(&(properties->print_mutex));
	if (!_check_end(properties, philo, state))
		return (0);
	current_time_ms = get_time_ms();
	time_elapsed_ms = current_time_ms - properties->start_ms;
	if (state == DIED)
		return (_print_death(properties, philo, time_elapsed_ms), 0);
	pthread_mutex_lock(&(philo->last_eat_mutex));
	if (current_time_ms - philo->last_eat > properties->time_to_die)
		return (pthread_mutex_unlock(&(philo->last_eat_mutex)), \
		restitute_forks(philo), \
		pthread_mutex_unlock(&(properties->print_mutex)), \
		print_state(properties, philo, DIED));
	else
		return (pthread_mutex_unlock(&(philo->last_eat_mutex)), \
		_print(time_elapsed_ms, philo->id, state), \
		pthread_mutex_unlock(&(properties->print_mutex)), 1);
}
