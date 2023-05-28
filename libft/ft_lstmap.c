/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguigli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:48:00 by jguigli           #+#    #+#             */
/*   Updated: 2021/12/03 18:58:46 by jguigli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*aprems;
	t_list	*anouv;

	aprems = NULL;
	while (lst)
	{
		anouv = ft_lstnew(f(lst->content));
		if (!anouv)
		{
			while (aprems)
			{
				ft_lstclear(&aprems, del);
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&aprems, anouv);
		lst = lst->next;
	}
	return (aprems);
}
