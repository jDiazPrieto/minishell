/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:52:14 by jdiaz             #+#    #+#             */
/*   Updated: 2019/05/19 17:19:30 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		fork_process(char *executable, t_minishell *shell)
{
	pid_t		pid;
	struct stat f;

	lstat(executable, &f);
	if (!(f.st_mode & S_IXUSR))
	{
		ft_putstr("minishell: permission denied: ");
		ft_putendl(executable);
		free(executable);
		return (1);
	}
	pid = fork();
	if (pid == 0)
		execve(executable, shell->args, shell->envv);
	if (pid > 0)
		wait(&pid);
	free(executable);
	return (1);
}

int		command_in_path(char *dir_path, char *command)
{
	struct stat	f;
	char		*full_path;
	char		*tmp;
	int			result;

	result = 0;
	tmp = ft_strjoin(dir_path, "/");
	full_path = ft_strjoin(tmp, command);
	if (lstat(full_path, &f) != -1)
		result = 1;
	free(tmp);
	free(full_path);
	return (result);
}

int		is_executable(char *filepath)
{
	struct stat f;

	if (lstat(filepath, &f) == -1)
		return (0);
	if (f.st_mode & S_IXUSR)
		return (1);
	return (0);
}

int		find_command(t_minishell *shell, char *path_env)
{
	char	**paths;
	int		i;
	char	*tmp;

	paths = ft_strsplit(path_env, ':');
	free(path_env);
	i = -1;
	while (paths[++i] != NULL)
		if (command_in_path(paths[i], shell->args[0]))
		{
			tmp = ft_strjoin(paths[i], "/");
			fork_process(ft_strjoin(tmp, shell->args[0]), shell);
			free(tmp);
			break ;
		}
	if (paths[i] == NULL)
	{
		ft_putstr("zsh: command not found: ");
		ft_putendl(shell->args[0]);
	}
	free_split(paths);
	return (1);
}

int		execute_command(t_minishell *shell)
{
	t_func	fn;
	char	*path_env;
	int		i;

	if (shell->args[0] == NULL)
		return (1);
	fn = get_fn(shell);
	if (ft_strcmp(shell->args[0], "exit") == 0)
		return (0);
	if (fn)
		return (fn(shell));
	i = 0;
	if (is_executable(shell->args[0]))
		return (fork_process(ft_strdup(shell->args[0]), shell));
	path_env = get_env_var("PATH", shell);
	if (!path_env)
		path_env = ft_strdup("");
	return (find_command(shell, path_env));
}
