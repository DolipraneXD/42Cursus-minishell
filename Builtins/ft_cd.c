/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:37:29 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/12 14:12:53 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_error_cd(char *path, t_data *data)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	data->status = 1;
}

static void	set_it_home(t_data *data)
{
	char	*home;
	char	*oldpwd;

	home = ft_getenv(data->env, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		data->status = 1;
		return ;
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(home) == -1)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		data->status = 1;
		free(oldpwd);
		return ;
	}
	if (oldpwd != NULL)
		ft_setenv("OLDPWD", oldpwd, data);
	ft_setenv("PWD", home, data);
	data->status = 0;
	free(oldpwd);
}

void	ft_cd(t_cmds *cmd, t_data *data)
{
	char	*pwd;
	char	*newpwd;

	if (cmd->args[1] == NULL || !ft_strncmp(cmd->args[1], "~", 2)
		|| cmd->args[1][0] == '\0')
		set_it_home(data);
	else if (cmd->args[1])
	{
		pwd = getcwd(NULL, 0);
		if (chdir(cmd->args[1]) == -1)
		{
			ft_error_cd(cmd->args[1], data);
			ft_free(pwd);
		}
		else
		{
			newpwd = getcwd(NULL, 0);
			if (pwd != NULL)
				ft_setenv("OLDPWD", pwd, data);
			if (newpwd != NULL)
				ft_setenv("PWD", newpwd, data);
			data->status = 0;
			(ft_free(pwd), ft_free(newpwd));
		}
	}
}
