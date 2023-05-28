/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguigli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:59:24 by jguigli           #+#    #+#             */
/*   Updated: 2021/12/07 13:39:45 by jguigli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*ptsrc;
	unsigned char		*ptdest;

	ptsrc = src;
	ptdest = dest;
	if (ptsrc < ptdest)
	{
		while (n)
		{
			ptdest[n - 1] = ptsrc[n - 1];
			n--;
		}
	}
	else if (ptdest < ptsrc)
	{
		i = -1;
		while (++i < n)
			ptdest[i] = ptsrc[i];
	}
	return (dest);
}
