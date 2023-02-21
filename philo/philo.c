/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:26:58 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/21 15:43:07 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	printf("Bonjour, je suis le philo %d\n", philo->nbr);
}

static int	ft_philo(t_properties *properties, \
	t_philo *first, pthread_t *threads)
{
	size_t	i;
	t_philo	*philo;

	philo = first;
	i = 0;
	while (i < properties->number_of_philosophers)
	{
		pthread_create(threads + i, NULL, routine, philo);
		philo = philo->next;
		i++;
	}
	philo = first;
	i = 0;
	while (i < properties->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (free(properties), free_philos(first), free(threads), 0);
}

static int	initialisation(char **args, int size)
{
	t_properties	*properties;
	t_philo			*philo;
	pthread_t		*threads;

	properties = define_properties(args, size);
	if (!properties)
		return (1);
	philo = generate_philos(properties->number_of_philosophers);
	if (!philo)
		return (free(properties), 1);
	if (properties->number_of_philosophers == 1)
	{
		philo->next = NULL;
		philo->prev = NULL;
	}
	threads = thread_philos(properties->number_of_philosophers);
	if (!threads)
		return (free(properties), free_philos(philo), 1);
	if (!time_initialisation(properties, philo))
		return (free(properties), free_philos(philo), free(threads), 1);
	return (ft_philo(properties, philo, threads));
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_putstr_fd(ERRARGS, 2), 1);
	else
		return (initialisation(argv + 1, argc - 1));
}
