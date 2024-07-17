/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 00:28:23 by ahsadik           #+#    #+#             */
/*   Updated: 2024/06/26 17:59:18 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	startswith(char *cmd, char character, int i)
{
	int	tmp;

	tmp = 0;
	if (cmd[tmp] == character)
		return (1);
	while (cmd[tmp] == 34)
		tmp++;
	if (cmd[tmp] == character)
		return (1);
	while (cmd[i] == 39)
		i++;
	if (cmd[i] == character)
		return (1);
	return (0);
}

int	add_token(t_data **data, char *token, int type)
{
	t_tokens	**tokens;
	t_tokens	*node_token;

	if (!data || !(*data))
		return (1);
	tokens = (*data)->tokens;
	node_token = ft_lstnew(token, type);
	if (!node_token || !token)
		fexit(data, EXIT_FAILURE);
	if (!*tokens)
		*tokens = node_token;
	else
		ft_lstadd_back(tokens, node_token);
	return (0);
}

int	synerror(t_data **data, t_tokens *token, int errno)
{
	if (errno == AMBGS)
		ft_putstr_fd("ambiguous redirect\n", STDERR_FILENO);
	else if (errno == UQUOTES)
		ft_putstr_fd("syntax error unclosed quotes\n", STDERR_FILENO);
	else if (errno == UNEXP)
	{
		if (token)
		{
			ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
			ft_putstr_fd(token->token, STDERR_FILENO);
			ft_putstr_fd("`\n", STDERR_FILENO);
		}
		else
			ft_putstr_fd("syntax error near unexpected token `new line`\n",
				STDERR_FILENO);
	}
	ft_lstclear((*data)->tokens);
	if (errno > AMBGS)
		(*data)->status = 258;
	else
		(*data)->status = 1;
	return (1);
}

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	fexit(t_data **data, int exit_status)
{
	if (data && *data)
	{
		if ((*data)->cmd)
			(*data)->cmd = ft_free((*data)->cmd);
		if ((*data)->tokens)
			ft_lstclear((*data)->tokens);
		if ((*data)->cmds)
			free_cmds((*data)->cmds);
		*data = ft_free(*data);
	}
	exit(exit_status);
}
