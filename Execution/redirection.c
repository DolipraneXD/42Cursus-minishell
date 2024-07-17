/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:29:07 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/12 13:40:02 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Apply file descriptor redirections
void	apply_redirections(t_data *data)
{
	if (data->fd_in != STDIN_FILENO)
	{
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
	if (data->fd_out != STDOUT_FILENO)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
}

// Reset file descriptor redirections to original values
void	reset_redirections(t_cmds *cmd, t_data *data, int or_in, int or_out)
{
	(void)data;
	dup2(or_in, STDIN_FILENO);
	dup2(or_out, STDOUT_FILENO);
	close(or_in);
	close(or_out);
	close_heredoc_fds(cmd);
}

// Handle redirections and return original stdin/stdout file descriptors
int	handle_red(t_cmds *cmds, t_data *data, int *or_stdin, int *or_stdout)
{
	*or_stdin = dup(STDIN_FILENO);
	*or_stdout = dup(STDOUT_FILENO);
	if (check_redirection(cmds) == -1)
	{
		reset_redirections(cmds, data, *or_stdin, *or_stdout);
		data->status = 1;
		return (-1);
	}
	data->fd_in = cmds->in_red;
	data->fd_out = cmds->out_red;
	apply_redirections(data);
	return (0);
}
