/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:48:39 by ahsadik           #+#    #+#             */
/*   Updated: 2023/11/17 15:47:54 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;
	size_t	n;

	if (!dst && !src)
		return (0);
	d = (char *)dst;
	s = (char *)src;
	if (d < s)
	{
		n = 0;
		while (n < len)
		{
			d[n] = s[n];
			n++;
		}
	}
	else
		while (len--)
			d[len] = s[len];
	return (dst);
}
