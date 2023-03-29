/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:17:41 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/29 19:13:50 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_properties *properties, t_philo *philo)
{
	long	time_ms;

	time_ms = get_time();
	if (properties->death)
	{
		restitute_forks(properties, philo);
		exit(0);
	}
	else if (time_ms - philo->last_eat >= properties->time_to_die)
	{
		print_state(properties, philo, DIED);
		exit(0);
	}
}

void	sleep_ms(t_properties *properties, t_philo *philo, long x_ms)
{
	x_ms *= 1000;

	while (x_ms > 500)
	{
		check_death(properties, philo);
		usleep(500);
		x_ms -= 500;
	}
	check_death(properties, philo);
	usleep(x_ms);
}

void	restitute_forks(t_properties *properties, t_philo *philo)
{
	if (!philo->fork_hodler)
		return ;
	philo->fork_hodler = 0;
	if (philo->nbr % 2)
	{
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
	}
}

void	take_forks(t_properties *properties, t_philo *philo)
{
	if (philo->nbr % 2)
	{
		pthread_mutex_lock(&philo->fork);
		print_state(properties, philo, FORK);
		pthread_mutex_lock(&philo->next->fork);
		print_state(properties, philo, FORK);
		
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork);
		print_state(properties, philo, FORK);
		pthread_mutex_lock(&philo->fork);
		print_state(properties, philo, FORK);
	}
	philo->fork_hodler = 1;
}

void	just_eat(t_properties *properties, t_philo *philo)
{
	check_death(properties, philo);
	print_state(properties, philo, EATING);
	sleep_ms(properties, philo, properties->time_to_eat);
	check_death(properties, philo);
	philo->last_eat = get_time();
}

void	*routine(void *arg)
{
	t_philo			*philo;
	t_properties	*properties;

	philo = arg;
	properties = philo->properties;
	while (1)
	{
		take_forks(properties, philo);
		just_eat(properties, philo);
		restitute_forks(properties, philo);
	}
}

static t_properties	*_init(int argc, char **argv, t_philo **philos_ptr, pthread_t **threads_ptr)
{
	t_properties	*properties;
	t_philo			*philos;
	pthread_t		*threads;

	properties = define_properties(argv + 1, argc - 1);
	if (!properties)
		return (NULL);
	philos = generate_philos(properties, properties->number_of_philosophers);
	if (!philos)
		return (free(properties), NULL);
	if (properties->number_of_philosophers == 1)
	{
		philos->next = NULL;
		philos->prev = NULL;
	}
	threads = thread_philos(properties->number_of_philosophers);
	if (!threads)
		return (free(properties), free_philos(philos), NULL);
	*philos_ptr = philos;
	*threads_ptr = threads;
	return (properties);
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
	if (get_time() == -1)
		return (free(properties), free_philos(philos), free(threads), 1);
	i = 0;
	while (i < properties->number_of_philosophers)
	{
		pthread_create(threads + i, NULL, routine, philosopher);
		philosopher = philosopher->next;
		i++;
	}
	philosopher = philos;
	i = 0;
	while (i < properties->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&(properties->print_mutex));
	return (free(properties), free_philos(philos), free(threads), 0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_putstr_fd(ERRARGS, 2), 1);
	else
		return (philo(argc, argv));
}
