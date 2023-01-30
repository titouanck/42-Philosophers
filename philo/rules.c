/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 01:59:18 by tchevrie          #+#    #+#             */
/*   Updated: 2023/01/30 02:29:05 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rules philo_rules(char **args, int size)
{
	t_rules	rules;

	rules.err = 1;
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
	else if (rules.number_of_philosophers < 1 || rules.time_to_die < 0 \
	|| rules.time_to_eat < 1 \
	|| rules.must_eat != UNDEFINED && rules.must_eat < 1)
		ft_putstr_fd(ERR_TOOSMALLVALUE, 2);
	else
		rules.err = 0;
	return (rules);
}
