/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:26:11 by ahsadik           #+#    #+#             */
/*   Updated: 2024/06/26 18:11:42 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tokens	*ft_lstnew(void *token, int type)
{
	t_tokens	*one;

	one = malloc(sizeof(t_tokens));
	if (!one)
		return (0);
	one->token = token;
	one->type = type;
	one->next = 0;
	return (one);
}
