/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:57:54 by jdiaz             #+#    #+#             */
/*   Updated: 2019/05/19 16:59:05 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\njdiaz@my_shell > ");
		signal(SIGINT, signal_handler);
	}
}
