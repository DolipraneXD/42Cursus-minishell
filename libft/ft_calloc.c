/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:07:13 by ahsadik           #+#    #+#             */
/*   Updated: 2023/11/19 16:18:34 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc( size_t count, size_t size )
{
	char	*mem;
	size_t	space;

	space = count * size;
	if (count != 0 && space / count != size)
		return (0);
	mem = malloc(space);
	if (mem)
		ft_bzero(mem, space);
	return (mem);
}
