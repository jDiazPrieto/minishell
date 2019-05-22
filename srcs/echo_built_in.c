/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 14:26:26 by jdiaz             #+#    #+#             */
/*   Updated: 2019/05/19 17:15:40 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	write_echo(char *str, char quote)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote && (str[i] == quote))
			quote = 0;
		else
		{
			ft_putchar(str[i]);
		}
		i++;
	}
	return (quote);
}

int		echo_fn(t_minishell *shell)
{
	int		flag;
	int		i;
	char	quote;

	if (shell->args[1] == NULL)
	{
		ft_putstr("\n");
		return (1);
	}
	flag = ft_strcmp(shell->args[1], "-n") == 0 ? 1 : 0;
	i = 1;
	quote = 0;
	while (shell->args[i])
	{
		quote = write_echo(shell->args[i], quote);
		if (shell->args[i + 1])
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (1);
}
