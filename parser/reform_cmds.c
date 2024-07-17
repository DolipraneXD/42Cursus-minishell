/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reform_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:45:20 by ahsadik           #+#    #+#             */
/*   Updated: 2024/07/12 14:10:35 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmds	*reform_cmds(t_data **data, t_cmds *tmp_cmd)
{
	if (tmp_cmd->args)
	{
		tmp_cmd->args = reform_args(data, tmp_cmd->args);
		tmp_cmd->cmd = tmp_cmd->args[0];
	}
	if (tmp_cmd->infile->type == INFILE)
		tmp_cmd->infile = reform_redfile(data, tmp_cmd->infile);
	if (tmp_cmd->outfile->type != STDOUT)
		tmp_cmd->outfile = reform_redfile(data, tmp_cmd->outfile);
	return (tmp_cmd);
}

char	**reform_args(t_data **data, char **args)
{
	int	i;
	int	is_exp;

	if (!args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		is_exp = 0;
		if (ft_strchr(args[i], '$'))
			args = expand_args(data, args, i, is_exp);
		if (notempty(args[i]))
		{
			args[i] = rm_quotes(args[i], 1);
			if (!args[i])
				fexit(data, EXIT_FAILURE);
		}
		i++;
	}
	return (args);
}

t_file	*reform_redfile(t_data **data, t_file *file)
{
	char	*tmp;
	t_file	*tmpf;

	tmpf = file;
	while (tmpf)
	{
		if (ft_strchr(tmpf->filename, '$'))
		{
			tmp = ft_strdup(tmpf->filename);
			tmpf->filename = check_expand(tmpf->filename, *data, NULL, 0);
			if (!tmpf->filename || !tmp)
				fexit(data, EXIT_FAILURE);
			if (ft_strncmp(tmp, tmpf->filename, ft_strlen(tmpf->filename) + 1))
				tmpf->is_exp = true;
			tmp = ft_free(tmp);
		}
		tmp = rm_quotes(tmpf->filename, 1);
		if (!tmp)
			fexit(data, EXIT_FAILURE);
		if (ft_strncmp(tmp, tmpf->filename, ft_strlen(tmpf->filename) + 1))
			tmpf->quotes = true;
		tmpf->filename = tmp;
		tmpf = tmpf->next;
	}
	return (file);
}

void	merge_red(t_data **data, int status)
{
	t_cmds	*tmp_cmd;

	tmp_cmd = *(*data)->cmds;
	while (tmp_cmd && !status)
	{
		tmp_cmd->iofiles = merge_io(data, tmp_cmd);
		tmp_cmd = tmp_cmd->next;
	}
}

t_file	*merge_io(t_data **data, t_cmds *tmp_cmd)
{
	int		i;
	t_file	*in;
	t_file	*out;
	t_file	*iofiles;

	(1) && (i = 1, iofiles = NULL, in = tmp_cmd->infile,
			out = tmp_cmd->outfile);
	if (syntaxerr(*(*data)->tokens))
		return (NULL);
	while ((in && in->type != STDIN) || (out && out->type != STDOUT))
	{
		while (in && in->index == i && i++)
		{
			ft_fileadd_back(&iofiles, file_copy(data, in));
			in = in->next;
		}
		while (out && out->index == i && i++)
		{
			ft_fileadd_back(&iofiles, file_copy(data, out));
			out = out->next;
		}
	}
	return (iofiles);
}
