/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:22:36 by jdiaz             #+#    #+#             */
/*   Updated: 2019/05/19 17:20:34 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_func	get_fn(t_minishell *shell)
{
	int				i;
	static	t_fns	fns[5] = {
		{ .command = "echo", .fn = echo_fn },
		{ .command = "cd", .fn = cd_fn },
		{ .command = "setenv", .fn = setenv_fn },
		{ .command = "unsetenv", .fn = unsetenv_fn },
		{ .command = "env", .fn = env_fn}};

	i = -1;
	while (++i < 5)
		if (ft_strcmp(shell->args[0], fns[i].command) == 0)
			return (fns[i].fn);
	return (NULL);
}
