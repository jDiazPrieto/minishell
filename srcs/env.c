/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:05:01 by jdiaz             #+#    #+#             */
/*   Updated: 2019/05/19 17:22:39 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_var(char *env, t_minishell *shell)
{
	char	*env_value;
	char	**split;
	int		i;

	i = 0;
	env_value = NULL;
	while (shell->envv[i] != NULL)
	{
		split = ft_strsplit(shell->envv[i], '=');
		if (split[0] && ft_strcmp(split[0], env) == 0)
			env_value = ft_strdup(split[1]);
		free_split(split);
		i++;
	}
	return (env_value);
}

int		set_env_var(char *env, char *new_value, t_minishell *shell)
{
	int		i;
	char	*value;
	char	**split;

	i = 0;
	while (shell->envv[i] != NULL)
	{
		split = ft_strsplit(shell->envv[i], '=');
		if (split[0] && ft_strcmp(split[0], env) == 0)
		{
			free(shell->envv[i]);
			shell->envv[i] = ft_strjoin(env, "=");
			value = ft_strjoin(shell->envv[i], new_value);
			free(shell->envv[i]);
			shell->envv[i] = value;
		}
		free_split(split);
		i++;
	}
	return (i);
}

int		realloc_envv(int new_size, t_minishell *shell)
{
	char	**new;
	int		i;

	new = (char **)ft_memalloc(sizeof(char *) * (new_size + 1));
	i = 0;
	while (shell->envv[i] && i < new_size)
	{
		new[i] = ft_strdup(shell->envv[i]);
		free(shell->envv[i]);
		i++;
	}
	free(shell->envv);
	shell->envv = new;
	return (1);
}

char	**copy_env(char **env)
{
	char	**new;
	int		length;

	length = 0;
	while (env[length])
		length++;
	new = (char **)malloc(sizeof(char *) * length + 1);
	length = 0;
	while (env[length])
	{
		new[length] = ft_strdup(env[length]);
		length++;
	}
	return (new);
}
