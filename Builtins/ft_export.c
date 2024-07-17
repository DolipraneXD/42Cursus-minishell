/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:37:51 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/12 14:13:07 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_get_env_value(char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_add_env2(char *name, char *value, t_env **env, int flag)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (flag == 2)
				tmp->value = ft_strdup(value);
			else if (flag == 0)
				return ;
			else
			{
				tmp->value = ft_free(tmp->value);
				if (value)
					tmp->value = ft_strdup(value);
				else
					tmp->value = NULL;
			}
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back_mini(env, ft_lstnew_mini(name, value));
}

static void	ft_export_partone(t_cmds *cmds, t_env **env, int i)
{
	char	*name;
	char	*value;

	name = ft_substr(cmds->args[i], 0,
			ft_strchr(cmds->args[i], '=') - cmds->args[i]);
	value = ft_strchr(cmds->args[i], '=') + 1;
	ft_add_env2(name, value, env, 1);
	name = ft_free(name);
}

static void	ft_export_parttwo(t_cmds *cmds, t_env **env, int i)
{
	char	*name;
	char	*value;
	char	*old_value;
	char	*new_value;

	name = ft_substr(cmds->args[i], 0,
			ft_strchr(cmds->args[i], '+') - cmds->args[i]);
	value = ft_strdup(ft_strchr(cmds->args[i], '+') + 2);
	if (value && value[0] == '\0')
	{
		name = ft_free(name);
		value = ft_free(value);
		return ;
	}
	old_value = ft_get_env_value(name, *env);
	if (old_value)
	{
		new_value = ft_strjoin(old_value, value, 1);
		ft_add_env2(name, new_value, env, 2);
		ft_free(new_value);
	}
	else
		ft_add_env2(name, value, env, 2);
	name = ft_free(name);
	value = ft_free(value);
}

void	ft_export(t_cmds *cmds, t_env **env, t_data *data)
{
	int	i;
	int	flag;

	(1) && (i = 1, flag = 0);
	if (cmds->args[1] == NULL || cmds->args[1][0] == '\0')
		ft_print_export(*env);
	else
	{
		while (cmds->args[i])
		{
			if (ft_isvalid_identifier(cmds->args[i]))
			{
				flag = ft_find_plusequal(cmds->args[i]);
				if (flag == 1)
					ft_export_partone(cmds, env, i);
				else if (flag == 2)
					ft_export_parttwo(cmds, env, i);
				else
					ft_add_env2(cmds->args[i], NULL, env, flag);
			}
			else
				ft_error_identifier(cmds->args[i], data, 1);
			i++;
		}
	}
}
