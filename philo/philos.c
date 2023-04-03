/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:59:51 by tchevrie          #+#    #+#             */
/*   Updated: 2023/04/03 15:06:20 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	_philos_init(t_properties *properties, t_philo *first)
{
	t_philo	*philo;
	size_t	i;

	i = 0;
	philo = first;
	while (philo && ++i)
	{
		philo->properties = properties;
		philo->id = i;
		philo->meals = 0;
		philo->left_fork.holder = 0;
		philo->right_fork.holder = 0;
		pthread_mutex_init(philo->left_fork.mutex, NULL);
		pthread_mutex_init(&(philo->last_eat_mutex), NULL);
		philo = philo->next;
		if (philo == first)
			break ;
	}
	while (philo)
	{
		philo->right_fork.mutex = philo->next->left_fork.mutex;
		philo = philo->next;
		if (philo == first)
			break ;
	}
}

t_philo	*generate_philos(t_properties *properties, int nb)
{
	t_philo	*philo;
	t_philo	*first;
	int		i;

	first = malloc(sizeof(t_philo));
	if (!first)
		return (ft_putstr_fd(ERRALLOC, 2), NULL);
	philo = first;
	i = 0;
	while (1)
	{
		philo->left_fork.mutex = malloc(sizeof(pthread_mutex_t));
		if (!(philo->left_fork.mutex))
			return (free_philos(first), ft_putstr_fd(ERRALLOC, 2), NULL);
		if (++i >= nb)
			break ;
		philo->next = malloc(sizeof(t_philo));
		if (!(philo->next))
			return (free_philos(first), ft_putstr_fd(ERRALLOC, 2), NULL);
		philo->next->prev = philo;
		philo = philo->next;
	}
	philo->next = first;
	first->prev = philo;
	return (_philos_init(properties, first), first);
}

void	free_philos(t_philo *first)
{
	t_philo	*philo;
	t_philo	*tmp;

	philo = first;
	while (philo)
	{
		pthread_mutex_destroy(&(philo->last_eat_mutex));
		pthread_mutex_destroy(philo->left_fork.mutex);
		free(philo->left_fork.mutex);
		tmp = philo;
		philo = philo->next;
		free(tmp);
		if (philo == first)
			break ;
	}
}
