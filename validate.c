/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 01:08:06 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/12 06:49:40 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

/**
* Function declaration
*/
int	ft_is_valid(char **argv, int argc);

/**
* Validates the input arguments for the dining philosophers program
* Converts all arguments to long and stores in an array
* Sets default value for optional fifth argument if not provided
* Checks if the number of philosophers is valid value
* Ensures time-related arguments are non-negative and within INT_MAX
* Validates the optional "number of meals" argument if present
* Returns 1 if all checks pass, otherwise returns 0
*/
int	ft_is_valid(char **argv, int argc)
{
	long	args[5];
	int		i;

	i = 1;
	args[0] = ft_atol(argv[1]);
	args[1] = ft_atol(argv[2]);
	args[2] = ft_atol(argv[3]);
	args[3] = ft_atol(argv[4]);
	if (argc == 6)
		args[4] = ft_atol(argv[5]);
	else
		args[4] = 1;
	if (args[0] < 1)
		return (0);
	while (i < 4)
	{
		if (args[i] < 0 || args[i] > INT_MAX)
			return (0);
		i++;
	}
	if (args[4] < 1 || args[4] > INT_MAX)
		return (0);
	return (1);
}
