/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:35:25 by jdiaz             #+#    #+#             */
/*   Updated: 2019/05/21 20:10:28 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	multi_num_words(char const *s, char c, char d)
{
	int len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		while (*s != '\0' && *s != c && *s != d)
			s++;
		while (*s == c || *s == d)
			s++;
	}
	return (len);
}

static char	**multi_get_words(char **result, char const *s, char *st, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		while (s[i] != '\0' && s[i] != st[0] && s[i] != st[1])
			i++;
		result[j] = ft_strnew(i + 1);
		result[j] = ft_strncpy(result[j], s, i);
		result[j][i] = '\0';
		s += i;
		i = 0;
		j++;
		while (*s == st[0] || *s == st[1])
			s++;
	}
	result[j] = NULL;
	return (result);
}

char		**ft_multisplit(char const *s, char *str)
{
	char	**result;
	int		len;

	if (!s)
		return (NULL);
	while (*s == str[0] || *s == str[1])
		s++;
	len = multi_num_words(s, str[0], str[1]);
	result = (char **)malloc(sizeof(char *) * len + 1);
	if (!result)
		return (NULL);
	result = multi_get_words(result, s, str, len);
	return (result);
}

char		*sub_env_var(t_minishell *shell, int i)
{
	char *tmp;

	tmp = get_env_var(shell->args[i] + 1, shell);
	free(shell->args[i]);
	if (tmp == NULL)
		return (ft_strdup(""));
	return (tmp);
}

int			parse_command(t_minishell *shell)
{
	int		i;
	char	*tmp;
	char	*home;

	i = 0;
	shell->args = ft_multisplit(shell->line, " \t");
	if (shell->args == NULL)
		exit(0);
	while (shell->args[i])
	{
		if (shell->args[i][0] == '~')
		{
			home = get_env_var("HOME", shell);
			tmp = ft_strjoin(home, shell->args[i] + 1);
			free(home);
			free(shell->args[i]);
			shell->args[i] = tmp;
		}
		else if (shell->args[i][0] == '$')
			shell->args[i] = sub_env_var(shell, i);
		i++;
	}
	return (1);
}
