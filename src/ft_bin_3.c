/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:35:56 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/30 13:36:06 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(char **cmd)
{
	int		pid;
	int		i;
	char	*path;
	char	**nullos;

	nullos = NULL;
	i = 0;
	while (cmd[i])
	{
		cmd[i] = delete_quote(cmd[i]);
		i++;
	}
	path = cmd[0];
	cmd[0] = malloc (1);
	cmd[0][0] = '\0';
	pid = fork();
	if (pid == 0)
	{
		if (execve(path + 2, cmd, nullos) == -1)
			printf("%s: No such file or directory\n", path);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	free(path);
}
