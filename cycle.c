/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:58:07 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/08 16:34:39 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void ft_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void ft_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->rules->time_sleep);
}

void *philo_routine(void *arg)
{
	t_philo	*ph = (t_philo *)arg;
	t_rules	*rules = ph->rules;

	if (ph->id % 2)
	{
		print_status(ph, "is thinking");
		ft_usleep(rules->time_eat);
	}
	while (!get_stop(rules))
	{
		int first = ph->left_fork < ph->right_fork ? ph->left_fork : ph->right_fork;
		int second = ph->left_fork > ph->right_fork ? ph->left_fork : ph->right_fork;
		pthread_mutex_lock(&rules->forks[first]);
		print_status(ph, "has taken a fork");
		pthread_mutex_lock(&rules->forks[second]);
		print_status(ph, "has taken a fork");
		print_status(ph, "is eating");
		pthread_mutex_lock(&ph->meal_lock);
		ph->last_meal = getcurrenttime();
		ph->meals_eaten++;
		pthread_mutex_unlock(&ph->meal_lock);
		ft_usleep(rules->time_eat);
		pthread_mutex_unlock(&rules->forks[second]);
		pthread_mutex_unlock(&rules->forks[first]);
		if (rules->must_eat != -1 && ph->meals_eaten >= rules->must_eat && !ph->done)
		{
			ph->done = 1;
			increment_done(rules);
		}
		ft_sleep(ph);
		ft_think(ph);
	}
	return NULL;
}
