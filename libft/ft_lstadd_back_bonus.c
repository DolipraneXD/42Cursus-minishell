/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:13:19 by ahsadik           #+#    #+#             */
/*   Updated: 2024/04/19 17:56:33 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*ptr;

	ptr = ft_lstlast(*lst);
	if (ptr)
		ptr->next = new;
	else
		*lst = new;
}
