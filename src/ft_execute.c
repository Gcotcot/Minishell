/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:47:37 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/29 15:45:54 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_value_path_2(char *env, int i)
{
	int		l;
	int		j;
	char	*res;

	l = i;
	j = 0;
	while (env[l] && env[l] != ':')
	{
		j++;
		l++;
	}
	res = ft_calloc(sizeof(*res), j + 1);
	j = 0;
	while (i < l)
	{
		res[j] = env[i];
		j++;
		i++;
	}
	return (res);
}

void	ft_execute_bin(char **cmd, t_env *env)
{
	int		pid;
	char	*path;
	char	*file_name;
	char	**nullos;

	nullos = NULL;
	path = ft_find_value_path("PATH", env->environ, 0);
	path = ft_strcat(path, cmd[0]);
	file_name = cmd[0];
	cmd[0] = malloc (1);
	cmd[0][0] = '\0';
	pid = fork();
	if (pid == 0)
	{
		env->error = execve(path, cmd, nullos);
		if (env->error == -1)
			printf("%s: command not found\n", file_name);
		exit(127);
	}
	waitpid(pid, &env->error, 0);
	env->error >>= 8;
	ft_actualisation(env, env->error);
	free(file_name);
	free(path);
}

void	ft_execute(t_env *env)
{
	char	*temp;

	temp = ft_strcpy(env->line);
	free(env->line);
	env->line = temp;
	env->cmd = ft_split(env);
	if (!env->cmd)
		return ;
	ft_replace_var(env->cmd, env->environ);
	ft_multiple_pipe(env->cmd, env);
}
