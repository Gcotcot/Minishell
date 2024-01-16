/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyword.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:58:50 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/30 13:59:05 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_cd(char **cmd, t_env *env)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
		return ;
	if (i > 2)
	{
		ft_actualisation(env, 1);
		printf("cd: too many arguments\n");
		return ;
	}
	ft_cd(env, cmd[1]);
}

int	ft_keyword_2(char **cmd, t_env *env)
{
	if (!ft_strcmp(cmd[0], "cd"))
		ft_check_cd(cmd, env);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd, env);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env(env);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(cmd, env);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(env, cmd);
	else if (!ft_strcmp(cmd[0], "$?"))
		printf("%i: command not found\n", env->error);
	else if (cmd[0][0] == '.' && cmd[0][1] == '/')
		ft_exec(cmd);
	else
		return (1);
	return (0);
}

int	ft_keyword(char **cmd, t_env *env, int pid)
{
	char	*buf;

	if (!*cmd)
		return (1);
	else if (ft_is_redirect(cmd))
	{
		pid = fork();
		if (pid == 0)
			ft_redirect(cmd, env);
		waitpid(pid, &env->error, 0);
		env->error >>= 8;
	}
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(env);
	else if (!ft_strcmp(cmd[0], "pwd"))
	{
		buf = malloc (2048);
		getcwd(buf, 2048);
		printf("%s\n", buf);
		ft_actualisation(env, 0);
		free(buf);
	}
	else
		return (ft_keyword_2(cmd, env));
	return (0);
}
