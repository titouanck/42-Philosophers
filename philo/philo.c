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
			pthread_mutex_lock(&(properties->end_mutex));
			if (properties->end)
			{
				pthread_mutex_unlock(&(properties->end_mutex));
				return ;
			}
			pthread_mutex_unlock(&(properties->end_mutex));
			pthread_mutex_lock(&(properties->satiety_mutex));
			if (!properties->hungry_philosophers)
			{
				pthread_mutex_unlock(&(properties->satiety_mutex));
				pthread_mutex_lock(&(properties->end_mutex));
				properties->end = 1;
				pthread_mutex_unlock(&(properties->end_mutex));
				return ;
			}
			pthread_mutex_unlock(&(properties->satiety_mutex));
			pthread_mutex_lock(&(philo->last_eat_mutex));
			if (get_time_ms() - philo->last_eat >= properties->time_to_die)
			{
				pthread_mutex_unlock(&(philo->last_eat_mutex));
				print_state(properties, philo, DIED);
				return ;
			}
			pthread_mutex_unlock(&(philo->last_eat_mutex));
			i++;
		}
		usleep(1);
	}
}

int	create_threads(t_properties *properties, t_philo *philo, pthread_t *threads)
{
	size_t	i;

	i = 0;
	while (i < properties->number_of_philosophers)
	{
		pthread_mutex_lock(&(philo->last_eat_mutex));
		philo->last_eat = properties->start_ms;
		pthread_mutex_unlock(&(philo->last_eat_mutex));
		if (properties->number_of_philosophers == 1)
			pthread_create(threads + i, NULL, lonely_routine, philo);
		else
			pthread_create(threads + i, NULL, routine, philo);
		philo = philo->next;
		i++;
	}
	return (1);
}

int	join_threads(t_properties *properties, pthread_t *threads)
{
	size_t	i;

	i = 0;
	while (i < properties->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (1);
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
	init_time(properties);
	create_threads(properties, philos, threads);
	check_death(properties, philos);
	join_threads(properties, threads);
	i = 0;
	philosopher = philos;
	while (i < properties->number_of_philosophers)
	{
		pthread_mutex_destroy(philosopher->left_fork.mutex);
		pthread_mutex_destroy(&(philosopher->last_eat_mutex));
		free(philosopher->left_fork.mutex);
		philosopher = philosopher->next;
		i++;
	}
	pthread_mutex_destroy(&(properties->print_mutex));
	pthread_mutex_destroy(&(properties->satiety_mutex));
	pthread_mutex_destroy(&(properties->end_mutex));
	return (free(properties), free_philos(philos), free(threads), 0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_putstr_fd(ERRARGS, 2), 1);
	else
		return (philo(argc, argv));
}
