/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguigli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:30:32 by jguigli           #+#    #+#             */
/*   Updated: 2021/12/07 13:39:25 by jguigli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*destmem;
	const char	*srcmem;

	destmem = (char *)dest;
	srcmem = (char *)src;
	if (!destmem && !srcmem)
		return (NULL);
	while (n)
	{
		*destmem = *srcmem;
		srcmem++;
		destmem++;
		n--;
	}
	return (dest);
}
