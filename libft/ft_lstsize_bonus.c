/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:31:33 by ahsadik           #+#    #+#             */
/*   Updated: 2024/06/26 18:11:56 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_tokens *lst)
{
	int			count;
	t_tokens	*ptr;

	count = 0;
	ptr = lst;
	while (ptr)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}
