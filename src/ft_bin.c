/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:20:55 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/29 15:49:54 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_export_3(t_env *env, int i)
{
	char	**res;

	res = ft_trie(env->environ);
	while (res[i])
	{
		if (res[i][ft_strlen(res[i]) - 1] == '=')
			res[i][ft_strlen(res[i]) - 1] = '\0';
		if ((res[i][0] != '?' && res[i][0] != '_') || res[i][1] != '=')
			printf("declare -x %s\n", res[i]);
		free(res[i]);
		i++;
	}
	free(res);
}

void	ft_export(t_env *env, char **cmd)
{
	int		i;

	i = 0;
	if (cmd[1])
	{
		while (cmd[i + 1])
		{
			cmd[i + 1] = delete_quote(cmd[i + 1]);
			ft_export_2(env, cmd[i + 1]);
			i++;
		}
	}
	else
		ft_export_3(env, i);
}

int	ft_echo_arg_n(char *cmd)
{
	int	i;

	i = 1;
	if (cmd[0] == '-' && cmd[i] == 'n')
	{
		while (cmd[i] == 'n' || cmd[i] == 'e')
			i++;
		if (!cmd[i])
			return (1);
	}
	return (0);
}

static void	ft_echo_2(char **cmd)
{
	int	i;
	int	bo;

	bo = 1;
	i = 1;
	while (cmd[i])
	{
		cmd[i] = delete_quote(cmd[i]);
		printf("%s", cmd[i]);
		if (cmd[i][0])
			bo = 0;
		if (cmd[++i] && !bo)
			printf(" ");
	}
	printf("\n");
}

void	ft_echo(char **cmd, t_env *env)
{
	int	i;
	int	bo;

	bo = 1;
	if (cmd[1] && ft_echo_arg_n(cmd[1]))
	{
		i = 2;
		while (cmd[i])
		{
			cmd[i] = ft_strchr_delete(cmd[i], '\n');
			cmd[i] = delete_quote(cmd[i]);
			printf("%s", cmd[i]);
			if (cmd[i][1])
				bo = 0;
			if (cmd[++i] && !bo)
				printf(" ");
		}
	}
	else
		ft_echo_2(cmd);
	ft_actualisation(env, 0);
}
