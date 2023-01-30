/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 02:18:08 by tchevrie          #+#    #+#             */
/*   Updated: 2023/01/30 12:37:30 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_philo *first)
{
	t_philo	*current;
	t_philo	*tmp;

	current = first;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp);
		if (current == first)
			break ;
	}
}

static void	philos_initialisation(t_philo *first, t_rules *rules)
{
	t_philo	*current;
	
	current = first;
	while (current)
	{
		current->rules = rules;
		current->fork = 1;
		current->eat = 0;
		current->sleep = 0;
		current = current->next;
		if (current == first)
			break ;
	}
}

t_philo	*create_philos(int nbr, t_rules *rules)
{
	size_t	i;
	t_philo	*first;
	t_philo	*current;

	first = malloc(sizeof(t_philo));
	if (!first)
		return (ft_putstr_fd(ERR_ALLOC, 2), NULL);
	first->nbr = 1;
	current = first;
	i = 2;
	while (i <= nbr)
	{
		current->next = malloc(sizeof(t_philo));
		if (!(current->next))
			return (ft_putstr_fd(ERR_ALLOC, 2), free_philos(first), NULL);
		current->next->prev = current;
		current = current->next;
		current->nbr = i;
		i++;
	}
	current->next = first;
	first->prev = current;
	philos_initialisation(first, rules);
	return (first);
}

pthread_t	*thread_philos(int number_of_philosophers)
{
	pthread_t	*threads;
	
	threads = malloc(sizeof(pthread_t) * number_of_philosophers);
	if (!threads)
		return (ft_putstr_fd(ERR_ALLOC, 2), NULL);
	return (threads);
}
