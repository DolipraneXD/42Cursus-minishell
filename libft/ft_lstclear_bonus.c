/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:37:13 by ahsadik           #+#    #+#             */
/*   Updated: 2024/06/26 18:12:15 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstclear(t_tokens **lst)
{
	t_tokens	*ptr;
	t_tokens	*tmp;

	if (!lst)
		return ;
	ptr = *lst;
	while (ptr)
	{
		if (ptr->token)
			ptr->token = ft_free(ptr->token);
		tmp = ptr->next;
		if (ptr)
			ptr = ft_free(ptr);
		ptr = tmp;
	}
	*lst = ptr;
}
