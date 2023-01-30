/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:26:58 by tchevrie          #+#    #+#             */
/*   Updated: 2023/01/30 02:52:48 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	printf("Hi from philo number %d\n", philo->nbr);
	return (NULL);
}

int	philo(char **args, int size)
{
	t_rules		rules;
	t_philo		*current;
	pthread_t	*threads;
	size_t		i;

	rules = philo_rules(args, size);
	if (rules.err)
		return (1);
	current = create_philos(rules.number_of_philosophers);
	if (!current)
		return (2);
	if (rules.number_of_philosophers == 1)
	{
		current->next = NULL;
		current->prev = NULL;
	}
	threads = thread_philos(rules.number_of_philosophers);
	if (!threads)
		return(free_philos(current), 3);
	i = 0;
	while (i < rules.number_of_philosophers)
	{
		pthread_create(threads + i, NULL, routine, current);
		current = current->next;
		i++;
	}
	i = 0;
	while (i < rules.number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free_philos(current);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 5)
		return (ft_putstr_fd(ERR_NOTENOUGHARGS, 2), 1);
	else if (argc > 6)
		return (ft_putstr_fd(ERR_TOOMANYARGS, 2), 1);
	else
		return (philo(argv + 1, argc - 1));
}
