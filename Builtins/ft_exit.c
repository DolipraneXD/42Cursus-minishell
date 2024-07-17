/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:37:45 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/12 14:13:03 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_isnumber(char *str)
{
	int		i;
	char	*tmp;

	if (str[0] == '\0' || just_space(str) == 1)
		return (0);
	tmp = ft_strtrim(str, " ");
	i = 0;
	if (tmp[i] == '-' || tmp[i] == '+')
		i++;
	while (tmp[i])
	{
		if (!ft_isdigit(tmp[i]))
		{
			tmp = ft_free(tmp);
			return (0);
		}
		i++;
	}
	tmp = ft_free(tmp);
	return (1);
}

static void	print_error_cd(char *str)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

static long int	ft_atoil(char *str)
{
	int					i;
	int					sign;
	unsigned long long	rest;

	i = 0;
	rest = 0;
	sign = 1;
	while (str[i] != '\0' && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		rest = rest * 10 + (str[i] - '0');
		if ((rest > 9223372036854775808ULL) && sign == -1)
			print_error_cd(str);
		if (rest > LONG_MAX && sign == 1)
			print_error_cd(str);
		i++;
	}
	return (rest * sign);
}

static void	exit_tool(char *str)
{
	int	i;

	i = ft_atoil(str);
	ft_putstr_fd("exit\n", 2);
	exit(i);
}

void	ft_exit(t_cmds *cmd, t_data *data)
{
	if (cmd->args[1] != NULL)
	{
		if (ft_isnumber(cmd->args[1]))
		{
			if (cmd->args[2] != NULL)
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				data->status = 1;
			}
			else
				exit_tool(cmd->args[1]);
		}
		else
			print_error_cd(cmd->args[1]);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit(data->status);
	}
}
