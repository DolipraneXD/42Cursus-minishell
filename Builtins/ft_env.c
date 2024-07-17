/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:37:35 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/12 14:13:00 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_cmds *cmd, t_env *env, t_data *data)
{
	t_env	*tmp;

	(void)cmd;
	(void)env;
	tmp = data->env;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	data->status = 0;
}
