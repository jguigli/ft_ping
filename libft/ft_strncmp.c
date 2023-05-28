/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguigli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:56:32 by jguigli           #+#    #+#             */
/*   Updated: 2021/12/02 19:56:19 by jguigli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	i;

	if (length == 0)
		return (0);
	i = 0;
	while ((first[i] || second[i]) && first[i] == second[i] && i < length - 1)
		i++;
	return ((unsigned char)first[i] -(unsigned char)second[i]);
}
