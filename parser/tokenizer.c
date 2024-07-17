/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:27:33 by ahsadik           #+#    #+#             */
/*   Updated: 2024/07/03 18:05:48 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	skip_spaces(char *cmd, int *i)
{
	while (cmd[*i] && cmd[*i] == ' ')
		(*i) += 1;
	return (*i);
}

int	check_filename(char chr, int position)
{
	if (position == 0 && !ft_strchr("!#&();<>[]\\`{}|", chr))
		return (1);
	else if (position == 1 && !ft_strchr(" !&();<>[]\\`{}|", chr))
		return (1);
	return (0);
}

static int	get_redirection(t_data **data, char *cmd, int *i)
{
	if (cmd[*i] == '<' && cmd[*i + 1] == '<')
	{
		add_token(data, ft_substr(cmd, *i, 2), RHEREDOC);
		*i += 2;
	}
	else if (cmd[*i] == '>' && cmd[*i + 1] == '>')
	{
		add_token(data, ft_substr(cmd, *i, 2), RAPPEND);
		*i += 2;
	}
	else if (cmd[*i] && cmd[*i] == '>')
		add_token(data, ft_substr(cmd, (*i)++, 1), ROUT);
	else if (cmd[*i] && cmd[*i] == '<')
		add_token(data, ft_substr(cmd, (*i)++, 1), RIN);
	else
		return (0);
	skip_spaces(cmd, i);
	if (check_filename(cmd[*i], 0))
		get_redfile(data, cmd, i);
	return (*i);
}

static int	get_args(t_data **data, int *id_counter, int *i)
{
	int	last_stop;
	int	assign;
	int	type;

	last_stop = skip_spaces((*data)->cmd, i);
	assign = get_unquoted((*data)->cmd, i);
	if (*i == last_stop)
		return (0);
	if (assign < 0)
		return (synerror(data, NULL, UQUOTES));
	else if (assign > 0 && *id_counter != 0)
		type = ASSIGN;
	else if (*id_counter == 0)
	{
		type = COMMAND;
		(*id_counter)++;
	}
	else if (startswith((*data)->cmd, '-', last_stop))
		type = FLAG;
	else
		type = ARGUMENT;
	add_token(data, ft_substr((*data)->cmd, last_stop, *i - last_stop), type);
	return (0);
}

int	lexer(t_data **data)
{
	int	i;
	int	last_stop;
	int	id_counter;

	i = 0;
	last_stop = 0;
	id_counter = 0;
	while ((*data)->cmd[i])
	{
		last_stop = skip_spaces((*data)->cmd, &i);
		while (((*data)->cmd[i] == '<' || (*data)->cmd[i] == '>')
			&& last_stop >= 0)
			last_stop = get_redirection(data, (*data)->cmd, &i);
		last_stop = skip_spaces((*data)->cmd, &i);
		while ((*data)->cmd[i] == '|' && ++i)
			id_counter = add_token(data, ft_strdup("|"), PIPE);
		if ((*data)->cmd[i] == '#')
			while ((*data)->cmd[i])
				i++;
		if (get_args(data, &id_counter, &i))
			(*data)->status = 258;
		last_stop = i;
	}
	return (0);
}
