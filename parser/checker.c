/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:45:08 by ahsadik           #+#    #+#             */
/*   Updated: 2024/07/11 16:02:00 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_syntax(t_data **data, int *is_heredoc, int line_start)
{
	t_tokens	*token;

	line_start = 1;
	token = *(*data)->tokens;
	while (token)
	{
		if (line_start == 1 && token->type == PIPE)
			return (synerror(data, token, UNEXP));
		else if (token->type >= ROUT && (!token->next
				|| token->next->type >= ROUT || token->next->type == PIPE))
			return (synerror(data, token->next, UNEXP));
		else if (token->type == RHEREDOC)
			(*is_heredoc)++;
		else if (token->type == PIPE && !token->next)
			return (synerror(data, token->next, UNEXP));
		else if (token->type == PIPE)
			line_start = 1;
		else
			line_start = 0;
		token = token->next;
	}
	return (0);
}

int	syntaxerr(t_tokens *tokens)
{
	int			line_start;
	t_tokens	*token;

	line_start = 1;
	token = tokens;
	while (token)
	{
		if (line_start == 1 && token->type == PIPE)
			return (1);
		else if (token->type >= ROUT && (!token->next
				|| token->next->type >= ROUT || token->next->type == PIPE))
			return (1);
		else if (token->type == PIPE && !token->next)
			return (1);
		else if (token->type == PIPE)
			line_start = 1;
		else
			line_start = 0;
		token = token->next;
	}
	return (0);
}

int	ft_strnchr(char *str, char c, int n)
{
	int		i;
	int		count;
	int		in_quotes;
	char	oquote;

	i = 0;
	count = 0;
	oquote = 34;
	in_quotes = 1;
	if (c == 34)
		oquote = 39;
	while (i < n)
	{
		if (str[i] == oquote)
			in_quotes *= -1;
		if (str[i] == c && in_quotes > 0)
		{
			count++;
			while (str[i + 1] != c && i + 1 < n)
				i++;
		}
		i++;
	}
	return (count);
}
