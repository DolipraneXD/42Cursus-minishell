/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:09:32 by ahsadik           #+#    #+#             */
/*   Updated: 2024/07/06 13:26:15 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_hd_fd(t_data *data, t_cmds **cmds, int status)
{
	t_file	*tmp_infile;
	t_cmds	*tmp_cmd;

	tmp_cmd = *cmds;
	while (tmp_cmd)
	{
		tmp_infile = tmp_cmd->infile;
		while (tmp_infile)
		{
			if (tmp_infile->type == HEREDOC && tmp_infile->hd_fd == -1)
			{
				tmp_infile->hd_fd
					= open_read_heredoc(data, tmp_infile->filename);
				if (status)
					close(tmp_infile->hd_fd);
				return (0);
			}
			tmp_infile = tmp_infile->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}

int	parseit(t_tokens **tokens, t_cmds **cmds, t_data **data, char *cmd)
{
	int		status;
	int		is_heredoc;
	t_cmds	*tmp_cmd;

	if (!cmd)
		exit((*data)->status);
	is_heredoc = 0;
	status = 1;
	(*data)->tokens = tokens;
	(*data)->cmds = cmds;
	(*data)->cmd = cmd;
	lexer(data);
	parser(data);
	tmp_cmd = *cmds;
	while (tmp_cmd)
	{
		tmp_cmd = reform_cmds(data, tmp_cmd);
		tmp_cmd = tmp_cmd->next;
	}
	if (!check_syntax(data, &is_heredoc, status))
		status = 0;
	while (is_heredoc--)
		set_hd_fd(*data, cmds, status);
	merge_red(data, status);
	return (status);
}

void	free_cmds(t_cmds **cmds)
{
	int		i;
	t_cmds	*tmp;

	while (*cmds)
	{
		if ((*cmds)->args)
		{
			i = 0;
			while ((*cmds)->args[i])
			{
				(*cmds)->args[i] = ft_free((*cmds)->args[i]);
				i++;
			}
			(*cmds)->args = ft_free((*cmds)->args);
		}
		ft_fileclear(&(*cmds)->infile);
		ft_fileclear(&(*cmds)->outfile);
		ft_fileclear(&(*cmds)->iofiles);
		tmp = (*cmds)->next;
		*cmds = ft_free(*cmds);
		*cmds = tmp;
	}
	*cmds = NULL;
}

int	count2d(char **str)
{
	int	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count])
		count++;
	return (count);
}

int	just_space(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
		if (str[i++] != 32)
			return (0);
	return (1);
}
