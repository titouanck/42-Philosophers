/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_spe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:31:56 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/29 16:41:19 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	_bis(const char *str, int i, long nbr, long sign)
{
	while ('0' <= str[i] && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		if ((nbr * sign) > 2147483647 || (nbr * sign) < -2147483648)
			return (ERRNBR);
		i++;
	}
	if (str[i])
		return (ERRNBR);
	return (nbr * sign);
}

long	atoi_spe(const char *str)
{
	long		nbr;
	long		sign;
	size_t		i;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	return (_bis(str, i, nbr, sign));
}
