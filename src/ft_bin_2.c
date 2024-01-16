/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:30:36 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/30 13:30:52 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_2(t_env *env, char **export, char *pwd)
{
	ft_export(env, export);
	free(export[1]);
	free(pwd);
	pwd = malloc(2048);
	getcwd(pwd, 2048);
	export[1] = ft_strcpy("PWD=");
	export[1] = ft_strcat(export[1], pwd);
	ft_export(env, export);
	free(export[1]);
	free(export);
	free(pwd);
}

void	ft_cd(t_env *env, char *cmd)
{
	char	**export;
	char	*pwd;

	ft_actualisation(env, 1);
	if (!cmd)
		return ;
	export = ft_calloc(sizeof(*export), 3);
	pwd = malloc(2048);
	getcwd(pwd, 2048);
	export[1] = ft_strcpy("OLDPWD=");
	export[1] = ft_strcat(export[1], pwd);
	cmd = delete_quote(cmd);
	if (!chdir(cmd))
		ft_actualisation(env, 0);
	else
	{
		printf("cd: %s: No such file or directory\n", cmd);
		ft_actualisation(env, 1);
	}
	ft_cd_2(env, export, pwd);
}

void	ft_env(t_env *env)
{
	int		i;
	char	**res;

	i = 0;
	while (env->environ[i])
	{
		res = ft_strcpy_double(env->environ);
		while (res[i])
		{
			if ((res[i][0] != '?' || res[i][1] != '=')
				&& res[i][ft_strlen(res[i]) - 1] != '=')
				printf("%s\n", res[i]);
			free(res[i]);
			i++;
		}
		free(res);
	}
}

void	ft_unset(char **path, t_env *env)
{
	int	i;
	int	j;

	j = 1;
	while (path[j])
	{
		path[j] = delete_quote(path[j]);
		i = 0;
		while (env->environ[i] && ft_strchr_var(env->environ[i], path[j]))
			i++;
		if (env->environ[i])
			env->environ = ft_strcpy_double_del(env->environ, i);
		j++;
	}
}

void	ft_exit(t_env *env)
{
	if (env)
		env->exit = 1;
	else
		exit(0);
}
