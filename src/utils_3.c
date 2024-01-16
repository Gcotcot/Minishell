/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:09:37 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/28 14:21:29 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s)
{
	char	*ptr;
	int		i;

	if (!s)
		return (ptr = (char *) ft_calloc(1, 1));
	ptr = (char *) ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}

char	*delete_quote_2(char *str, int start, int end)
{
	int		i;
	int		j;
	char	*res;

	res = malloc(sizeof(*res) * ft_strlen(str) - 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i != start && i != end)
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	free(str);
	return (res);
}

char	*delete_quote(char *str)
{
	char	c;
	int		i;
	int		start;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			start = i;
			c = str[i++];
			while (str[i] != c && str[i])
				i++;
			if (str[i])
			{
				str = delete_quote_2(str, start, i);
				i -= 2;
			}
		}
		if (str[i])
			i++;
	}
	return (str);
}

int	ft_strchr_var(char *env, char *var)
{
	int	i;

	i = 0;
	while (env[i] != '=')
	{
		if (env[i] != var[i])
			return (1);
		i++;
	}
	if (var[i])
		return (1);
	return (0);
}

char	**ft_strcpy_double(char **src)
{
	char	**res;
	int		j;
	int		k;

	j = 0;
	while (src[j])
		j++;
	res = ft_calloc(sizeof(*res), j + 1);
	j = 0;
	k = 0;
	while (src[j])
	{
		res[k++] = ft_strcpy(src[j]);
		j++;
	}
	return (res);
}
