/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:17:44 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/05 15:57:36 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	heredoc_handler(int signum)
{
	(void)signum;
	g_king = 4;
	close(0);
}

static int	create_and_open_temp_file(t_data *data, char **here_name)
{
	*here_name = ft_itoa((int)(uintptr_t)create_and_open_temp_file);
	*here_name = ft_strjoin("/tmp/.", *here_name, 2);
	data->heredoc_fd = open(*here_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->heredoc_fd == -1)
	{
		perror("open");
		ft_free(*here_name);
		return (-1);
	}
	data->redoc_fd = open(*here_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->redoc_fd == -1)
	{
		perror("open");
		close(data->heredoc_fd);
		ft_free(*here_name);
		return (-1);
	}
	if (unlink(*here_name) == -1)
		perror("unlink");
	return (0);
}

static int	raw_here(t_data *data, char *delm, int expand, int old_zero)
{
	while (1)
	{
		data->line = readline("> ");
		if (g_king == 4)
		{
			data->status = 1;
			ft_free(data->line);
			dup2(old_zero, 0);
			close(data->heredoc_fd);
			close(old_zero);
			signals_hand();
			return (close(data->redoc_fd), -1);
		}
		if (!data->line || !ft_strncmp(data->line, delm, ft_strlen(delm) + 1))
		{
			ft_free(data->line);
			break ;
		}
		if (expand)
			data->line = check_expand(data->line, data, NULL, 0);
		ft_putstr_fd(data->line, data->heredoc_fd);
		ft_putstr_fd("\n", data->heredoc_fd);
		ft_free(data->line);
	}
	return (0);
}

static void	cleanup(t_data *data, char *delimiter, int expand, int old_zero)
{
	signals_hand();
	close(data->heredoc_fd);
	if (expand == 0)
		ft_free(delimiter);
	dup2(old_zero, 0);
	close(old_zero);
}

int	open_read_heredoc(t_data *data, char *delimiter)
{
	int		expand;
	int		old_zero;
	char	*here_name;

	if (create_and_open_temp_file(data, &here_name) == -1)
		return (-1);
	expand = 1;
	if (ft_strchr(delimiter, 34) || ft_strchr(delimiter, 39))
	{
		expand = 0;
		delimiter = rm_quotes(delimiter, 0);
	}
	signal(SIGINT, heredoc_handler);
	old_zero = dup(0);
	if (raw_here(data, delimiter, expand, old_zero) == -1)
	{
		ft_free(here_name);
		return (-1);
	}
	cleanup(data, delimiter, expand, old_zero);
	ft_free(here_name);
	return (data->redoc_fd);
}
