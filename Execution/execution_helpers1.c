/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:16:48 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/01 15:50:01 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_non_empty_args(char **args)
{
	int	count;
	int	non_empty_count;

	count = 0;
	non_empty_count = 0;
	while (args[count] != NULL)
	{
		if (ft_strcmp(args[count], "") != 0)
			non_empty_count++;
		count++;
	}
	return (non_empty_count);
}

// Function to allocate memory for new arguments array
char	**allocate_new_args(int non_empty_count)
{
	char	**new_args;

	new_args = malloc((non_empty_count + 1) * sizeof(char *));
	if (new_args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (new_args);
}

// Function to copy a single argument
void	copy_argument(char **new_args, char *arg, int index)
{
	int	k;

	k = 0;
	new_args[index] = ft_strdup(arg);
	if (new_args[index] == NULL)
	{
		perror("strdup");
		while (k < index)
		{
			ft_free(new_args[k]);
			k++;
		}
		ft_free(new_args);
		exit(EXIT_FAILURE);
	}
}

// Function to copy non-empty arguments to a new array
char	**copy_non_empty_args(char **args, int non_empty_count)
{
	char	**new_args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_args = allocate_new_args(non_empty_count);
	while (args[i] != NULL)
	{
		if (strcmp(args[i], "") != 0)
		{
			copy_argument(new_args, args[i], j);
			j++;
		}
		i++;
	}
	new_args[j] = NULL;
	return (new_args);
}

// Main function to remove empty arguments from array
char	**remove_empty_args(t_cmds *cmd)
{
	char	**new_args;
	int		non_empty_count;
	int		i;

	if (cmd == NULL || cmd->args == NULL)
		return (NULL);
	non_empty_count = count_non_empty_args(cmd->args);
	new_args = copy_non_empty_args(cmd->args, non_empty_count);
	i = 0;
	while (cmd->args[i] != NULL)
	{
		cmd->args[i] = ft_free(cmd->args[i]);
		i++;
	}
	ft_free(cmd->args);
	return (new_args);
}
