/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguigli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:32:31 by jguigli           #+#    #+#             */
/*   Updated: 2021/12/02 19:24:56 by jguigli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_case_rep(int n)
{
	int				count;
	unsigned int	nbun;

	if (n <= 0)
	{
		count = 1;
		nbun = -n;
	}
	else
	{
		count = 0;
		nbun = n;
	}
	while (nbun != 0)
	{
		nbun /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int				count;
	char			*rep;
	unsigned int	val;

	count = ft_count_case_rep(n);
	rep = (char *)malloc(sizeof(char) * (count + 1));
	if (rep == NULL)
		return (NULL);
	if (n < 0)
	{
		val = -n;
		rep[0] = '-';
	}
	else
		val = n;
	rep[count] = '\0';
	while (val >= 10)
	{
		rep[--count] = (val % 10) + '0';
		val /= 10;
	}
	rep[--count] = (val % 10) + '0';
	return (rep);
}
