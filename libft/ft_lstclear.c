/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguigli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:25:12 by jguigli           #+#    #+#             */
/*   Updated: 2021/12/03 18:47:09 by jguigli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lstdel;

	lstdel = *lst;
	if (*lst)
	{
		while (*lst)
		{
			del((*lst)->content);
			lstdel = *lst;
			*lst = lstdel->next;
			free(lstdel);
		}
		*lst = NULL;
	}
}
