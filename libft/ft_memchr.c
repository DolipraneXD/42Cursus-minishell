/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:18:37 by ahsadik           #+#    #+#             */
/*   Updated: 2023/11/26 10:55:00 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr( const void *m_block, int chr, size_t size )
{
	unsigned char	*str;

	str = (unsigned char *)m_block;
	while (size > 0)
	{
		if (*str == (unsigned char)chr)
			return (str);
		str++;
		size--;
	}
	return (0);
}
