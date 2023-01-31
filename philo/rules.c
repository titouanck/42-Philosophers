/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 01:59:18 by tchevrie          #+#    #+#             */
/*   Updated: 2023/01/31 17:17:20 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_rules	micro_to_mili(t_rules rules)
{
	rules.time_to_eat *= 1000;
	rules.time_to_sleep *= 1000;
	rules.start_time = philo_gettimeofday();
	rules.round = malloc(sizeof(t_round));
	if (!(rules.round))
		rules.end = 1;
	else
	{
		rules.round->eat = 0;
		rules.round->philos = 0;
	}
	return (rules);
}

t_rules	philo_rules(char **args, int size)
{
	t_rules	rules;

	rules.end = 1;
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
		rules = micro_to_mili(rules);
	}
	return (rules);
}
