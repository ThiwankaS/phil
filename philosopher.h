/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:55:36 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/10 00:53:15 by tsomacha         ###   ########.fr       */
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

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;
typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	size_t		last_meal;
	int			meals_eaten;
	t_thread	thread;
	t_mutex		meal_lock;
	t_rules		*rules;
}	t_philo;

struct s_rules
{
	int nb_philo;
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	int		must_eat;
	int		stop;
	int		done_count;
	t_mutex	*forks;
	t_mutex	print_lock;
	t_mutex	stop_lock;
	t_mutex	done_lock;
	size_t	start_time;
	t_philo	*philos;
};

size_t	getcurrenttime(void);
int		ft_usleep(size_t m_sec);
void	ft_print(t_philo *philo, const char *msg);
void	print_status(t_philo *philo, const char *msg);

int		init_rules(t_rules *rules, int argc, char **argv);

long	ft_atol(const char *nptr);

int		get_stop(t_rules *rules);
void	set_stop(t_rules *rules);
void	increment_done(t_rules *rules);
void	*monitor_routine(void *arg);

void	*philo_routine(void *arg);

#endif
