/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:12:43 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/01 17:34:57 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_waitline(t_rules rules)
{
	t_waitingline *current;
	int	i;

	if (rules.waitl)
		current = rules.waitl->next;
	i = 0;
	while (current && i < rules.number_of_philosophers)
	{
		printf("%d -> ", current->nbr);
		current = current->prev;
		i++;
	}
	printf("\n");
}

void	swap_waitline(t_rules rules)
{
	t_waitingline *current;
	
	current = rules.waitl;
	if (rules.number_of_philosophers < 3)
		return ;
	ft_swap(&(current->next->nbr), &(current->next->next->nbr));
}

void	back_to_the_end(t_rules rules)
{
	if (rules.number_of_philosophers < 2)
		return ;
	rules.waitl->next = rules.waitl->next->next;	
}
