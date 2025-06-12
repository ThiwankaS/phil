/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:08:52 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/12 06:49:31 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

/**
* Function declaration
*/
size_t	ft_strlen(char *str);
size_t	getcurrenttime(void);
int		ft_usleep(size_t m_sec);
void	ft_print(t_philo *philo, const char *msg);
void	print_status(t_philo *philo, const char *msg);

/**
* Calculates the length of a null-terminated string
* Returns the number of characters before the null terminator
* Safely handles a NULL pointer by returning 0
*/
size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

/**
* Returns the current system time in milliseconds.
* Uses gettimeofday to calculate time in ms since the epoch.
* Returns 0 if gettimeofday fails.
*/
size_t	getcurrenttime(void)
{
	t_timeval	time;
	size_t		m_sec;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	m_sec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (m_sec);
}

/**
* Custom sleep function that pauses execution for the specified
* number of milliseconds.
* Uses getcurrenttime to loop-check the elapsed time and calls usleep
* in small intervals.
* Returns 1 when the delay has completed.
*/
int	ft_usleep(size_t m_sec)
{
	size_t	time;

	time = getcurrenttime();
	while (getcurrenttime() - time < m_sec)
		usleep(500);
	return (1);
}

/**
* Prints the current timestamp, philosopher ID, and a message to stdout.
* The timestamp is relative to the simulation start time.
*/
void	ft_print(t_philo *philo, const char *msg)
{
	size_t	time;
	int		id;

	id = philo->id;
	time = getcurrenttime() - philo->rules->start_time;
	printf("%ld %d %s\n", time, id, msg);
}

/**
* Prints a status message in a thread-safe way.
* Locks the print mutex, checks if the simulation has not stopped,
* and then calls ft_print.
*/
void	print_status(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->rules->print_lock);
	if (!get_stop(philo->rules))
		ft_print(philo, msg);
	pthread_mutex_unlock(&philo->rules->print_lock);
}
