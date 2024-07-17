/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:30:28 by ahsadik           #+#    #+#             */
/*   Updated: 2024/05/20 15:54:41 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *source )
{
	char	*mem;
	size_t	size;

	size = ft_strlen(source) + 1;
	mem = malloc(size);
	if (mem)
		ft_memcpy(mem, source, size);
	return (mem);
}
