/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:55:44 by gcot              #+#    #+#             */
/*   Updated: 2023/08/10 13:58:00 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	char	*temp;
	int		tmp_res;
	int		i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	tmp_res = nmemb * size;
	if (tmp_res / size != nmemb)
		return (NULL);
	ptr = malloc(tmp_res);
	if (ptr == NULL)
		return (ptr);
	i = 0;
	temp = ptr;
	while (i < tmp_res)
		temp[i++] = 0;
	return (ptr);
}

void	ft_strstr_delete_2(char *s1, char *res, int i, int j)
{
	int	k;

	k = -1;
	while (++k < i)
		res[k] = s1[k];
	while (s1[i + j])
	{
		res[k] = s1[i + j];
		k++;
		j++;
	}
	res[k] = '\0';
}

char	*ft_strstr_delete(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i + j] == s2[j] && s1[i + j])
			j++;
		if (!s2[j])
			break ;
		i++;
	}
	if (!s1[i])
		return (s1);
	res = malloc(sizeof(*s1) * (ft_strlen(s1) - ft_strlen(s2) + 1));
	ft_strstr_delete_2(s1, res, i, j);
	free(s1);
	return (res);
}

char	*ft_strcpy(char *str)
{
	int		i;
	char	*res;

	res = ft_calloc(sizeof(*res), ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
