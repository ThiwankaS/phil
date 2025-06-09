/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 01:13:53 by tsomacha          #+#    #+#             */
/*   Updated: 2025/06/10 01:15:17 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * Function declaration
*/
int	ft_error(char *text);

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
