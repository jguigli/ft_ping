/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguigli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:09:51 by jguigli           #+#    #+#             */
/*   Updated: 2021/12/02 17:37:42 by jguigli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_free(char **liste)
{
	unsigned int	i;

	i = 0;
	while (liste[i])
	{
		free(liste[i]);
		i++;
	}
	free(liste);
	return (NULL);
}

static int	check_sep(char stri, char c)
{
	if (stri == c)
		return (1);
	return (0);
}

static char	*get_word(char const *str, char c, int i, char **liste)
{
	char	*dest;
	int		j;

	j = 0;
	while (str[i + j] && !(check_sep(str[i + j], c)))
		j++;
	dest = (char *)malloc(sizeof(char) * j + 1);
	if (!dest)
		return (ft_free(liste));
	j = 0;
	while (str[i + j] && !(check_sep(str[i + j], c)))
	{
		dest[j] = str[i + j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

static int	size_list(char const *str, char c)
{
	int	i;
	int	count;

	if (*str == '\0')
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && (check_sep(str[i], c)))
			i++;
		if (str[i] && !(check_sep(str[i], c)))
		{
			count++;
			while (str[i] && !(check_sep(str[i], c)))
				i++;
		}
	}
	return (count);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	int		p;
	char	**liste;

	i = 0;
	p = 0;
	liste = (char **)malloc(sizeof(char *) * (size_list(str, c) + 1));
	if (!liste)
		return (NULL);
	while (str[i])
	{
		while (str[i] && (check_sep(str[i], c)))
			i++;
		if (str[i] && !(check_sep(str[i], c)))
		{
			liste[p] = get_word(str, c, i, liste);
			while (str[i] && !(check_sep(str[i], c)))
				i++;
			p++;
		}
	}
	liste[p] = 0;
	return (liste);
}
