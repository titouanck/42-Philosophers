/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:45:10 by tchevrie          #+#    #+#             */
/*   Updated: 2023/01/30 13:28:12 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_rules
{
	int		err;
	long	number_of_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	must_eat;
}		t_rules;

typedef struct s_philo
{
	t_rules			*rules;
	int				nbr;
	int				eat;
	int				sleep;
	int				fork;
	struct s_philo	*prev;
	struct s_philo	*next;
}					t_philo;

# define ERRNBR 4815162342
# define UNDEFINED -4815162342

# define ERR_ALLOC "philo: could not allocate memory.\n"
# define ERR_TOOSMALLVALUE "philo: the given value is too small\n"

# define ERR_NOTENOUGHARGS "usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define ERR_TOOMANYARGS "usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define ERR_WRONGTYPEARGS "usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

/* Colors */
# define RED "\033[0;31m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define WHITE "\033[37m"
# define MAGENTA "\033[35m"
# define ENDCL "\033[0m"

// utils.c
void		ft_putstr_fd(char const *s, int fd);
long		ft_atoi_check(const char *str);

// operations.c
int			just_eat(t_philo *philo);
void		just_sleep(t_philo *philo);
void		just_think(t_philo *philo);

// rules.c
t_rules		philo_rules(char **args, int size);

// philos_alloc.c
t_philo		*create_philos(int nbr, t_rules *rules);
void		free_philos(t_philo *first);
pthread_t	*thread_philos(int number_of_philosophers);

#endif
