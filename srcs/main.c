/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 08:38:26 by jdiaz             #+#    #+#             */
/*   Updated: 2019/05/19 17:18:05 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		free_split(char **split)
{
	int i;

	i = -1;
	if (split)
		while (split[++i])
			free(split[i]);
	free(split);
}

t_minishell	*init_shell(char **envv)
{
	t_minishell *shell;

	shell = (t_minishell *)malloc(sizeof(t_minishell));
	if (shell == NULL)
		return (NULL);
	shell->line = NULL;
	shell->args = NULL;
	shell->status = 1;
	shell->envv = copy_env(envv);
	return (shell);
}

int			main(int argc, char **argv, char **envv)
{
	t_minishell *shell;

	shell = init_shell(envv);
	while (shell->status != 0)
	{
		ft_putstr("jdiaz@my_shell > ");
		signal(SIGINT, signal_handler);
		get_next_line(0, &(shell->line));
		parse_command(shell);
		shell->status = execute_command(shell);
		free_split(shell->args);
		free(shell->line);
	}
	argv = NULL;
	argc = 1;
	return (0);
}
