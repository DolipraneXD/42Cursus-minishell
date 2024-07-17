/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:08:22 by moel-fat          #+#    #+#             */
/*   Updated: 2024/06/04 15:08:34 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_env_var(t_env **env, const char *name, const char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	ft_lstadd_back_mini(env, new);
}

void	make_backup_env(t_env **env)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	add_env_var(env, "PWD", cwd);
	add_env_var(env, "PATH", "/usr/bin:/bin:/usr/sbin:/sbin");
	add_env_var(env, "OLDPWD", cwd);
	add_env_var(env, "SHLVL", "1");
	add_env_var(env, "_", "/usr/bin/env");
}

static void	ft_error_env(int i)
{
	if (i == 0)
		ft_putstr_fd("Error: Invalid environment variable format\n", 2);
	else if (i == 1)
		perror("malloc");
	exit(EXIT_FAILURE);
}

t_env	*make_env(t_env **env, char **envp)
{
	int		i;
	char	*tmp;
	t_env	*new;

	i = 0;
	if (!envp || !*envp)
		make_backup_env(env);
	while (envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			ft_error_env(1);
		tmp = ft_strchr(envp[i], '=');
		if (!tmp)
			ft_error_env(0);
		new->name = ft_substr(envp[i], 0, tmp - envp[i]);
		new->value = ft_strdup(tmp + 1);
		new->next = NULL;
		ft_lstadd_back_mini(env, new);
		i++;
	}
	return (*env);
}

void	ft_printlist(t_env *env)
{
	while (env)
	{
		printf("name: %s\n", env->name);
		printf("value: %s\n", env->value);
		env = env->next;
	}
}
