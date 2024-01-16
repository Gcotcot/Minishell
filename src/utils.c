/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:55:59 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/05 18:03:28 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_delete(char *s1, char s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if (s1[i] == s2)
			j++;
		i++;
	}
	res = malloc(sizeof(*s1) * (ft_strlen(s1) - j + 1));
	i = 0;
	j = 0;
	while (s1[i])
	{
		if (s1[i] != s2)
			res[j++] = s1[i];
		i++;
	}
	res[j] = '\0';
	free(s1);
	return (res);
}

char	*ft_strcat(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	res = malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	if (s1)
		free(s1);
	return (res);
}

int	ft_strc(char *s1, char s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == s2)
			return (0);
		i++;
	}
	return (1);
}

int	ft_strchr(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i] == s2[j] && s2[j])
		{
			j++;
			i++;
		}
		if (!s2[j])
			return (0);
		i++;
	}
	return (1);
}
