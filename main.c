/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:30:02 by ahsadik           #+#    #+#             */
/*   Updated: 2024/07/12 14:28:42 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_data	*data_grep(t_data *data)
{
	static t_data	*_data;

	if (data != NULL)
		_data = data;
	return (_data);
}

int	main(int arc, char **arv, char **envp)
{
	char		*cmd;
	t_cmds		*cmds;
	t_tokens	*tokens;
	t_data		*data;

	(void)arc;
	(void)arv;
	data = malloc(sizeof(t_data));
	(1) && (data->status = 0, cmds = NULL, tokens = NULL, data->env = NULL);
	data->env = make_env(&data->env, envp);
	data_grep(data);
	reset_tty();
	signals_hand();
	while (1)
	{
		cmd = readline("msh$> ");
		if (cmd && *cmd)
			add_history(cmd);
		if (!parseit(&tokens, &cmds, &data, cmd))
			ft_execut(cmds, data);
		free_cmds(&cmds);
		ft_lstclear(&tokens);
		cmd = ft_free(cmd);
	}
	return (0);
}
