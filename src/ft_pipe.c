/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:57:39 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/29 17:43:42 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_receive_send(int **fd, t_env *env, int j)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd[j][0], STDIN_FILENO);
		close(fd[j][0]);
		close(fd[j][1]);
		dup2(fd[j + 1][1], STDOUT_FILENO);
		close(fd[j + 1][0]);
		close(fd[j + 1][1]);
		if (ft_keyword(env->cmd[j + 1], env, 0))
			ft_execute_bin(env->cmd[j + 1], env);
		exit(env->error);
	}
	close(fd[j][0]);
	close(fd[j][1]);
	waitpid(pid, &env->error, 0);
	env->error >>= 8;
}

static void	ft_multiple_pipe_3(t_env *env, int *pid, int **fd, int i)
{
	int		j;

	j = i - 1;
	pid[1] = fork();
	if (pid[1] == 0)
	{
		dup2(fd[j][0], STDIN_FILENO);
		close(fd[j][0]);
		close(fd[j][1]);
		if (ft_keyword(env->cmd[j + 1], env, 0))
			ft_execute_bin(env->cmd[j + 1], env);
		exit(env->error);
	}
	j = 0;
	while (j < i)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		free(fd[j]);
		j++;
	}
	free (fd);
	waitpid(pid[1], &env->error, 0);
	env->error >>= 8;
}

static void	ft_multiple_pipe_2(t_env *env, int *pid, int **fd, int i)
{
	int		j;

	pid[0] = fork();
	if (pid[0] == 0)
	{
		dup2(fd[0][1], STDOUT_FILENO);
		close(fd[0][1]);
		close(fd[0][0]);
		if (ft_keyword(env->cmd[0], env, 0))
			ft_execute_bin(env->cmd[0], env);
		exit(env->error);
	}
	else
	{
		waitpid(pid[0], &env->error, 0);
		env->error >>= 8;
	}
	j = 0;
	while (j < i - 1)
	{
		ft_receive_send(fd, env, j);
		j++;
	}
	ft_multiple_pipe_3(env, pid, fd, i);
}

void	ft_multiple_pipe(char ***cmd, t_env *env)
{
	int		i;
	int		j;
	int		pid[2];
	int		**fd;

	i = 0;
	j = 0;
	while (cmd[i])
		i++;
	i--;
	if (!i)
	{
		if (ft_keyword(cmd[0], env, 0))
			ft_execute_bin(cmd[0], env);
		return ;
	}
	fd = (int **) malloc (sizeof(int *) * i);
	while (j < i)
	{
		fd[j] = (int *) malloc(sizeof(int) * 2);
		pipe(fd[j]);
		j++;
	}
	ft_multiple_pipe_2(env, pid, fd, i);
}
