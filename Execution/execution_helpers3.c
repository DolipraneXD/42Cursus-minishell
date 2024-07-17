/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:40:07 by moel-fat          #+#    #+#             */
/*   Updated: 2024/05/31 17:47:15 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_environment(t_data *data)
{
	data->env_arry = ft_lst_to_array(data->env);
	data->path = ft_find_path(data->env_arry);
}

void	cleanup_environment(t_data *data)
{
	ft_free_array(data->env_arry);
	ft_free_array(data->path);
}

void	add_last_arg_to_env(t_cmds *cmds, t_data *data, int flag)
{
	int		i;
	char	*str;

	if (cmds == NULL || cmds->args == NULL)
		return ;
	i = 0;
	str = "_";
	while (cmds->args[i])
		i++;
	if (flag == 0 && i != 0)
		ft_add_env2(str, cmds->args[i - 1], &data->env, 1);
	else
		ft_add_env2(str, "", &data->env, 1);
}

int	check_slash(char **cmd)
{
	if (cmd == NULL || *cmd == NULL)
		return (0);
	if (ft_strchr (cmd[0], '/') != NULL)
		return (1);
	return (0);
}

int	check_point_slash(char **cmd)
{
	if (cmd == NULL || *cmd == NULL)
		return (0);
	if (ft_strncmp(cmd[0], "./", 2) == 0)
	{
		if (access(cmd[0], X_OK) == -1)
			return (1);
	}
	return (0);
}
