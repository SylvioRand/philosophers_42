/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srandria <srandria@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 07:28:28 by srandria          #+#    #+#             */
/*   Updated: 2024/12/17 07:32:06 by srandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if(nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if(nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if(nb > 9)
	{
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
	}
}
