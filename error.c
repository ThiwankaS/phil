/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 01:13:53 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/12 06:48:35 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

/**
* Function declaration
*/
int	ft_error(char *text);
int	exit_err(t_rules *rules, char *msg);
int	exit_clr(t_rules *rules, char *msg);

/**
* Displays an error message to standard error output
* Prepends and appends formatting around the provided error text
* Returns 1 after writing the message
*/
int	ft_error(char *text)
{
	size_t	len;

	len = ft_strlen(text);
	write(2, " ERROR : [ ", 11);
	write(2, text, len);
	write(2, " ]\n", 3);
	return (1);
}

/**
* Frees allocated forks and philosophers if they exist,
* then prints the provided error message and returns an error code.
*/
int	exit_err(t_rules *rules, char *msg)
{
	if (rules->forks)
		clean_forks(rules);
	if (rules->philos)
		clean_philos(rules);
	return (ft_error(msg));
}

/**
* Performs full cleanup of all allocated resources,
* then prints the provided error message and returns an error code.
*/
int	exit_clr(t_rules *rules, char *msg)
{
	ft_cleanup(rules);
	return (ft_error(msg));
}
