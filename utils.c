/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:08:52 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/10 01:21:56 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

size_t getcurrenttime(void)
{
	t_timeval	time;
	size_t		m_sec;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	m_sec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (m_sec);
}

int ft_usleep(size_t m_sec)
{
	size_t	time;

	time = getcurrenttime();
	while (getcurrenttime() - time < m_sec)
		usleep(500);
	return (1);
}

void	ft_print(t_philo *philo, const char *msg)
{
	size_t	time;
	int		id;

	id = philo->id;
	time = getcurrenttime() - philo->rules->start_time;
	printf("%ld %d %s\n", time, id, msg);
}

void print_status(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->rules->print_lock);
	if (!get_stop(philo->rules))
		ft_print(philo, msg);
	pthread_mutex_unlock(&philo->rules->print_lock);
}
