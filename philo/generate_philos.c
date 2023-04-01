/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:59:51 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/30 14:18:52 by tchevrie         ###   ########.fr       */
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
		tmp = philo;
		philo = philo->next;
		free(tmp);
		if (philo == first)
			break ;
	}
}
// MALLOC PAS PROTEGE !
void	philos_initialiation(t_properties *properties, t_philo *first)
{
	t_philo	*philo;
	size_t	i;

	i = 1;
	philo = first;
	while (philo)
	{

		philo->properties = properties;
		philo->id = i;
		philo->meals = 0;
		philo->left_fork.holder = 0;
		philo->right_fork.holder = 0;
		philo->left_fork.mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo->left_fork.mutex, NULL);
		pthread_mutex_init(&(philo->last_eat_mutex), NULL);
		philo = philo->next;
		if (philo == first)
			break ;
		i++;
	}
	while (philo)
	{

		philo->right_fork.mutex = philo->next->left_fork.mutex;
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
