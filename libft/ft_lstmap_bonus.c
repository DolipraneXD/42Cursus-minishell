/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:21:25 by ahsadik           #+#    #+#             */
/*   Updated: 2024/05/24 16:25:45 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tokens	*ft_lstmap(t_tokens *lst, void *(*f)(void *), void (*del)(void *))
{
	t_tokens	*swx;
	t_tokens	*new;

	if (!lst || !f || !del)
		return (0);
	new = 0;
	while (lst)
	{
		swx = ft_lstnew(NULL, 0);
		if (!swx)
		{
			ft_lstclear(&new);
			return (0);
		}
		swx->token = f(lst->token);
		ft_lstadd_back(&new, swx);
		lst = lst->next;
	}
	return (new);
}
