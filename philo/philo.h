/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevrie <tchevrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:17:54 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/31 01:43:17 by tchevrie         ###   ########.fr       */
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
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_think;
	int				must_eat;
	int				start;
	int				end;
	long			start_ms;
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
	long			last_eat;
	pthread_mutex_t	last_eat_mutex;
	t_fork			left_fork;
	t_fork			right_fork;
}					t_philo;

/* Colors */

# define RED "\033[31m"
# define NC "\033[0m"

/* Numbers attached to states */

# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5
# define DIED_EXTERN 6
# define L_FORK 7
# define R_FORK 8

/* Error messages */

# define ERRNBR		4815162342

# define ERRARGS	"usage: ./philo number_of_philosophers time_to_die " \
					"time_to_eat time_to_sleep " \
					"[number_of_times_each_philosopher_must_eat]\n"

# define ERRALLOC	"philo: could not allocate memory.\n"

/* Time functions */

int				init_time(t_properties *properties);

long			get_time_us(void);
long			get_time_ms(void);

/* Philosophers functions */

int				print_state(t_properties *properties, t_philo *philo, \
				int state);

long			atoi_spe(const char *str);

t_properties	*define_properties(char **args, int size);

t_philo			*generate_philos(t_properties *properties, int nb);

void			free_philos(t_philo *first);

pthread_t		*thread_philos(int number_of_philosophers);

void			restitute_forks(t_properties *properties, t_philo *philo);

int				deep_thought(t_properties *properties, t_philo *philo);

void			sleep_ms(unsigned long sleep_ms);
void			sleep_us(unsigned long sleep_us);
// void			sleep_ms(long sleep_ms);
// int				sleep_ms(t_properties *properties, t_philo *philo, long sleep_ms);

void			restitute_forks(t_properties *properties, t_philo *philo);

int				take_forks(t_properties *properties, t_philo *philo);

int				just_eat(t_properties *properties, t_philo *philo);

int				night_time(t_properties *properties, t_philo *philo);

void			*routine(void *arg);

void			*lonely_routine(void *arg);

/* Libft functions */

size_t			ft_strlen(const char *s);

size_t			ft_putstr_fd(const char *str, int fd);

#endif
