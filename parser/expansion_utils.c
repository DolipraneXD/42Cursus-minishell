/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:27:52 by ahsadik           #+#    #+#             */
/*   Updated: 2024/07/03 16:24:39 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value(t_data *data, char *str, int var_end)
{
	char	varname;
	char	*value;

	value = NULL;
	varname = str[var_end];
	if (varname == '0')
		value = ft_strdup("minishell");
	else if (ft_isdigit(varname))
		value = ft_strdup("");
	else if (varname == '?')
		value = ft_itoa(data->status);
	return (value);
}

char	*single_var(t_data *data, char *str, int var_start, int var_end)
{
	char	*new_str;
	char	*value;
	char	*part;
	char	*tmp_str;

	value = get_value(data, str, var_end);
	if (!value)
		return (NULL);
	part = ft_substr(str, 0, var_start);
	if (!part)
		return (NULL);
	new_str = ft_strjoin(part, value, 3);
	if (!new_str)
		return (NULL);
	part = ft_substr(str, var_end + 1, ft_strlen(str) - var_end);
	if (!part)
		return (NULL);
	tmp_str = new_str;
	new_str = ft_free(new_str);
	new_str = ft_strjoin(tmp_str, part, 2);
	if (!new_str)
		return (NULL);
	str = ft_free(str);
	return (new_str);
}

char	*get_var_value(char *str, t_data *data, int *i)
{
	int	var_start;

	var_start = (*i)++;
	if (str[*i] == '?' || ft_isdigit(str[*i]))
	{
		str = single_var(data, str, var_start, *i);
		(*i) = var_start - 1;
		if (!str)
			return (NULL);
	}
	else
	{
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			(*i)++;
		str = expand(data, str, var_start, *i);
		(*i) = var_start - 1;
		if (!str)
			return (NULL);
	}
	return (str);
}

char	*ft_getenv(t_env *env, char *var_name)
{
	while (env)
	{
		if (!ft_strncmp(env->name, var_name, ft_strlen(env->name) + 1))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	**expand_args(t_data **data, char **args, int i, int is_exp)
{
	args[i] = check_expand(args[i], *data, &is_exp, 1);
	if (!args[i])
		fexit(data, EXIT_FAILURE);
	if (is_exp && just_space(args[i]))
	{
		ft_free(args[i]);
		args[i] = ft_strdup(" ");
	}
	else if (is_exp && ft_strchr(args[i], ' '))
	{
		args = split_arg(args, i);
		if (!args)
			fexit(data, EXIT_FAILURE);
	}
	return (args);
}
