/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguigli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:12:52 by jguigli           #+#    #+#             */
/*   Updated: 2021/12/07 13:42:15 by jguigli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tabl;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	tabl = (void *)malloc(nmemb * size);
	if (tabl == NULL)
		return (NULL);
	ft_bzero(tabl, nmemb * size);
	return (tabl);
}
