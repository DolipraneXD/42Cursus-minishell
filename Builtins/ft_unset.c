/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:38:05 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/12 14:13:15 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_isvalid_identifier_unset(char *str)
{
	int	i;

	i = 1;
	if (str == NULL)
		return (1);
	if ((!ft_isalpha(str[0]) && str[0] != '_') || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && !ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env_variable(t_env **env, char *arg)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, arg) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			tmp->name = ft_free(tmp->name);
			tmp->value = ft_free(tmp->value);
			tmp = ft_free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset(t_cmds *cmd, t_data *data)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!ft_isvalid_identifier_unset(cmd->args[i]))
		{
			ft_error_identifier(cmd->args[i], data, 2);
			data->status = 1;
		}
		else
		{
			remove_env_variable(&data->env, cmd->args[i]);
		}
		i++;
	}
}
