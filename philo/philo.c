/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:26:58 by tchevrie          #+#    #+#             */
/*   Updated: 2023/01/27 23:03:35 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo(char **args, int size)
{
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc < 5)
		return (ft_putstr_fd(ERR_NOTENOUGHARGS, 2), 1);
	else
		return (!philo(argv + 1, argc - 1));
}
