/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:51:59 by ahsadik           #+#    #+#             */
/*   Updated: 2023/11/24 05:19:08 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dest_len;
	size_t	len_to_cpy;

	if (dstsize == 0)
		return (ft_strlen(src));
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	if (dstsize <= dest_len)
		return (dstsize + src_len);
	len_to_cpy = dstsize - dest_len - 1;
	i = 0;
	while (i < len_to_cpy && src[i])
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}
