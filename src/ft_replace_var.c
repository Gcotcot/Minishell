/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:06:52 by gcot              #+#    #+#             */
/*   Updated: 2023/08/29 16:38:55 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_write_var(char *str, int i)
{
	int		j;
	char	*res;

	if (str[i] == '?')
	{
		res = ft_calloc(sizeof(*res), 2);
		res[0] = '?';
		return (res);
	}
	j = 0;
	while (str[i + j] && str[i + j] != ' ' && str[i + j] != 34
		&& str[i + j] != 39 && str[i + j] != '$')
		j++;
	res = ft_calloc(sizeof(*res), j + 1);
	j = 0;
	while (str[i] && str[i] != ' ' && str[i] != 34 && str[i] != 39
		&& str[i] != '$')
	{
		res[j] = str[i];
		j++;
		i++;
	}
	return (res);
}

char	*ft_find_var_2(char *str, char **environ, int *i)
{
	char	*var;

	if (str[*i] == 34)
	{
		*i += 1;
		while (str[*i] != 34 && str[*i])
		{
			if (str[*i] == '$')
			{
				*i += 1;
				var = ft_write_var(str, *i);
				str = ft_add_var(str, environ, var);
				*i -= 1;
			}
			*i += 1;
		}
	}
	if (str[*i] == '$')
	{
		*i += 1;
		var = ft_write_var(str, *i);
		str = ft_add_var(str, environ, var);
		*i -= 1;
	}
	return (str);
}

char	*ft_find_var(char *str, char **environ)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			if (str[i + 1])
				i++;
			while (str[i] && str[i] != 39)
				i++;
		}
		str = ft_find_var_2(str, environ, &i);
		if (str[i])
			i++;
	}
	return (str);
}

void	ft_replace_var(char ***cmd, char **environ)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		if (!ft_strcmp(cmd[i][0], "$?"))
			j++;
		while (cmd[i][j])
		{
			cmd[i][j] = ft_find_var(cmd[i][j], environ);
			j++;
		}
		i++;
	}
}
