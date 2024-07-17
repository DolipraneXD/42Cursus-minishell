/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 01:23:59 by ahsadik           #+#    #+#             */
/*   Updated: 2024/06/26 18:11:33 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char sep)
{
	int	words_counter;
	int	is_word;

	words_counter = 0;
	is_word = 0;
	while (*str)
	{
		if (*str != sep && is_word == 0)
		{
			is_word = 1;
			words_counter++;
		}
		else if (*str == sep)
			is_word = 0;
		str++;
	}
	return (words_counter);
}

static char	*word_dup(const char *str, int start, int end)
{
	char	*word;
	int		i;

	word = (char *)malloc(((end - start) + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	extract(t_sp *spl, const char *s, char sep)
{
	if (s[spl->s_counter] != sep && spl->start < 0)
		spl->start = spl->s_counter;
	else if ((s[spl->s_counter] == sep || spl->s_counter == spl->s_len)
		&& spl->start >= 0)
	{
		spl->res[spl->res_count++] = word_dup(s, spl->start, spl->s_counter);
		if (!spl->res[spl->res_count - 1])
		{
			while (--spl->res_count)
				free(spl->res[spl->res_count - 1]);
			free(spl->res);
			spl->res = NULL;
			return ;
		}
		spl->start = -1;
	}
}

char	**ft_split(char const *s, char sep)
{
	t_sp	spl;

	if (!s)
		return (NULL);
	spl.s_len = (int)ft_strlen(s);
	spl.res = (char **)malloc((count_words(s, sep) + 1) * sizeof(char *));
	if (!spl.res)
		return (NULL);
	spl.s_counter = -1;
	spl.res_count = 0;
	spl.start = -1;
	while (++spl.s_counter <= spl.s_len)
	{
		extract(&spl, s, sep);
		if (spl.res == NULL)
			return (NULL);
	}
	spl.res[spl.res_count] = 0;
	return (spl.res);
}
