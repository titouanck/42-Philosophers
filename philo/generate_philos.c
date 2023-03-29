/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:59:51 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/29 18:44:39 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_philo *first)
{
	t_philo	*philo;
	t_philo	*tmp;

	philo = first;
	while (philo)
	{
		pthread_mutex_destroy(&(philo->fork));
		tmp = philo;
		philo = philo->next;
		free(tmp);
		if (philo == first)
			break ;
	}
}

void	philos_initialiation(t_properties *properties, t_philo *first)
{
	t_philo	*philo;
	size_t	i;

	i = 1;
	philo = first;
	while (philo)
	{
		pthread_mutex_init(&(philo->fork), NULL);
		philo->nbr = i;
		philo->properties = properties;
		philo->meals = 0;
		philo->last_eat = 0;
		philo->fork_hodler = 0;
		philo = philo->next;
		if (philo == first)
			break ;
		i++;
	}
}

t_philo	*generate_philos(t_properties *properties, int nb)
{
	t_philo	*philo;
	t_philo	*first;
	size_t	i;

	first = malloc(sizeof(t_philo));
	if (!first)
		return (ft_putstr_fd(ERRALLOC, 2), NULL);
	philo = first;
	i = 1;
	while (i < nb)
	{
		philo->next = malloc(sizeof(t_philo));
		if (!(philo->next))
			return (free_philos(first), ft_putstr_fd(ERRALLOC, 2), NULL);
		philo->next->prev = philo;
		philo = philo->next;
		i++;
	}
	philo->next = first;
	first->prev = philo;
	philos_initialiation(properties, first);
	return (first);
}

pthread_t	*thread_philos(int number_of_philosophers)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * number_of_philosophers);
	if (!threads)
		return (ft_putstr_fd(ERRALLOC, 2), NULL);
	return (threads);
}
