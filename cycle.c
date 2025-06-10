/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:58:07 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/10 07:43:51 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *mono_philo(t_philo *ph)
{
	int		first;
	t_rules	*rules;

	rules = ph->rules;
	first = ph->left_fork;
	pthread_mutex_lock(&rules->forks[first]);
	print_status(ph, "has taken a fork");
	pthread_mutex_unlock(&rules->forks[first]);
	ft_usleep(rules->time_die);
	print_status(ph, "died");
	set_stop(rules);
	return (NULL);
}

void ft_think(t_philo *philo)
{
	size_t time;
	size_t die;
	size_t sleep;
	size_t eat;
	t_rules *rules;

	rules = philo->rules;
	die = rules->time_die;
	eat = rules->time_eat;
	sleep = rules->time_sleep;
	time = die - sleep - eat;
	if (get_stop(rules))
		return ;
	if (get_full(rules))
		return ;
	print_status(philo, "is thinking");
	if (time > 0)
		ft_usleep(time);
}

void ft_sleep(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	if (get_stop(rules))
		return ;
	print_status(philo, "is sleeping");
	ft_usleep(philo->rules->time_sleep);
}

void ft_eat(t_philo *ph)
{
	int	first;
	int	second;
	t_rules *rules;

	rules = ph->rules;
	if (ph->left_fork < ph->right_fork)
	{
		first = ph->left_fork;
		second = ph->right_fork;
	}
	else
	{
		first = ph->right_fork;
		second = ph->left_fork;
	}
	pthread_mutex_lock(&rules->forks[first]);
	print_status(ph, "has taken a fork");
	pthread_mutex_lock(&rules->forks[second]);
	print_status(ph, "has taken a fork");
	print_status(ph, "is eating");
	ft_usleep(rules->time_eat);
	pthread_mutex_lock(&ph->meal_lock);
	ph->last_meal = getcurrenttime();
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->meal_lock);
	pthread_mutex_unlock(&rules->forks[second]);
	pthread_mutex_unlock(&rules->forks[first]);
}

void *routine(void *arg)
{
	t_philo	*ph;
	t_rules	*rules;

	ph = (t_philo *)arg;
	rules = ph->rules;
	if (rules->nb_philo == 1)
		return (mono_philo(ph));
	if (ph->id % 2)
	{
		print_status(ph, "is thinking");
		ft_usleep(rules->time_eat);
	}
	while (!get_stop(rules) && !get_full(rules))
	{
		ft_eat(ph);
		ft_sleep(ph);
		ft_think(ph);
	}
	return (NULL);
}
