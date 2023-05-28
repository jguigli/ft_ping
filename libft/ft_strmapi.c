/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguigli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:37:32 by jguigli           #+#    #+#             */
/*   Updated: 2021/12/01 17:50:03 by jguigli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*newstr;

	if (!s || !f)
		return (NULL);
	i = 0;
	newstr = (char *)malloc(ft_strlen((char *)s) + 1);
	if (!newstr)
		return (NULL);
	ft_strcpy(newstr, (char *)s);
	while (s[i])
	{
		newstr[i] = (*f)(i, newstr[i]);
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
