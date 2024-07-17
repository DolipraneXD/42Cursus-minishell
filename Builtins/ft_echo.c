/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:37:32 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/12 14:12:56 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_n(char *str)
{
	int	i;

	i = 2;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	ft_echo(t_cmds *cmd, t_data *data)
{
	data->i = 1;
	data->n = 0;
	if (cmd->args[data->i] == NULL)
	{
		ft_putstr_fd("\n", 1);
		data->status = 0;
		return ;
	}
	while (cmd->args[data->i] && !ft_strncmp(cmd->args[data->i], "-n", 2))
	{
		if (check_for_n(cmd->args[data->i]) == 0)
			break ;
		data->n = 1;
		data->i++;
	}
	while (cmd->args[data->i])
	{
		ft_putstr_fd(cmd->args[data->i], 1);
		if (cmd->args[data->i + 1])
			ft_putstr_fd(" ", 1);
		data->i++;
	}
	if (!data->n)
		ft_putstr_fd("\n", 1);
	data->status = 0;
}
