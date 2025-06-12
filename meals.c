/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:09:36 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/13 02:02:24 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

/**
* Function declaration
*/
int		get_full(t_rules *rules);
int		pick_first_fork(t_rules *rules, int first);
int		pick_second_fork(t_rules *rules, int first, int second);
void	set_full(t_rules *rules);
void	*dinning(void *arg);

/**
* Returns the value of the 'full' flag in a thread-safe way.
* Indicates whether all philosophers have eaten the required number of times.
*/
int	get_full(t_rules *rules)
{
	int	full;

	pthread_mutex_lock(&rules->done_lock);
	full = rules->full;
	pthread_mutex_unlock(&rules->done_lock);
	return (full);
}

/**
* Sets the 'full' flag to 1 in a thread-safe way.
* Marks that all philosophers have completed their required meals.
*/
void	set_full(t_rules *rules)
{
	pthread_mutex_lock(&rules->done_lock);
	rules->full = 1;
	pthread_mutex_unlock(&rules->done_lock);
}

/**
* Thread function that monitors philosophers' meal counts.
* If all philosophers have eaten the required number of times,
* it sets the 'full' flag to signal completion.
*/
void	*dinning(void *arg)
{
	t_rules	*rules;
	int		completed;
	int		i;

	rules = (t_rules *)arg;
	while (!get_stop(rules) && !get_full(rules))
	{
		i = 0;
		completed = 0;
		while (i < rules->nb_philo)
		{
			pthread_mutex_lock(&rules->philos[i].meal_lock);
			if (rules->philos[i].meals_eaten == rules->must_eat)
				completed++;
			pthread_mutex_unlock(&rules->philos[i].meal_lock);
			i++;
		}
		if (rules->must_eat != -1 && completed == rules->nb_philo)
			set_full(rules);
	}
	return (NULL);
}

/**
* Attempts to pick up the first fork if the simulation has not stopped
* or completed.
* Locks the corresponding fork mutex and returns 0 on success, 1 otherwise.
*/
int	pick_first_fork(t_rules *rules, int first)
{
	if (get_stop(rules))
		return (1);
	if (get_full(rules))
		return (1);
	pthread_mutex_lock(&rules->forks[first]);
	return (0);
}

/**
* Attempts to pick up the second fork if the simulation has not stopped
* or completed.
* If the attempt fails, the first fork is unlocked to avoid deadlocks.
* Returns 0 on success, 1 otherwise.
*/
int	pick_second_fork(t_rules *rules, int first, int second)
{
	if (get_stop(rules))
	{
		pthread_mutex_unlock(&rules->forks[first]);
		return (1);
	}
	if (get_full(rules))
	{
		pthread_mutex_unlock(&rules->forks[first]);
		return (1);
	}
	pthread_mutex_lock(&rules->forks[second]);
	return (0);
}
