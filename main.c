/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 13:58:32 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/10 08:14:58 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_thread	monitor;
	t_thread	meal;
	t_rules		rules;

	if (argc == 5 || argc == 6)
	{
		if (ft_is_valid(argv, argc))
		{
			if (init_rules(&rules, argc, argv))
				return (ft_error("Rules initiating fails!"));
			if (init_life(&rules, &monitor))
				return (ft_error("life thread creating fails!"));
			if (init_phio_routines(&rules, &monitor))
				return (ft_error("philo routine thread creating fails!"));
			if (init_dinning(&rules, &meal, &monitor))
				return (ft_error("dinning thread creating fails!"));
			join_all(&rules, &meal, &monitor);
		}
		else
			return (ft_error("Invalid arguments!"));
	}
	else
		return (ft_error(ERROR));
	return (0);
}
