/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:58:32 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/10 01:32:43 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main(int argc, char **argv)
{
	t_thread	monitor;
	t_rules		rules;
	int	i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		if (ft_is_valid(argv, argc))
		{
			if (init_rules(&rules, argc, argv))
				return (1);
			while (i < rules.nb_philo)
			{
				pthread_create(&rules.philos[i].thread, NULL, philo_routine, &rules.philos[i]);
				i++;
			}
			pthread_create(&monitor, NULL, monitor_routine, &rules);
			i = 0;
			while (i < rules.nb_philo)
			{
				pthread_join(rules.philos[i].thread, NULL);
				i++;
			}
			pthread_join(monitor, NULL);
		}
		else
			return (ft_error("Invalid arguments!"));
	}
	else
		return (ft_error(ERROR));
	return (0);
}
