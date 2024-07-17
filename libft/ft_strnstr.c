/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:15:50 by ahsadik           #+#    #+#             */
/*   Updated: 2023/11/24 02:47:40 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *word, size_t len)
{
	size_t	x;
	size_t	y;

	if (!str && !len && word)
		return (NULL);
	if (!word[0])
		return ((char *)str);
	x = 0;
	y = 0;
	while (str[x] && x < len)
	{
		y = 0;
		while (str[x + y] == word[y] && str[x + y] != '\0' && (x + y) < len)
			y++;
		if (y == ft_strlen(word))
			return ((char *)(str + x));
		x++;
	}
	return (0);
}
