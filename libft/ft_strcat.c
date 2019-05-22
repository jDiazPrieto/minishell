/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 19:29:18 by jdiaz             #+#    #+#             */
/*   Updated: 2018/10/02 19:46:19 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *restrict s1, const char *restrict s2)
{
	char	*cpy;

	cpy = (char *)s1;
	while (*cpy != '\0')
		cpy++;
	while (*s2 != '\0')
	{
		*cpy = *s2;
		cpy++;
		s2++;
	}
	*cpy = '\0';
	return (s1);
}