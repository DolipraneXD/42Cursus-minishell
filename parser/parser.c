/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:17:25 by ahsadik           #+#    #+#             */
/*   Updated: 2024/07/03 16:16:49 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	join_2d(t_cmds *cmd, char *arg)
{
	int		i;
	char	**new_args;

	i = 0;
	while (cmd->args[i])
		i++;
	new_args = malloc((i + 2) * sizeof(char *));
	if (!new_args)
		return (0);
	i = -1;
	while (cmd->args[++i])
		new_args[i] = cmd->args[i];
	cmd->args = ft_free(cmd->args);
	new_args[i++] = arg;
	new_args[i] = NULL;
	cmd->args = new_args;
	return (1);
}

t_cmds	*setdefaultio(t_data **data, t_cmds *cmd, int return_cmd)
{
	t_cmds	*new_cmd;

	if (!cmd->infile)
		cmd->infile = ft_filenew(NULL, STDIN, 1, 0);
	if (!cmd->outfile)
		cmd->outfile = ft_filenew(NULL, STDOUT, 1, 0);
	if (!cmd->infile || !cmd->outfile)
		fexit(data, EXIT_FAILURE);
	ft_cmdadd_back((*data)->cmds, cmd);
	if (return_cmd)
	{
		new_cmd = ft_cmdnew();
		if (!new_cmd)
			fexit(data, EXIT_FAILURE);
		return (new_cmd);
	}
	return (NULL);
}

static t_cmds	*join_arg(t_data **data, t_cmds *cmd, char *token)
{
	if (!token)
		fexit(data, EXIT_FAILURE);
	if (!cmd->args)
	{
		cmd->args = malloc (2 * sizeof(char *));
		if (!cmd->args)
			fexit(data, EXIT_FAILURE);
		cmd->args[0] = token;
		cmd->args[1] = NULL;
		return (cmd);
	}
	if (!join_2d(cmd, token))
		fexit(data, EXIT_FAILURE);
	return (cmd);
}

static t_cmds	*set_cmds(t_data **data,
	t_cmds *cmd, t_tokens *token, int rf_index)
{
	t_file	*red;

	if (token->type == COMMAND)
		cmd->cmd = NULL;
	if (token->type >= COMMAND && token->type <= ASSIGN)
		cmd = join_arg(data, cmd, ft_strdup(token->token));
	else if ((token->type == ROUT || token->type == RAPPEND) && token->next)
	{
		red = ft_filenew(ft_strdup(token->next->token),
				token->type - 4, 0, rf_index);
		if (!red)
			fexit(data, EXIT_FAILURE);
		ft_fileadd_back(&cmd->outfile, red);
	}
	else if ((token->type == RIN || token->type == RHEREDOC) && token->next)
	{
		red = ft_filenew(ft_strdup(token->next->token),
				token->type - 4, 0, rf_index);
		if (!red)
			fexit(data, EXIT_FAILURE);
		ft_fileadd_back(&cmd->infile, red);
	}
	else if (token->type == PIPE)
		cmd = setdefaultio(data, cmd, 1);
	return (cmd);
}

int	parser(t_data **data)
{
	t_cmds		*cmd_node;
	t_tokens	*token;
	int			is_first;
	int			red_index;

	is_first = 1;
	red_index = 1;
	if (!*(*data)->tokens)
		return (0);
	token = *(*data)->tokens;
	while (token)
	{
		if (is_first)
		{
			cmd_node = ft_cmdnew();
			if (!cmd_node)
				return (1);
			is_first = 0;
		}
		cmd_node = set_cmds(data, cmd_node, token,
				get_red_index(token, &red_index));
		token = token->next;
	}
	setdefaultio(data, cmd_node, 0);
	return (0);
}
