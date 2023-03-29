/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:25:45 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/29 16:28:39 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_putstr_fd(const char *str, int fd)
{
	if (!str)
		return (write(fd, "(null)", 6));
	else
		return (write(fd, str, ft_strlen(str)));
}
