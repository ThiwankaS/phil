/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:58:13 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/10 15:55:45 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * Function declaration
*/
void	clean_forks(t_rules *rules);
void	clean_philos(t_rules *rules);
void	ft_cleanup(t_rules *rules);

void	clean_forks(t_rules *rules)
{
	int		i;
	t_mutex	*forks;

	i = 0;
	forks = rules->forks;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(rules->forks);
}

void	clean_philos(t_rules *rules)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = rules->philos;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&ph[i].meal_lock);
		i++;
	}
	free(rules->philos);
}

void	ft_cleanup(t_rules *rules)
{
	if (rules->forks)
		clean_forks(rules);
	if (rules->philos)
		clean_philos(rules);
	pthread_mutex_destroy(&rules->print_lock);
	pthread_mutex_destroy(&rules->stop_lock);
	pthread_mutex_destroy(&rules->done_lock);
}
