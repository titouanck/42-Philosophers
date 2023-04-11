/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:17:54 by tchevrie          #+#    #+#             */
/*   Updated: 2023/04/11 14:16:52 by tchevrie         ###   ########.fr       */
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
	long long		number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_think;
	long long		must_eat;
	int				start;
	int				end;
	long long		start_ms;
	int				hungry_philosophers;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	satiety_mutex;
}					t_properties;

typedef struct s_fork
{
	pthread_mutex_t	*mutex;
	int				holder;
}					t_fork;

typedef struct s_philo
{
	t_properties	*properties;
	struct s_philo	*next;
	struct s_philo	*prev;
	int				id;
	int				meals;
	long long		last_eat;
	pthread_mutex_t	last_eat_mutex;
	t_fork			left_fork;
	t_fork			right_fork;
}					t_philo;

/* Colors */

# define RED "\033[31m"
# define NC "\033[0m"

/* Numbers attached to states */

# define L_FORK 0
# define R_FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5
# define DIED_EXTERN 6

/* Error messages */

# define ERRNBR		4815162342

# define ERRARGS	"\
usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

# define ERRALLOC	"philo: could not allocate memory.\n"

/* Time functions */

int				init_time(t_properties *properties);

long long		get_time_us(void);

long long		get_time_ms(void);

void			sleep_ms(unsigned long long sleep_ms);

void			sleep_us(unsigned long long sleep_us);

/* Philosophers functions */

int				print_state(t_properties *properties, t_philo *philo, \
				int state);

t_properties	*define_properties(char **args, int size);

t_philo			*generate_philos(t_properties *properties, int nb);

void			free_philos(t_philo *first, int initialized);

pthread_t		*allocate_threads(int number_of_philosophers);

void			restitute_forks(t_philo *philo);

int				deep_thought(t_properties *properties, t_philo *philo);

int				take_forks(t_properties *properties, t_philo *philo);

int				just_eat(t_properties *properties, t_philo *philo);

int				night_time(t_properties *properties, t_philo *philo);

void			*routine(void *arg);

void			*lonely_routine(void *arg);

void			free_properties(t_properties *properties);

void			check_death(t_properties *properties, t_philo *philo);

int				create_threads(t_properties *properties, t_philo *philo, \
				pthread_t *threads);

int				join_threads(t_properties *properties, pthread_t *threads);

/* Utility functions */

long long		atoi_spe(const char *str);

size_t			ft_putstr_fd(const char *str, int fd);

#endif
