/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:22:10 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/20 13:23:20 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_redirect(char ***cmd_line)
{
	int	i;
	int	word;

	i = 0;
	if (cmd_line[0])
	{
		while (cmd_line[0][i])
			free(cmd_line[0][i++]);
		free(cmd_line[0]);
	}
	word = 1;
	while (cmd_line[word])
	{
		if (cmd_line[word][0])
			free(cmd_line[word][0]);
		if (cmd_line[word][1])
			free(cmd_line[word][1]);
		free(cmd_line[word]);
		word++;
	}
	free(cmd_line);
}

void	ft_redirect(char **cmd, t_env *env)
{
	int		word;
	char	***cmd_line;

	word = ft_get_nb_cmd(cmd, 0, 0, env);
	if (!word)
		exit(env->error);
	cmd_line = (char ***) ft_calloc(sizeof(char **), word + 2);
	ft_split_redirect(cmd_line, cmd, 1, 0);
	ft_exec_redirect(cmd_line, env);
	env->error >>= 8;
	ft_free_redirect(cmd_line);
	exit (env->error);
}

int	ft_redirect_left(char *file_name, int in_fd, char ***cmd)
{
	int	file_fd;

	file_fd = open(file_name, O_RDONLY);
	if (file_fd == -1)
	{
		printf("%s: No such file or directory\n", file_name);
		ft_free_redirect(cmd);
		exit(1);
	}
	if (in_fd > 0)
		close(in_fd);
	return (file_fd);
}

void	ft_redirect_left_dbl(char *key_word, char ***cmd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_free_redirect(cmd);
			exit(0);
		}
		if (!ft_strcmp(line, key_word))
		{
			free(line);
			return ;
		}
		free(line);
	}
}

int	ft_right_redirect(char *file_name, int out_fd, int is_dbl)
{
	int	file_fd;

	if (is_dbl)
	{
		file_fd = open(file_name, O_RDWR | O_APPEND, 0664);
		if (file_fd == -1)
			file_fd = open(file_name, O_CREAT | O_RDWR, 0664);
	}
	else
		file_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (out_fd > 0)
		close(out_fd);
	return (file_fd);
}
