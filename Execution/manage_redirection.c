/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:54:04 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/03 16:10:05 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error_open(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(" No such file or directory", 2);
	ft_putstr_fd("\n", 2);
}

void	open_files(t_cmds *cmds, t_file *tmp)
{
	int	old_in;
	int	old_out;

	old_in = cmds->in_red;
	old_out = cmds->out_red;
	if (tmp->type == STDIN)
		cmds->in_red = 0;
	else if (tmp->type == HEREDOC)
		cmds->in_red = tmp->hd_fd;
	else if (tmp->type == INFILE)
		cmds->in_red = open_infile(tmp);
	else if (tmp->type == STDOUT)
		cmds->out_red = 1;
	else if (tmp->type == OUTFILE)
		cmds->out_red = open_outfile(tmp);
	else if (tmp->type == APPEND)
		cmds->out_red = open_append(tmp);
	if (cmds->in_red != 0 && old_in != cmds->in_red
		&& cmds->in_red != tmp->hd_fd && old_in != 0)
		close(old_in);
	if (cmds->out_red != 1 && old_out != cmds->out_red && old_out != 1)
		close(old_out);
}

int	check_redirection(t_cmds *cmds)
{
	t_file	*tmp;

	cmds->in_red = 0;
	cmds->out_red = 1;
	tmp = cmds->iofiles;
	while (tmp)
	{
		open_files(cmds, tmp);
		if (cmds->in_red == -1 || cmds->out_red == -1)
		{
			if (cmds->in_red != 0)
				close(cmds->in_red);
			if (cmds->out_red != 1)
				close(cmds->out_red);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}
