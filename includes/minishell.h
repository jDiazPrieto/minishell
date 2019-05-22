/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:37:00 by jdiaz             #+#    #+#             */
/*   Updated: 2019/05/19 16:57:42 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>

typedef	struct		s_minishell
{
	char	*line;
	char	**args;
	int		status;
	char	**envv;
}						t_minishell;

typedef int			(*t_func)(t_minishell *shell);

typedef struct		s_fns
{
	char	*command;
	t_func	fn;
}					t_fns;

int					parse_command(t_minishell *shell);		
int					execute_command(t_minishell *shell);

t_func				get_fn(t_minishell *shell);

// command functions
int					echo_fn(t_minishell *shell);
int					cd_fn(t_minishell *shell);
int					setenv_fn(t_minishell *shell);
int					unsetenv_fn(t_minishell *shell);
int					env_fn(t_minishell *shell);

// environment
char				*get_env_var(char *env, t_minishell *shell);
int					set_env_var(char *env, char *value, t_minishell *shell);
int					realloc_envv(int new_size, t_minishell *shell);
char				**copy_env(char **envv);

// memory
void				free_split(char **split);

//signals
void				signal_handler(int signo);
#endif
