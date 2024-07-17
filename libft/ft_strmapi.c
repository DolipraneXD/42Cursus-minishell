/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:37:18 by ahsadik           #+#    #+#             */
/*   Updated: 2023/11/19 17:14:40 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		n;
	size_t	s_len;
	char	*mem;

	if (!s || !f)
		return (0);
	s_len = ft_strlen(s);
	mem = malloc(s_len * sizeof(char) + 1);
	if (!mem)
		return (0);
	n = 0;
	while (s[n])
	{
		mem[n] = f(n, s[n]);
		n++;
	}
	mem[n] = '\0';
	return (mem);
}
