/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:54:01 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/03 15:56:48 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_ambgred(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}

int	open_outfile(t_file *outfile)
{
	int	fd;

	if (check_ambgred(outfile->filename) && outfile->is_exp == 1)
	{
		if (outfile->quotes != true)
		{
			ft_error_ambiguous_redirect(outfile->filename);
			return (-1);
		}
	}
	fd = open(outfile->filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error_open(outfile->filename);
	return (fd);
}

int	open_append(t_file *outfile)
{
	int	fd;

	if (check_ambgred(outfile->filename) && outfile->is_exp == 1)
	{
		if (outfile->quotes != true)
		{
			ft_error_ambiguous_redirect(outfile->filename);
			return (-1);
		}
	}
	fd = open(outfile->filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_error_open(outfile->filename);
	return (fd);
}

int	open_infile(t_file *infile)
{
	int	fd;

	if (check_ambgred(infile->filename) && infile->is_exp == 1)
	{
		if (infile->quotes != true)
		{
			ft_error_ambiguous_redirect(infile->filename);
			return (-1);
		}
	}
	fd = open(infile->filename, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_error_open(infile->filename);
		return (-1);
	}
	return (fd);
}
