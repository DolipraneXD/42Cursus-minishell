/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtinutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:51:55 by moel-fat          #+#    #+#             */
/*   Updated: 2024/06/04 14:59:37 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstadd_back_mini(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*ft_lstnew_mini(char *name, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node)
	{
		new_node->name = ft_strdup(name);
		if (value)
			new_node->value = ft_strdup(value);
		else
			new_node->value = NULL;
		new_node->next = NULL;
	}
	return (new_node);
}

void	ft_setenv(char *name, char *value, t_data *data)
{
	t_env	*tmp;
	t_env	*new;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new = ft_lstnew_mini(name, NULL);
	new->value = ft_strdup(value);
	ft_lstadd_back_mini(&(data->env), new);
}

void	ft_free_list_env(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*env = NULL;
}

void	ft_error_identifier(char *str, t_data *data, int flag)
{
	if (flag == 1)
		ft_putstr_fd("minishell: export: `", 2);
	else if (flag == 2)
		ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	data->status = 1;
}
