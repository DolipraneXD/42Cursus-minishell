/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:58:21 by ahsadik           #+#    #+#             */
/*   Updated: 2024/04/24 17:11:48 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_tokens *lst, void (*f)(void *))
{
	t_tokens	*ptr;

	ptr = lst;
	while (ptr)
	{
		f(ptr->token);
		if (!ptr->next)
			break ;
		ptr = ptr->next;
	}
}
