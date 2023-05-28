/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguigli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:16:00 by jguigli           #+#    #+#             */
/*   Updated: 2021/12/06 12:09:49 by jguigli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*lstnew;

	if (*alst && alst)
	{
		lstnew = *alst;
		while (lstnew->next)
			lstnew = lstnew->next;
		lstnew->next = new;
	}
	else if (alst && !*alst)
		*alst = new;
}
