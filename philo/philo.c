/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:17:41 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/30 19:31:14 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_properties *properties, t_philo *philo)
{
	long	time_ms;

	time_ms = get_time();
	pthread_mutex_lock(&(properties->checkdeath_mutex));
	if (properties->death)
	{
		pthread_mutex_unlock(&(properties->checkdeath_mutex));
		// dprintf(2, "[%d] renonce a la vie apres avoir appris la mort d'un collegue.\n", philo->nbr);
		restitute_forks(properties, philo);
		return (0);
	}
	else
		pthread_mutex_unlock(&(properties->checkdeath_mutex));
	return (1);
}

int	sleep_ms(t_properties *properties, t_philo *philo, long sleep_ms)
{
	long	time_ms;
	long	max_ms;

	time_ms = get_time();
	max_ms = properties->time_to_die - (time_ms - philo->last_eat);
	if (sleep_ms < max_ms)
		return (usleep(sleep_ms * 1000), 1);
	else
	{
		usleep(max_ms * 1000);
		// dprintf(2, "[%d] S'est fait rattraper par le temps et n'a d'autre choix que de mourir.\n", philo->nbr);
		return (print_state(properties, philo, DIED));
	}
}

void	restitute_forks(t_properties *properties, t_philo *philo)
{
	if (philo->nbr % 2 == 0)
	{
		if (philo->right_fork_hodler)
			pthread_mutex_unlock(&philo->next->fork);
		philo->right_fork_hodler = 0;
		if (philo->left_fork_hodler)
			pthread_mutex_unlock(&philo->fork);
		philo->left_fork_hodler = 0;
	}
	else
	{
		if (philo->left_fork_hodler)
			pthread_mutex_unlock(&philo->fork);
		philo->left_fork_hodler = 0;
		if (philo->right_fork_hodler)
			pthread_mutex_unlock(&philo->next->fork);
		philo->right_fork_hodler = 0;
	}
}

int	take_forks(t_properties *properties, t_philo *philo)
{
	if (philo->nbr % 2 == 0)
	{
		dprintf(2, "[%d] veut prendre la fourchette %d\n", philo->nbr, philo->nbr);
		pthread_mutex_lock(&philo->fork);
		philo->left_fork_hodler = 1;
		if (!check_death(properties, philo) || !print_state(properties, philo, FORK))
			return (0);
		dprintf(2, "[%d] veut prendre la fourchette %d\n", philo->nbr, philo->next->nbr);
		pthread_mutex_lock(&philo->next->fork);
		philo->right_fork_hodler = 1;
		if (!check_death(properties, philo) || !print_state(properties, philo, FORK))
			return (0);
	}
	else
	{
		dprintf(2, "[%d] veut prendre la fourchette %d\n", philo->nbr, philo->next->nbr);
		pthread_mutex_lock(&philo->next->fork);
		philo->right_fork_hodler = 1;
		if (!check_death(properties, philo) || !print_state(properties, philo, FORK))
			return (0);
		dprintf(2, "[%d] veut prendre la fourchette %d\n", philo->nbr, philo->nbr);
		pthread_mutex_lock(&philo->fork);
		philo->left_fork_hodler = 1;
		if (!check_death(properties, philo) || !print_state(properties, philo, FORK))
			return (0);
	}
	return (1);
}

int	just_eat(t_properties *properties, t_philo *philo)
{
	if (!print_state(properties, philo, EATING))
		return (0);
	philo->last_eat = get_time();
	if (!sleep_ms(properties, philo, properties->time_to_eat))
		return (0);
	return (1);
}

int	night_time(t_properties *properties, t_philo *philo)
{
	if (!print_state(properties, philo, SLEEPING) \
	|| !sleep_ms(properties, philo, properties->time_to_sleep))
		return (0);
	return (1);
}

int	reflexion_time(t_properties *properties, t_philo *philo)
{
	return (print_state(properties, philo, THINKING));
}

void	*routine(void *arg)
{
	t_philo			*philo;
	t_properties	*properties;

	philo = arg;
	properties = philo->properties;
	while (!properties->start)
		usleep(10);
	while (1)
	{
		if (!take_forks(properties, philo))
			return (NULL);
		if (!just_eat(properties, philo))
			return (NULL);
		restitute_forks(properties, philo);
		if (!night_time(properties, philo))
			return (NULL);
		if (!reflexion_time(properties, philo))
			return (NULL);
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
	// if (get_time() == -1)
	// 	return (free(properties), free_philos(philos), free(threads), 1);
	i = 0;
	while (i < properties->number_of_philosophers)
	{
		pthread_create(threads + i, NULL, routine, philosopher);
		philosopher = philosopher->next;
		i++;
	}
	get_time();
	pthread_mutex_lock(&(properties->checkdeath_mutex));
	properties->start = 1;
	pthread_mutex_unlock(&(properties->checkdeath_mutex));
	while (1)
	{
		if (get_time() - philosopher->last_eat > properties->time_to_die)
			break ;
		philosopher = philosopher->next;
	}
	print_state(properties, philosopher, DIED_EXTERN);
	dprintf(2, "[%d] mutex from MAIN.\n", philosopher->nbr);
	pthread_mutex_lock(&(properties->checkdeath_mutex));
	properties->death = 1;
	pthread_mutex_unlock(&(properties->checkdeath_mutex));
	philosopher = philos;
	i = 0;
	while (i < properties->number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&(properties->print_mutex));
	pthread_mutex_destroy(&(properties->checkdeath_mutex)); // Penser a les destroy en cas de exit anticipe
	return (free(properties), free_philos(philos), free(threads), 0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_putstr_fd(ERRARGS, 2), 1);
	else
		return (philo(argc, argv));
}
