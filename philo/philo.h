/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:22:46 by tchevrie          #+#    #+#             */
/*   Updated: 2023/02/21 15:43:27 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define ERRNBR 4815162342
# define ERRARGS "usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define ERRALLOC "philo: could not allocate memory.\n"

typedef struct t_properties
{
	long	number_of_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	must_eat;
	long	start;
}			t_properties;

typedef struct s_philo {
	int				nbr;
	int				meals;
	long			last_eat;
	pthread_mutex_t	fork;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

// utils.c
void			ft_swap(int *a, int *b);
void			ft_putstr_fd(char const *s, int fd);
long			ft_atoi_check(const char *str);

// properties.c
t_properties	*define_properties(char **args, int size);

// time.c
long			get_current_time(void);
int				time_initialisation(t_properties *properties, t_philo *first);

// generate_philos.c
void			free_philos(t_philo *first);
t_philo			*generate_philos(int nb);
pthread_t		*thread_philos(int number_of_philosophers);

#endif