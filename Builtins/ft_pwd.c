/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:38:01 by moel-fat          #+#    #+#             */
/*   Updated: 2024/06/07 10:24:06 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_cmds *cmds, t_data *data)
{
	char	*tmp;

	(void)cmds;
	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		ft_putstr_fd(tmp, 1);
		ft_putstr_fd("\n", 1);
		tmp = ft_free(tmp);
		data->status = 0;
	}
	else
	{
		perror("pwd");
		data->status = 1;
	}
	return ;
}
