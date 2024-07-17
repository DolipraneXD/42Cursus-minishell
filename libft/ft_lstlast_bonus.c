/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:50:56 by ahsadik           #+#    #+#             */
/*   Updated: 2024/04/19 17:57:07 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tokens	*ft_lstlast(t_tokens *lst)
{
	t_tokens	*ptr;

	ptr = lst;
	while (ptr)
	{
		if (ptr->next)
			ptr = ptr->next;
		else
			break ;
	}
	return (ptr);
}
