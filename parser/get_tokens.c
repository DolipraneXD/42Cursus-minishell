/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:57:41 by ahsadik           #+#    #+#             */
/*   Updated: 2024/06/26 17:39:36 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_squoted(char *cmd, int *i)
{
	(*i)++;
	while (cmd[*i] && cmd[*i] != 39)
		(*i)++;
	if (!cmd[*i])
		return (-1);
	if (cmd[*i] == 39)
		(*i)++;
	return (0);
}

int	get_dquoted(char *cmd, int *i)
{
	int	assign;

	assign = 0;
	(*i)++;
	while (cmd[*i] && cmd[*i] != 34)
	{
		if (cmd[*i] == '=')
			assign = 1;
		(*i)++;
	}
	if (!cmd[*i])
		return (-1);
	if (cmd[*i] == 34)
		(*i)++;
	return (assign);
}

int	get_unquoted(char *cmd, int *i)
{
	int	assign;
	int	tmp;

	assign = 0;
	tmp = *i;
	while (cmd[*i] && !ft_strchr("<>| ", cmd[*i]))
	{
		if (*i != 0 && cmd[*i] == '=' && cmd[*i - 1] != ' ')
			assign += 1;
		if (cmd[*i] == 34 || cmd[*i] == 39)
		{
			if (cmd[*i] == 34)
				assign += get_dquoted(cmd, i);
			if (cmd[*i] == 39)
				assign += get_squoted(cmd, i);
		}
		else
			(*i)++;
	}
	return (assign);
}

char	*get_redfile(t_data **data, char *cmd, int *i)
{
	int	ret;
	int	last_stop;

	last_stop = *i;
	ret = 0;
	if (cmd[*i] == '#')
		synerror(data, NULL, UNEXP);
	while (cmd[*i])
	{
		if (cmd[*i] == 39)
			ret = get_squoted(cmd, i);
		else if (cmd[*i] == 34)
			ret = get_dquoted(cmd, i);
		else if (check_filename(cmd[*i], 1))
			*i += 1;
		else
			break ;
		if (ret == -1)
			synerror(data, NULL, UQUOTES);
	}
	if (ret >= 0)
		add_token(data, ft_substr(cmd, last_stop, *i - last_stop), RFILE);
	return (0);
}
