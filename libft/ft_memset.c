/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:17:57 by ahsadik           #+#    #+#             */
/*   Updated: 2023/11/18 13:34:22 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset( void *ptr, int value, size_t count )
{
	unsigned char	*ss;

	ss = (unsigned char *)ptr ;
	while (count > 0)
	{
		*ss = value;
		ss++;
		count--;
	}
	return (ptr);
}
