/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:58:07 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/17 05:33:27 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

/**
* Function declaration
*/
void	*mono_philo(t_philo *ph);
void	ft_think(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_eat(t_philo *philo);
void	*routine(void *arg);

/**
* Handles the case when there is only one philosopher.
* Takes one fork, waits until the philosopher dies, then prints death
* and sets stop flag.
*/
void	*mono_philo(t_philo *ph)
{
	int		first;
	t_rules	*rules;

	rules = ph->rules;
	first = ph->left_fork;
	pthread_mutex_lock(&rules->forks[first]);
	print_status(ph, "has taken a fork");
	pthread_mutex_unlock(&rules->forks[first]);
	ft_usleep(rules->time_die, rules);
	print_status(ph, "died");
	set_stop(rules);
	return (NULL);
}

/**
* Prints that the philosopher is thinking and optionally waits for
* a calculated amount of time.
* The wait helps avoid early starvation based on the time to eat and sleep.
*/
void	ft_think(t_philo *philo)
{
	int		time;
	size_t	die;
	size_t	sleep;
	size_t	eat;
	t_rules	*rules;

	rules = philo->rules;
	die = rules->time_die;
	eat = rules->time_eat;
	sleep = rules->time_sleep;
	time = (int)(die - sleep - eat - 10);
	if (get_stop(rules))
		return ;
	if (get_full(rules))
		return ;
	print_status(philo, "is thinking");
	if (time > 0)
		ft_usleep(time, rules);
}

/**
* Prints that the philosopher is sleeping and then sleeps
* for the defined time.
*/
void	ft_sleep(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	if (get_stop(rules))
		return ;
	print_status(philo, "is sleeping");
	ft_usleep(philo->rules->time_sleep, rules);
}

/**
* Handles the eating cycle for a philosopher.
* Locks both forks, updates meal data, simulates eating,
* then unlocks the forks.
*/
void	ft_eat(t_philo *philo)
{
	int		first;
	int		second;
	t_rules	*rules;
	size_t	time;

	rules = philo->rules;
	pick_forks(philo, &first, &second);
	if (pick_first_fork(rules, first))
		return ;
	print_status(philo, "has taken a fork");
	if (pick_second_fork(rules, first, second))
		return ;
	print_status(philo, "has taken a fork");
	time = getcurrenttime();
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = time;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, "is eating");
	ft_usleep(rules->time_eat, rules);
	pthread_mutex_unlock(&rules->forks[second]);
	pthread_mutex_unlock(&rules->forks[first]);
}

/**
* Main routine function executed by each philosopher thread.
* If only one philosopher exists, runs the mono_philo function.
* Otherwise, cycles through eating, sleeping, and thinking while
* the simulation runs.
*/
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
		ft_usleep(rules->time_eat, rules);
	}
	while (!get_stop(rules) && !get_full(rules))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
