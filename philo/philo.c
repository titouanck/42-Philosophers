/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:17:41 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/31 12:51:42 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_properties	*_init(int argc, char **argv, t_philo **philos_ptr, \
	pthread_t **threads_ptr)
{
	t_properties	*properties;
	t_philo			*philos;
	pthread_t		*threads;

	properties = define_properties(argv + 1, argc - 1);
	if (!properties)
		return (NULL);
	if (properties->must_eat == 0)
		return (free(properties), NULL);
	philos = generate_philos(properties, properties->number_of_philosophers);
	if (!philos)
		return (free(properties), NULL);
	threads = thread_philos(properties->number_of_philosophers);
	if (!threads)
		return (free(properties), free_philos(philos), NULL);
	*philos_ptr = philos;
	*threads_ptr = threads;
	properties->time_to_think = properties->time_to_eat * 2 - properties->time_to_sleep;
	if (properties->number_of_philosophers % 2 == 0 || properties->time_to_think < 0)
		properties->time_to_think = 0;
	if (properties->time_to_eat == 0 && properties->time_to_sleep == 0)
		properties->time_to_think = 1;
	return (properties);
}

void	check_death(t_properties *properties, t_philo *philo)
{
	size_t	i;


	while (1)
	{
		i = 0;
		while (i < properties->number_of_philosophers)
		{
			if (properties->end)
				return ;
			pthread_mutex_lock(&(properties->satiety_mutex));
			if (!properties->hungry_philosophers)
			{
				properties->end = 1;
				return ;
			}
			pthread_mutex_unlock(&(properties->satiety_mutex));
			if (get_time_ms() - philo->last_eat > properties->time_to_die)
			{
				print_state(properties, philo, DIED);
				return ;
			}
			i++;
		}
		usleep(1);
	}
}

int	philo(int argc, char **argv)
{
	t_properties	*properties;
	t_philo			*philos;
	pthread_t		*threads;
	t_philo			*philosopher;
	size_t			i;

	properties = _init(argc, argv, &philos, &threads);
	if (!properties)
		return (1);
	philosopher = philos;
	i = 0;
	init_time(properties);
	while (i < properties->number_of_philosophers)
	{
		philosopher->last_eat = properties->start_ms;
		pthread_create(threads + i, NULL, routine, philosopher);
		philosopher = philosopher->next;
		i++;
	}
	i = 0;
	check_death(properties, philos);
	while (i < properties->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	i = 0;
	while (i < properties->number_of_philosophers)
	{
		pthread_mutex_destroy(philosopher->left_fork.mutex);
		free(philosopher->left_fork.mutex);
		philosopher = philosopher->next;
		i++;
	}
	pthread_mutex_destroy(&(properties->print_mutex));
	pthread_mutex_destroy(&(properties->satiety_mutex));
	return (free(properties), free_philos(philos), free(threads), 0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_putstr_fd(ERRARGS, 2), 1);
	else
		return (philo(argc, argv));
}
