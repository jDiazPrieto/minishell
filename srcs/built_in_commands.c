/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 20:00:40 by jdiaz             #+#    #+#             */
/*   Updated: 2019/05/21 19:48:10 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		cd_fn(t_minishell *ob)
{
	char	*cwd;
	char	buff[4097];
	char	*tmp;
	int		result;

	cwd = getcwd(buff, 4096);
	tmp = ob->args[1] && ft_strcmp(ob->args[1], "-") == 0 ?
		get_env_var("OLDPWD", ob) : get_env_var("HOME", ob);
	result = ob->args[1] && ft_strcmp(ob->args[1], "-") ?
		chdir(ob->args[1]) : chdir(tmp);
	if (!result)
		set_env_var("OLDPWD", cwd, ob);
	else
	{
		if (access(tmp, F_OK) == -1)
			ft_putstr("cd: no such file or directory: ");
		else if (access(tmp, R_OK) == -1)
			ft_putstr("cd: permission denied: ");
		else
			ft_putstr("cd: not a directory: ");
		ft_putendl(ob->args[1]);
	}
	free(tmp);
	return (ob->status);
}

int		setenv_fn(t_minishell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	if (shell->args[1] == NULL || shell->args[2] == NULL)
		return (env_fn(shell));
	else if (shell->args[3])
	{
		ft_putendl("setenv: Too many arguments");
		return (1);
	}
	else if ((tmp = get_env_var(shell->args[1], shell)) != NULL)
	{
		free(tmp);
		return (set_env_var(shell->args[1], shell->args[2], shell));
	}
	while (shell->envv[i])
		i++;
	realloc_envv(i + 1, shell);
	tmp = ft_strjoin(shell->args[1], "=");
	shell->envv[i] = ft_strjoin(tmp, shell->args[2]);
	free(tmp);
	return (shell->status);
}

int		remove_env(t_minishell *shell)
{
	int		i;
	int		update;
	char	**split;

	i = -1;
	update = 0;
	while (shell->envv[++i])
	{
		split = ft_strsplit(shell->envv[i], '=');
		if (ft_strcmp(split[0], shell->args[1]) == 0)
		{
			update = 1;
			free(shell->envv[i]);
		}
		shell->envv[i] = shell->envv[i + update];
		free_split(split);
	}
	realloc_envv(i - update, shell);
	return (shell->status);
}

int		unsetenv_fn(t_minishell *shell)
{
	char	*tmp;

	if (!shell->args[1])
	{
		ft_putendl("unetenv: Too few arguements");
		return (1);
	}
	tmp = get_env_var(shell->args[1], shell);
	if (!tmp)
		return (1);
	free(tmp);
	return (remove_env(shell));
}

int		env_fn(t_minishell *shell)
{
	int		i;

	i = 0;
	while (shell->envv[i])
	{
		ft_putendl(shell->envv[i]);
		i++;
	}
	return (shell->status);
}
