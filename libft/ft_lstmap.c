/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwi <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 17:56:15 by dwi               #+#    #+#             */
/*   Updated: 2020/05/27 17:41:38 by dwi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*alst;

	if (!lst)
		return (0);
	newlst = ft_lstnew((*f)(lst->content));
	if (!newlst)
		return (0);
	alst = newlst;
	while (lst->next)
	{
		lst = lst->next;
		newlst->next = ft_lstnew((*f)(lst->content));
		if (!newlst->next)
		{
			ft_lstclear(&alst, del);
			return (0);
		}
		newlst = newlst->next;
	}
	return (alst);
}
