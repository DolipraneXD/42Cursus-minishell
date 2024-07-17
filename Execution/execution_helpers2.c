/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:33:30 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/04 15:53:24 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>

// Check if the command is a builtin and execute it
int	check_builtins(t_cmds *cmds, t_data *data)
{
	if (!cmds || !cmds->args || !cmds->args[0])
		return (0);
	if (ft_strncmp(cmds->args[0], "echo", 5) == 0)
		return (ft_echo(cmds, data), 1);
	if (ft_strncmp(cmds->args[0], "cd", 3) == 0)
		return (ft_cd(cmds, data), 1);
	if (ft_strncmp(cmds->args[0], "pwd", 4) == 0)
		return (ft_pwd(cmds, data), 1);
	if (ft_strncmp(cmds->args[0], "export", 7) == 0)
		return (ft_export(cmds, &(data->env), data), 1);
	if (ft_strncmp(cmds->args[0], "unset", 6) == 0)
		return (ft_unset(cmds, data), 1);
	if (ft_strncmp(cmds->args[0], "env", 4) == 0)
		return (ft_env(cmds, data->env, data), 1);
	if (ft_strncmp(cmds->args[0], "exit", 5) == 0)
		return (ft_exit(cmds, data), 1);
	return (0);
}

// Wait for all child processes to finish and set the last exit status
void	wait_for_children(t_data *data)
{
	int	status;

	if (waitpid(data->pid, &status, 0) == -1)
	{
		perror("waitpid");
		return ;
	}
	if (WIFSIGNALED(status))
	{
		data->status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == 2)
			printf("\n");
		else if (WTERMSIG(status) == 3)
			printf("Quit: 3\n");
		g_king = 0;
		reset_tty();
	}
	else
		data->status = WEXITSTATUS(status);
	while (wait(NULL) > 0)
		;
}

// Function to handle commands with slashes in their path
static void	execute_with_path(t_cmds *cmds, t_data *data)
{
	struct stat	filestat;

	if (stat(cmds->args[0], &filestat) == -1)
	{
		if (errno == ENOTDIR)
			ft_error_not_directory(cmds->args, data);
		else if (errno == ENOENT)
			ft_print_cmd_error(cmds->args, data);
		return ;
	}
	if (S_ISDIR(filestat.st_mode))
	{
		ft_error_is_directory(cmds->args, data);
		return ;
	}
	if (!(filestat.st_mode & S_IEXEC))
	{
		ft_error_permission_denie(cmds->args, data);
		return ;
	}
	if (execve(cmds->args[0], cmds->args, data->env_arry) == -1)
	{
		perror(cmds->args[0]);
		exit(EXIT_FAILURE);
	}
}

static void	execute_command(t_cmds *cmds, t_data *data)
{
	if (!cmds->args || !cmds->args[0])
		exit(1);
	if (check_builtins(cmds, data))
		exit(0);
	if (check_point_slash(cmds->args) || check_slash(cmds->args))
	{
		execute_with_path(cmds, data);
	}
	else
	{
		if (cmds->args && cmds->args[0] && cmds->args[0][0] == '\0')
			ft_error_cmdnotfound(cmds->args, data);
		if (cmds->args && cmds->args[0]
			&& (ft_strncmp(cmds->args[0], ".", 1) == 0
				|| ft_strncmp(cmds->args[0], "..", 2) == 0))
			ft_error_cmdnotfound(cmds->args, data);
		access_exev(cmds, data);
	}
}

// Call child process with appropriate redirections
void	call_child(t_cmds *cmds, t_data *data, int in_fd, int out_fd)
{
	if (data->pipe_on == true)
	{
		if (check_redirection(cmds) == -1)
			exit(EXIT_FAILURE);
		data->fd_in = cmds->in_red;
		data->fd_out = cmds->out_red;
	}
	if (data->fd_in == STDIN_FILENO && in_fd != STDIN_FILENO)
		data->fd_in = in_fd;
	if (data->fd_out == STDOUT_FILENO && out_fd != STDOUT_FILENO)
		data->fd_out = out_fd;
	apply_redirections(data);
	execute_command(cmds, data);
}
