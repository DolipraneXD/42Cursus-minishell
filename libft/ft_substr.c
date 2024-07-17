/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:51:43 by ahsadik           #+#    #+#             */
/*   Updated: 2024/05/25 16:45:08 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*mem;
	int		n;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > (s_len - start))
		len = s_len - start;
	mem = malloc((len + 1) * sizeof(char));
	if (!mem)
		return (NULL);
	n = 0;
	while (n < (int)len)
	{
		mem[n] = s[start + n];
		n++;
	}
	mem[n] = '\0';
	return (mem);
}
