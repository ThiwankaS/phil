/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:58:02 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/12 06:48:19 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

/**
* Function declaration
*/
int		get_stop(t_rules *rules);
void	set_stop(t_rules *rules);
void	*life(void *arg);

/**
* Thread-safe getter for the simulation stop flag.
*
* Locks the stop mutex, retrieves the value of the `stop` flag from rules,
* and unlocks the mutex before returning the value.
*
* Pointer to the shared simulation rules.
* Return the value of the stop flag (0 or 1).
*/
int	get_stop(t_rules *rules)
{
	int	stop;

	pthread_mutex_lock(&rules->stop_lock);
	stop = rules->stop;
	pthread_mutex_unlock(&rules->stop_lock);
	return (stop);
}

/**
* Thread-safe setter for the simulation stop flag.
*
* Locks the stop mutex, sets the `stop` flag to 1 in rules,
* and then unlocks the mutex.
*
* Pointer to the shared simulation rules.
*/
void	set_stop(t_rules *rules)
{
	pthread_mutex_lock(&rules->stop_lock);
	rules->stop = 1;
	pthread_mutex_unlock(&rules->stop_lock);
}

/**
* Monitor thread function that checks if any philosopher has died.
*
* Loops continuously until the stop flag is set. It checks each philosopher's
* time since their last meal. If the time exceeds the allowed `time_die`,
* and the simulation has not ended due to all philosophers being full,
* it prints the death message and sets the stop flag.
*
* Pointer to the shared simulation rules (cast from void*).
* Always returns NULL.
*/
void	*life(void *arg)
{
	t_rules	*rules;
	size_t	since_meal;
	int		i;

	rules = (t_rules *)arg;
	while (!get_stop(rules))
	{
		i = 0;
		while (i < rules->nb_philo)
		{
			pthread_mutex_lock(&rules->philos[i].meal_lock);
			since_meal = getcurrenttime() - rules->philos[i].last_meal;
			pthread_mutex_unlock(&rules->philos[i].meal_lock);
			if (since_meal > rules->time_die)
			{
				if (!get_full(rules))
					print_status(&rules->philos[i], "died");
				set_stop(rules);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
