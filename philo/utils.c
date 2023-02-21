/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:50:15 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/21 13:22:38 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_putstr_fd(char const *s, int fd)
{
	size_t	i;

	if (!s || fd == -1)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

static long	ft_atoi_check_bis(const char *str, int i, long nbr, long sign)
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

long	ft_atoi_check(const char *str)
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
	return (ft_atoi_check_bis(str, i, nbr, sign));
}
