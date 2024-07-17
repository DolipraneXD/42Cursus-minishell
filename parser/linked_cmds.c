/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:45:20 by ahsadik           #+#    #+#             */
/*   Updated: 2024/07/02 15:18:31 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmds	*ft_cmdnew(void)
{
	t_cmds	*one;

	one = malloc(sizeof(t_cmds));
	if (!one)
		return (NULL);
	one->args = NULL;
	one->cmd = NULL;
	one->infile = NULL;
	one->outfile = NULL;
	one->iofiles = NULL;
	one->next = NULL;
	one->next = 0;
	return (one);
}

static t_cmds	*ft_cmdlast(t_cmds *lst)
{
	t_cmds	*ptr;

	ptr = lst;
	while (ptr)
	{
		if (ptr->next)
			ptr = ptr->next;
		else
			break ;
	}
	return (ptr);
}

void	ft_cmdadd_back(t_cmds **lst, t_cmds *new)
{
	t_cmds	*ptr;

	ptr = ft_cmdlast(*lst);
	if (ptr)
		ptr->next = new;
	else
		*lst = new;
}
