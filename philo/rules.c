/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 01:59:18 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/01 17:26:39 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_waitline(t_rules rules)
{
	t_waitingline	*first;
	t_waitingline	*current;
	size_t			i;

	rules.waitl->nbr = 0;
	rules.waitl->next = NULL;
	rules.waitl->prev = NULL;
	current = rules.waitl;
	first = NULL;
	i = 1;
	while (i <= rules.number_of_philosophers)
	{
		if (i % 2 != 0)
		{
			current->next = malloc(sizeof(t_waitingline));
			if (!(current->next))
				return (ft_putstr_fd(ERR_ALLOC, 2), free_rules(rules), 0);
			if (!first)
				first = current->next;
			current->next->prev = current;
			current = current->next;
			current->nbr = i;
		}
		i++;
	}
	i = 2;
	while (i <= rules.number_of_philosophers)
	{
		if (i % 2 == 0)
		{
			current->next = malloc(sizeof(t_waitingline));
			if (!(current->next))
				return (ft_putstr_fd(ERR_ALLOC, 2), free_rules(rules), 0);
			current->next->prev = current;
			current = current->next;
			current->nbr = i;
		}
		i++;
	}
	current->next = first;
	first->prev = current;
	rules.waitl->next = first;
	rules.waitl->prev = first;
	return (1);
}

static t_rules	rules_conversion_and_initialisation(t_rules rules)
{
	rules.time_to_eat *= 1000;
	rules.time_to_sleep *= 1000;
	if (rules.number_of_philosophers > 1)
	{
		rules.waitl = malloc(sizeof(t_waitingline));
		if (!(rules.waitl))
			rules.end = -1;
		else
			create_waitline(rules);
	}
	else
		rules.waitl = NULL;
	rules.start_time = philo_gettimeofday();
	return (rules);
}

void	free_rules(t_rules rules)
{
	printf(RED"Fonction free_rules() pas encore implemente\n"ENDCL);
}

t_rules	philo_rules(char **args, int size)
{
	t_rules	rules;

	rules.end = -1;
	rules.number_of_philosophers = ft_atoi_check(args[0]);
	rules.time_to_die = ft_atoi_check(args[1]);
	rules.time_to_eat = ft_atoi_check(args[2]);
	rules.time_to_sleep = ft_atoi_check(args[3]);
	if (size > 4)
		rules.must_eat = ft_atoi_check(args[4]);
	else
		rules.must_eat = UNDEFINED;
	if (rules.number_of_philosophers == ERRNBR || rules.time_to_die == ERRNBR \
	|| rules.time_to_eat == ERRNBR || rules.time_to_sleep == ERRNBR \
	|| rules.must_eat == ERRNBR)
		ft_putstr_fd(ERR_WRONGTYPEARGS, 2);
	else if (rules.number_of_philosophers < 0 || rules.time_to_die < 0 \
	|| rules.time_to_eat < 0 || rules.time_to_sleep < 0 \
	|| rules.must_eat != UNDEFINED && rules.must_eat < 0)
		ft_putstr_fd(ERR_TOOSMALLVALUE, 2);
	else
	{
		rules.end = 0;
		rules = rules_conversion_and_initialisation(rules);
	}
	return (rules);
}
