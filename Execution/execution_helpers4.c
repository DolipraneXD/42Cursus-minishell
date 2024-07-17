/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:43:02 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/12 14:14:05 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_quotesfromargs(t_cmds *cmds)
{
	int	i;

	if (cmds == NULL || cmds->args == NULL)
		return ;
	i = 0;
	while (cmds->args[i])
	{
		if (notempty(cmds->args[i]) == 0)
			cmds->args[i] = rm_quotes(cmds->args[i], 1);
		i++;
	}
}

void	ft_error_not_directory(char **cmd, t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": not a directory\n", 2);
	data->status = 126;
	exit(126);
}

void	close_heredoc_fds(t_cmds *cmds)
{
	t_file	*tmp;

	if (cmds->iofiles == NULL)
		return ;
	tmp = cmds->iofiles;
	while (tmp)
	{
		if (cmds->iofiles != NULL && cmds->iofiles->hd_fd != -1
			&& cmds->iofiles->hd_fd != 0)
			close(cmds->iofiles->hd_fd);
		tmp = tmp->next;
	}
}
