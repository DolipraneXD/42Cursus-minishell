/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:26:41 by ahsadik           #+#    #+#             */
/*   Updated: 2024/07/11 16:04:12 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*remove_quotes(char *str, int start, int end, int free)
{
	char	*tmp_str;
	char	*new_str;
	char	*part;

	new_str = ft_substr(str, 0, start);
	if (!new_str)
		return (NULL);
	part = ft_substr(str, start + 1, end - (start + 1));
	if (!part)
		return (NULL);
	tmp_str = ft_strjoin(new_str, part, 3);
	if (!tmp_str)
		return (NULL);
	new_str = tmp_str;
	part = ft_substr(str, end + 1, ft_strlen(str) - end);
	if (!part)
		return (NULL);
	tmp_str = ft_strjoin(new_str, part, 3);
	if (!tmp_str)
		return (NULL);
	new_str = tmp_str;
	if (free)
		str = ft_free(str);
	return (new_str);
}

static int	exp_quotes(char *str, int i)
{
	char	quote;

	if (str[i + 1] != 34 && str[i + 1] != 39)
		return (0);
	quote = str[i + 1];
	if (ft_strnchr(str, quote, i) % 2 == 0)
		return (1);
	return (0);
}

char	*check_expand(char *str, t_data *data, int *is_exp, int thirdarg)
{
	int	i;
	int	open2quotes;

	i = 0;
	open2quotes = -1;
	while (str[i])
	{
		open2quotes = skip_quotes(str, &i, open2quotes);
		if (open2quotes > 0 && str[i] == '$'
			&& str[i + 1] && (str[i + 1] == '"' || str[i + 1] == '\''))
			i++;
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1])
				|| ft_strchr("?_", str[i + 1]) || exp_quotes(str, i)))
		{
			if (thirdarg && is_exp)
				*is_exp = true;
			str = get_var_value(str, data, &i);
			if (!str)
				return (NULL);
		}
		i++;
	}
	return (str);
}

static int	get_second_quote(char *str, int i)
{
	if (str[i] == 34 && ++i)
		while (str[i] && str[i] != 34)
			i++;
	else if (str[i] == 39 && ++i)
		while (str[i] && str[i] != 39)
			i++;
	return (i);
}

char	*rm_quotes(char *str, int free)
{
	int	i;
	int	last_stop;

	i = 0;
	while (str[i])
	{
		while (str[i])
			if ((str[i] == 39 || str[i] == 34) || !(++i))
				break ;
		if (!str[i])
			return (str);
		last_stop = i;
		i = get_second_quote(str, i);
		if (i != last_stop)
		{
			str = remove_quotes(str, last_stop, i, free);
			if (!str)
				return (NULL);
			free = 1;
			i--;
		}
	}
	return (str);
}
