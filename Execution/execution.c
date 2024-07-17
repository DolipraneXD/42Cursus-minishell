/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:08:32 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/12 14:12:38 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fork_and_execute(t_cmds *cmds, t_data *data)
{
	int	status;

	data->pid = fork();
	if (data->pid == -1)
		return (perror("fork"));
	if (data->pid == 0)
	{
		call_child(cmds, data, STDIN_FILENO, STDOUT_FILENO);
		exit(0);
	}
	else
	{
		waitpid(data->pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			data->status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == 2)
				printf("\n");
			if (WTERMSIG(status) == 3)
				printf("Quit: 3\n");
			reset_tty();
		}
		else
			data->status = WEXITSTATUS(status);
	}
}

// Execute a single command with redirections and handle status
void	ft_execut_one(t_cmds *cmds, t_data *data)
{
	int	or_stdin;
	int	or_stdout;

	setup_environment(data);
	if (handle_red(cmds, data, &or_stdin, &or_stdout) == -1)
	{
		cleanup_environment(data);
		return ;
	}
	if (cmds->cmd == NULL)
	{
		reset_redirections(cmds, data, or_stdin, or_stdout);
		cleanup_environment(data);
		return ;
	}
	if (check_builtins(cmds, data))
	{
		reset_redirections(cmds, data, or_stdin, or_stdout);
		cleanup_environment(data);
		return ;
	}
	fork_and_execute(cmds, data);
	reset_redirections(cmds, data, or_stdin, or_stdout);
	cleanup_environment(data);
}

// Set up pipe and fork a command
int	setup_and_fork_command(t_cmds *cmds, t_data *data, int in_fd, int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	data->pid = fork();
	if (data->pid == -1)
		return (-1);
	if (data->pid == 0)
	{
		close(pipe_fd[0]);
		call_child(cmds, data, in_fd, pipe_fd[1]);
		exit (0);
	}
	else
	{
		close(pipe_fd[1]);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		close_heredoc_fds(cmds);
	}
	return (0);
}

// Execute multiple piped commands
static void	ft_execut_multi(t_cmds *cmds, t_data *data)
{
	int		pipe_fd[2];
	int		in_fd;
	t_cmds	*current_cmd;

	in_fd = STDIN_FILENO;
	current_cmd = cmds;
	if (current_cmd->cmd == NULL)
		return ;
	setup_environment(data);
	while (current_cmd->next != NULL)
	{
		if (setup_and_fork_command(current_cmd, data, in_fd, pipe_fd) == -1)
			break ;
		in_fd = pipe_fd[0];
		current_cmd = current_cmd->next;
	}
	data->pid = fork();
	if (data->pid == -1)
		return (perror("fork"));
	if (data->pid == 0)
		call_child(current_cmd, data, in_fd, STDOUT_FILENO);
	else
		ft_execut_multi_helper(current_cmd, data, in_fd);
}

// Main function to execute commands
void	ft_execut(t_cmds *cmds, t_data *data)
{
	t_cmds	*tmp;

	if (cmds == NULL)
		return ;
	g_king = 1;
	tmp = cmds;
	while (tmp && cmds->cmd != NULL)
	{
		tmp->args = remove_empty_args(tmp);
		remove_quotesfromargs(tmp);
		tmp = tmp->next;
	}
	if (cmds->next == NULL)
	{
		data->pipe_on = false;
		add_last_arg_to_env(cmds, data, 0);
		ft_execut_one(cmds, data);
	}
	else
	{
		data->pipe_on = true;
		add_last_arg_to_env(cmds, data, 1);
		ft_execut_multi(cmds, data);
	}
	g_king = 0;
}
