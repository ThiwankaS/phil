/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:58:02 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/10 05:28:46 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int get_stop(t_rules *rules)
{
	int stop;
	pthread_mutex_lock(&rules->stop_lock);
	stop = rules->stop;
	pthread_mutex_unlock(&rules->stop_lock);
	return stop;
}

void set_stop(t_rules *rules)
{
	pthread_mutex_lock(&rules->stop_lock);
	rules->stop = 1;
	pthread_mutex_unlock(&rules->stop_lock);
}

void increment_done(t_rules *rules)
{
	pthread_mutex_lock(&rules->done_lock);
	rules->done_count++;
	if (rules->done_count == rules->nb_philo)
		set_stop(rules);
	pthread_mutex_unlock(&rules->done_lock);
}

void *monitor_routine(void *arg)
{
	t_rules *rules;
	size_t since_meal;
	int i;

	rules = (t_rules *)arg;
	while (!get_stop(rules))
	{
		i = 0;
		while(i < rules->nb_philo)
		{
			pthread_mutex_lock(&rules->philos[i].meal_lock);
			since_meal = getcurrenttime() - rules->philos[i].last_meal;
			if (since_meal > rules->time_die)
			{
				if (!get_full(rules))
					print_status(&rules->philos[i], "died");
				set_stop(rules);
			}
			pthread_mutex_unlock(&rules->philos[i].meal_lock);
			i++;
		}
	}
	return NULL;
}
