/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:51:04 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/12 14:14:32 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_list_size(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**ft_lst_to_array(t_env *env)
{
	int		i;
	char	**env_arry;

	i = get_list_size(env);
	env_arry = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_arry)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			env_arry[i] = ft_strjoin(env->name, "=", 0);
			env_arry[i] = ft_strjoin(env_arry[i], env->value, 1);
		}
		else
			env_arry[i] = ft_strjoin(env->name, NULL, 0);
		env = env->next;
		i++;
	}
	env_arry[i] = NULL;
	return (env_arry);
}

char	**ft_find_path(char **env)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			tmp = ft_strdup(env[i] + 5);
			if (!tmp)
				return (NULL);
			path = ft_split(tmp, ':');
			free(tmp);
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	access_exev(t_cmds *cmds, t_data *data)
{
	char	*joined;

	data->i = 0;
	data->flag = 0;
	joined = NULL;
	while (data->path && data->path[data->i])
	{
		joined = ft_strjoin(data->path[data->i], "/", 0);
		joined = ft_strjoin(joined, cmds->args[0], 0);
		if (access(joined, F_OK | X_OK) == 0)
		{
			if (execve(joined, cmds->args, data->env_arry) == -1)
				perror("execve");
			data->flag = 1;
			free(joined);
			break ;
		}
		else
			free(joined);
		data->i++;
	}
	if (data->flag == 0)
		ft_error_cmdnotfound(cmds->args, data);
	return (0);
}

void	ft_execut_multi_helper(t_cmds *cmds, t_data *data, int in_fd)
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	close_heredoc_fds(cmds);
	wait_for_children(data);
	cleanup_environment(data);
}
