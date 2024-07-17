/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:17:17 by ahsadik           #+#    #+#             */
/*   Updated: 2024/07/03 16:23:15 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_file	*ft_filenew(char *file, int type, int arg1null, int rf_index)
{
	t_file	*one;

	if (!file && !arg1null)
		return (NULL);
	one = malloc(sizeof(t_file));
	if (!one)
		return (NULL);
	one->filename = file;
	one->hd_fd = -1;
	one->is_exp = false;
	one->quotes = false;
	one->type = type;
	one->index = rf_index;
	one->next = NULL;
	return (one);
}

static t_file	*ft_filelast(t_file *lst)
{
	t_file	*ptr;

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

void	ft_fileadd_back(t_file **lst, t_file *new)
{
	t_file	*ptr;

	ptr = ft_filelast(*lst);
	if (ptr)
		ptr->next = new;
	else
		*lst = new;
}

void	ft_fileclear(t_file **lst)
{
	t_file	*ptr;
	t_file	*tmp_ptr;

	if (!lst)
		return ;
	ptr = *lst;
	while (ptr)
	{
		tmp_ptr = ptr->next;
		if (ptr->type >= OUTFILE)
			ptr->filename = ft_free(ptr->filename);
		ptr = ft_free(ptr);
		ptr = tmp_ptr;
	}
	*lst = ptr;
}

t_file	*file_copy(t_data **data, t_file *file)
{
	t_file	*tmp_file;

	tmp_file = ft_filenew(ft_strdup(file->filename),
			file->type, 0, file->index);
	if (!tmp_file)
		fexit(data, EXIT_FAILURE);
	tmp_file->hd_fd = file->hd_fd;
	tmp_file->is_exp = file->is_exp;
	tmp_file->quotes = file->quotes;
	return (tmp_file);
}
