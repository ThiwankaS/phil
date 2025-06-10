/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:55:36 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/10 08:17:14 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>
# include <limits.h>

# define ERROR "Usage: ./philo n_philo time_die time_eat time_sleep [meals]"

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;
typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	int			meals_eaten;
	size_t		last_meal;
	t_thread	thread;
	t_mutex		meal_lock;
	t_rules		*rules;
}	t_philo;

struct s_rules
{
	int		nb_philo;
	int		must_eat;
	int		stop;
	int		full;
	int		done_count;
	t_mutex	*forks;
	t_mutex	print_lock;
	t_mutex	stop_lock;
	t_mutex	done_lock;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	size_t	start_time;
	t_philo	*philos;
};

size_t	getcurrenttime(void);
size_t	ft_strlen(char *str);
int		ft_usleep(size_t m_sec);
void	ft_print(t_philo *philo, const char *msg);
void	print_status(t_philo *philo, const char *msg);

int		init_rules(t_rules *rules, int argc, char **argv);

long	ft_atol(const char *nptr);

int		get_stop(t_rules *rules);
void	set_stop(t_rules *rules);
void	increment_done(t_rules *rules);
void	*life(void *arg);

void	*routine(void *arg);

int		ft_is_valid(char **argv, int argc);

int		ft_error(char *text);

int		get_full(t_rules *rules);
void	set_full(t_rules *rules);
void	*dinning(void *arg);

int		init_life(t_rules *rules, t_thread *monitor);
int		init_dinning(t_rules *rules, t_thread *meal, t_thread *monitor);
int		init_phio_routines(t_rules *rls, t_thread *monitor);
void	join_all(t_rules *rules, t_thread *meal, t_thread *monitor);

#endif
