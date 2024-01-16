/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tata <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:52:54 by tata              #+#    #+#             */
/*   Updated: 2023/08/28 15:57:14 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_add_export_var(char **env, char *var, char *value)
{
	int		i;
	char	**res;

	i = 0;
	while (env[i])
		i++;
	res = ft_calloc(sizeof(*res), i + 2);
	i = 0;
	while (env[i])
	{
		res[i] = ft_strcpy(env[i]);
		free(env[i]);
		i++;
	}
	free(env);
	res[i] = ft_calloc(sizeof(**res), 1);
	res[i] = ft_strcat(res[i], var);
	res[i] = ft_strcat(res[i], "=");
	res[i] = ft_strcat(res[i], value);
	return (res);
}

void	ft_export_var(t_env *env, char *var, char *value)
{
	int		i;
	int		l;
	int		j;
	char	*new;

	l = 0;
	while (env->environ[l] && ft_strchr_var(env->environ[l], var))
		l++;
	if (env->environ[l])
	{
		free(env->environ[l]);
		new = ft_calloc(sizeof(*new), ft_strlen(var) + ft_strlen(value) + 2);
		i = -1;
		while (var[++i])
			new[i] = var[i];
		new[i++] = '=';
		j = 0;
		while (value[j])
			new[i++] = value[j++];
		env->environ[l] = new;
	}
	else
		env->environ = ft_add_export_var(env->environ, var, value);
}

char	*ft_find_value(char *cmd)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (cmd[i] != '=' && cmd[i])
		i++;
	if (cmd[i])
		i++;
	j = i;
	while (cmd[j])
		j++;
	res = ft_calloc(sizeof(*res), j - i + 1);
	j = 0;
	while (cmd[i])
	{
		res[j] = cmd[i];
		i++;
		j++;
	}
	return (res);
}

char	*ft_find_var_ex(char *cmd)
{
	int		i;
	char	*res;

	i = 0;
	while (cmd[i] != '=' && cmd[i])
		i++;
	res = ft_calloc(sizeof(*res), i + 1);
	i = 0;
	while (cmd[i] != '=' && cmd[i])
	{
		res[i] = cmd[i];
		i++;
	}
	return (res);
}

void	ft_export_2(t_env *env, char *cmd)
{
	char	*var;
	char	*value;

	var = ft_find_var_ex(cmd);
	value = ft_find_value(cmd);
	ft_export_var(env, var, value);
	free(var);
	free(value);
}
