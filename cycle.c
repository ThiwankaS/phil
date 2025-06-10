/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:58:07 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/10 11:07:16 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*mono_philo(t_philo *ph)
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

void	ft_think(t_philo *philo)
{
	size_t	time;
	size_t	die;
	size_t	sleep;
	size_t	eat;
	t_rules	*rules;

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

void	ft_sleep(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	if (get_stop(rules))
		return ;
	print_status(philo, "is sleeping");
	ft_usleep(philo->rules->time_sleep);
}

void	ft_eat(t_philo *philo)
{
	int		first;
	int		second;
	t_rules	*rules;

	rules = philo->rules;
	pick_forks(philo, &first, &second);
	pthread_mutex_lock(&rules->forks[first]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&rules->forks[second]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = getcurrenttime();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, "is eating");
	ft_usleep(rules->time_eat);
	pthread_mutex_unlock(&rules->forks[second]);
	pthread_mutex_unlock(&rules->forks[first]);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo->rules;
	if (rules->nb_philo == 1)
		return (mono_philo(philo));
	if (philo->id % 2)
	{
		print_status(philo, "is thinking");
		ft_usleep(rules->time_eat);
	}
	while (!get_stop(rules) && !get_full(rules))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
