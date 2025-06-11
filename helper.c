/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 07:23:16 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/11 10:44:01 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
* Function declaration
*/
int		pick_forks(t_philo *philo, int *first, int *second);
int		init_life(t_rules *rules, t_thread *monitor);
int		init_dinning(t_rules *rules, t_thread *meal, t_thread *monitor);
int		init_phio_routines(t_rules *rules, t_thread *monitor);
void	join_all(t_rules *rules, t_thread *meal, t_thread *monitor);

/**
* Determines the order in which a philosopher should pick up forks
* to prevent deadlocks. The lower-numbered fork is picked up first.
*/
int	pick_forks(t_philo *philo, int *first, int *second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	return (0);
}

/**
* Initializes and starts the life monitoring thread.
* Returns 0 on success, or 1 on failure.
*/
int	init_life(t_rules *rules, t_thread *monitor)
{
	if (pthread_create(monitor, NULL, life, rules) != 0)
		return (1);
	return (0);
}

/**
* Starts the meal-checking thread. If it fails, joins all philosopher
* and monitor threads.
* Returns 0 on success, or 1 on failure.
*/
int	init_dinning(t_rules *rules, t_thread *meal, t_thread *monitor)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = rules->philos;
	if (pthread_create(meal, NULL, dinning, rules) != 0)
	{
		while (i < rules->nb_philo)
		{
			pthread_join(ph[i].thread, NULL);
			i++;
		}
		pthread_join(*monitor, NULL);
		return (1);
	}
	return (0);
}

/**
* Creates and starts all philosopher threads.
* If any thread creation fails, joins all previously created threads
* and the monitor thread.
* Returns 0 on success, or 1 on failure.
*/
int	init_phio_routines(t_rules *rules, t_thread *monitor)
{
	int		i;
	int		j;
	t_philo	*ph;

	i = 0;
	ph = rules->philos;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&ph[i].thread, NULL, routine, &ph[i]) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_join(ph[j].thread, NULL);
				j++;
			}
			pthread_join(*monitor, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
* Waits for all philosopher, monitor, and meal-checking threads to finish.
*/
void	join_all(t_rules *rules, t_thread *meal, t_thread *monitor)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = rules->philos;
	while (i < rules->nb_philo)
	{
		pthread_join(ph[i].thread, NULL);
		i++;
	}
	pthread_join(*meal, NULL);
	pthread_join(*monitor, NULL);
}
