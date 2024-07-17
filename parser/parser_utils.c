/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:16:12 by ahsadik           #+#    #+#             */
/*   Updated: 2024/07/12 14:10:26 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand(t_data *data, char *str, int var_start, int var_end)
{
	char	*new_str;
	char	*value;
	char	*beforev;
	char	*afterv;
	char	*var_name;

	var_name = ft_substr(str, var_start + 1, var_end - (var_start + 1));
	if (!var_name)
		return (NULL);
	value = ft_getenv(data->env, var_name);
	var_name = ft_free(var_name);
	beforev = ft_substr(str, 0, var_start);
	if (!beforev)
		return (NULL);
	afterv = ft_substr(str, var_end, ft_strlen(str) - var_end);
	if (!afterv)
		return (NULL);
	new_str = ft_strjoin(beforev, value, 1);
	if (!new_str)
		return (NULL);
	str = ft_free(str);
	str = ft_strjoin(new_str, afterv, 3);
	if (!str)
		return (NULL);
	return (str);
}

int	skip_quotes(char *str, int *i, int open2quotes)
{
	if (str[*i] == 34)
	{
		open2quotes *= -1;
		(*i)++;
	}
	while (str[*i] == 39 && open2quotes < 0)
	{
		(*i)++;
		while (str[*i] && str[*i] != 39)
			(*i)++;
		(*i)++;
	}
	if (str[*i] == 34)
	{
		open2quotes *= -1;
		(*i)++;
	}
	return (open2quotes);
}

char	**split_arg(char **args, int i)
{
	int		c;
	int		j;
	char	**split_arg;
	char	**new_args;

	split_arg = ft_split(args[i], ' ');
	if (!split_arg)
		return (NULL);
	args[i] = ft_free(args[i]);
	c = count2d(split_arg);
	new_args = malloc((i + c + 1) * sizeof(char *));
	if (!new_args)
		return (NULL);
	j = -1;
	while (++j < i)
		new_args[j] = args[j];
	args = ft_free(args);
	c = 0;
	while (split_arg[c])
		new_args[j++] = split_arg[c++];
	split_arg = ft_free(split_arg);
	new_args[j] = NULL;
	return (new_args);
}

int	notempty(char *arg)
{
	char	*tmp;

	if (ft_strncmp("\"''\"", arg, 5) == 0 || ft_strncmp("'\"\"'", arg, 5) == 0)
		return (0);
	if (ft_strlen(arg) < 2 || arg[0] != arg[1]
		|| (arg[0] != 39 && arg[0] != 34))
		return (1);
	tmp = rm_quotes(arg, 0);
	if (tmp && !tmp[0])
		return (ft_free(tmp), 0);
	tmp = ft_free(tmp);
	return (1);
}

int	get_red_index(t_tokens *token, int *red_index)
{
	if (token->type == RFILE)
		(*red_index)++;
	else if (token->type == PIPE)
		*red_index = 1;
	return (*red_index);
}
