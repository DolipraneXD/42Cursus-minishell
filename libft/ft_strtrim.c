/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:35:46 by ahsadik           #+#    #+#             */
/*   Updated: 2023/11/19 13:35:38 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

int	getstart(char const *s, char const *set)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_in(s[i], set) == 1)
			i++;
		else
			break ;
	}
	return (i);
}

int	getend(char const *s, char const *set)
{
	int	i;

	i = (int)ft_strlen(s) - 1;
	while (i > 0)
	{
		if (is_in(s[i], set) == 1)
			i--;
		else
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*mem;

	if (!s1 || !set)
		return (0);
	start = getstart(s1, set);
	end = getend(s1, set);
	if (end < start)
		return ((char *)ft_calloc(1, 1));
	mem = ft_substr(s1, start, (end - start) + 1);
	return (mem);
}
