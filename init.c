/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:58:18 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/10 10:48:46 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	init_rules_lock(t_rules *rules)
{
	if (pthread_mutex_init(&rules->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&rules->stop_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&rules->print_lock);
		return (1);
	}
	if (pthread_mutex_init(&rules->done_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&rules->print_lock);
		pthread_mutex_destroy(&rules->stop_lock);
		return (1);
	}
	return (0);
}

static int	init_meal_locks(t_philo *philos, int *index)
{
	int	i;
	int	j;

	i = *index;
	if (pthread_mutex_init(&philos[i].meal_lock, NULL) != 0)
	{
		j = 0;
		while (j < i)
		{
			pthread_mutex_destroy(&philos[j].meal_lock);
			j++;
		}
		return (1);
	}
	return (0);
}

t_mutex	*ft_set_froks(int size)
{
	int		i;
	int		j;
	t_mutex	*forks;

	i = 0;
	forks = malloc(sizeof(t_mutex) * size);
	if (!forks)
		return (NULL);
	while (i < size)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&forks[j]);
				j++;
			}
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

t_philo	*ft_set_philos(t_rules *rules, int size)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * size);
	if (!philos)
		return (NULL);
	while (i < size)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % rules->nb_philo;
		philos[i].last_meal = rules->start_time;
		philos[i].meals_eaten = 0;
		if (init_meal_locks(philos, &i))
		{
			free(philos);
			return (NULL);
		}
		philos[i].rules = rules;
		i++;
	}
	return (philos);
}

int	init_rules(t_rules *rules, int argc, char **argv)
{
	rules->nb_philo = ft_atol(argv[1]);
	rules->time_die = ft_atol(argv[2]);
	rules->time_eat = ft_atol(argv[3]);
	rules->time_sleep = ft_atol(argv[4]);
	if (argc == 6)
		rules->must_eat = ft_atol(argv[5]);
	else
		rules->must_eat = -1;
	rules->stop = 0;
	rules->full = 0;
	rules->done_count = 0;
	rules->start_time = getcurrenttime();
	rules->forks = ft_set_froks(rules->nb_philo);
	rules->philos = ft_set_philos(rules, rules->nb_philo);
	if (!rules->forks || !rules->philos)
		return (1);
	if (init_rules_lock(rules))
		return (1);
	return (0);
}
