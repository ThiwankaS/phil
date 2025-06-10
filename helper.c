/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 07:23:16 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/10 10:22:42 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

int	init_life(t_rules *rules, t_thread *monitor)
{
	if (pthread_create(monitor, NULL, life, rules) != 0)
		return (1);
	return (0);
}

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
	pthread_join(*monitor, NULL);
	pthread_join(*meal, NULL);
}
