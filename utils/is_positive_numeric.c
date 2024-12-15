/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_positive_numeric.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:43:11 by srandria          #+#    #+#             */
/*   Updated: 2024/12/12 09:57:58 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_positive_numeric(char *token)
{
	if (token == NULL)
		return (0);
	if (*token == '\0')
		return (0);
	while (*token)
	{
		if (*token < '0' || *token > '9')
			return (0);
		token++;
	}
	return (1);
}
