/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:39:37 by ahsadik           #+#    #+#             */
/*   Updated: 2024/05/25 15:41:18 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	n;
	size_t	str_len;

	str_len = ft_strlen(str);
	n = 0;
	while (n <= str_len)
	{
		if (str[n] == (char)c)
		{
			return ((char *)&str[n]);
		}
		n++;
	}
	return (0);
}
