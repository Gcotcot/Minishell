/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:25:02 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/29 16:58:56 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_nb_cmd_2(char *cmd, int res, int *i)
{
	char	c;

	*i = 0;
	while (cmd[*i])
	{
		if (cmd[*i] == 34 || cmd[*i] == 39)
		{
			c = cmd[*i];
			*i += 1;
			while (cmd[*i] && cmd[*i] != c)
				*i += 1;
		}
		if (cmd[*i] && (cmd[*i] == '>' || cmd[*i] == '<'))
		{
			res++;
			while (cmd[*i] == '>' || cmd[*i] == '<')
				*i += 1;
		}
		if (cmd[*i])
			*i += 1;
	}
	return (res);
}

int	ft_get_nb_cmd(char **cmd, int word, int res, t_env *env)
{
	int	i;

	while (cmd[word])
	{
		i = 0;
		res = ft_get_nb_cmd_2(cmd[word], res, &i);
		if (cmd[word])
			word++;
	}
	if (cmd[word - 1][i - 1] == '<' || cmd[word - 1][i - 1] == '>' 
			|| cmd[word - 1][i - 1] == ';'
			|| cmd[word - 1][i - 1] == '\\' || cmd[word - 1][i - 1] == '/')
	{
		printf("syntax error near unexpected token `%c'\n", \
				cmd[word - 1][i - 1]);
		env->error = 2;
		return (0);
	}
	return (res);
}

void	ft_exec_all_redirects(char ***cmd, int *in_fd, int *out_fd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i][0], "<<"))
			ft_redirect_left_dbl(cmd[i][1], cmd);
		i++;
	}
	i = 1;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i][0], "<"))
			*in_fd = ft_redirect_left(cmd[i][1], *in_fd, cmd);
		i++;
	}
	i = 1;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i][0], ">"))
			*out_fd = ft_right_redirect(cmd[i][1], *out_fd, 0);
		else if (!ft_strcmp(cmd[i][0], ">>"))
			*out_fd = ft_right_redirect(cmd[i][1], *out_fd, 1);
		i++;
	}
}

void	ft_exec_redirect(char ***cmd, t_env *env)
{
	int	pid;
	int	in_fd;
	int	out_fd;

	in_fd = 0;
	out_fd = 0;
	ft_exec_all_redirects(cmd, &in_fd, &out_fd);
	pid = fork();
	if (pid == 0)
	{
		if (in_fd > 0)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (out_fd > 0)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		if (ft_keyword(cmd[0], env, 0))
			ft_execute_bin(cmd[0], env);
		exit(env->error);
	}
	waitpid(pid, &env->error, 0);
}
