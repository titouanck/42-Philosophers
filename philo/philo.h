/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:17:54 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/29 18:47:14 by tchevrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* Includes and types */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct t_properties
{
	pthread_mutex_t	print_mutex;
	long			number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	int				death;
}					t_properties;

typedef struct s_philo
{
	int				nbr;
	int				meals;
	long			last_eat;
	pthread_mutex_t	fork;
	struct s_philo	*next;
	struct s_philo	*prev;
	t_properties	*properties;
	int				fork_hodler;
}					t_philo;

/* Numbers attached to states */

# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5

/* Error messages */

# define ERRNBR	4815162342
# define ERRARGS	"usage: ./philo number_of_philosophers time_to_die " \
					"time_to_eat time_to_sleep " \
					"[number_of_times_each_philosopher_must_eat]\n"
# define ERRALLOC "philo: could not allocate memory.\n"

/* Philosophers functions */

long			get_time(void);

int				print_state(t_properties *properties, t_philo *philo, \
				int state);

long			atoi_spe(const char *str);

t_properties	*define_properties(char **args, int size);

t_philo			*generate_philos(t_properties *properties, int nb);

void			free_philos(t_philo *first);

pthread_t		*thread_philos(int number_of_philosophers);

void			check_death(t_properties *properties, t_philo *philo);

void			restitute_forks(t_properties *properties, t_philo *philo);

/* Libft functions */

size_t			ft_strlen(const char *s);

size_t			ft_putstr_fd(const char *str, int fd);

#endif
