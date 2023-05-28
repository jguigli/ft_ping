/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguigli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:12:26 by jguigli           #+#    #+#             */
/*   Updated: 2021/11/30 15:02:57 by jguigli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbun;

	if (n < 0)
	{
		nbun = -n;
		write(fd, "-", 1);
	}
	else
		nbun = n;
	if (nbun >= 10)
	{
		ft_putnbr_fd(nbun / 10, fd);
		ft_putchar_fd(nbun % 10 + '0', fd);
	}
	else
		ft_putchar_fd(nbun + '0', fd);
}
