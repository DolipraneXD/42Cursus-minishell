/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:57:16 by moel-fat          #+#    #+#             */
/*   Updated: 2024/05/31 12:20:02 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_cmd_error(char **cmd, t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	data->status = 127;
	exit(127);
}

void	ft_error_cmdnotfound(char **cmd, t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	data->status = 127;
	exit(127);
}

void	ft_error_permission_denie(char **cmd, t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": Permission denie\n", 2);
	data->status = 126;
	exit(126);
}

void	ft_error_is_directory(char **cmd, t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": is a directory\n", 2);
	data->status = 126;
	exit(126);
}

void	ft_error_ambiguous_redirect(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}
