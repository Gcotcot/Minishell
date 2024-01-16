/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:10:55 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/29 16:11:18 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_strcpy_double_del(char **src, int i)
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
		if (j != i)
			res[k++] = ft_strcpy(src[j]);
		j++;
	}
	k = 0;
	while (src[k])
		free(src[k++]);
	free(src);
	return (res);
}

char	*ft_find_value_path(char *path, char **env, int i)
{
	int		l;
	char	*res;

	while (env[i] && ft_strchr_var(env[i], path))
		i++;
	if (env[i])
	{
		l = 5;
		while (env[i][l])
		{
			res = ft_find_value_path_2(env[i], l);
			if (!ft_strcmp(res, "/bin") || !ft_strcmp(res, "/usr/bin"))
			{
				res = ft_strcat(res, "/");
				return (res);
			}
			free (res);
			while (env[i][l] && env[i][l] != ':')
				l++;
			if (env[i][l])
				l++;
		}
	}
	res = ft_calloc(sizeof(*res), 1);
	return (res);
}

static void	ft_actualisation_2(int x, int j, t_env *env)
{
	char	*cmd;

	cmd = ft_calloc(sizeof(*cmd), x + 3);
	cmd[0] = '?';
	cmd[1] = '=';
	while (x + 1 > 1)
	{
		cmd[x + 1] = (j % 10) + 48;
		x--;
		j = j / 10;
	}
	cmd = delete_quote(cmd);
	ft_export_2(env, cmd);
	free(cmd);
}

void	ft_actualisation(t_env *env, int i)
{
	int		j;
	int		x;

	j = i;
	env->error = i;
	x = 0;
	while (i >= 0)
	{
		x++;
		i = i / 10;
		if (i == 0)
			break ;
	}
	ft_actualisation_2(x, j, env);
}
