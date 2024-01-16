/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 18:45:51 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/31 10:07:23 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_redirect(char **cmd, int word, int i, char ***cmd_line)
{
	char	**res;

	res = (char **) ft_calloc(sizeof(char *), 3);
	res[2] = NULL;
	res[0] = (char *) ft_calloc (1, 3);
	i = ft_put_redirect(cmd[word], res, i);
	if (cmd[word][i] == '>' || cmd[word][i] == '<')
	{
		printf(ERR_REDIRECT, cmd[word][i]);
		ft_free_redirect(cmd_line);
		free(res[0]);
		free(res[1]);
		free(res);
		exit(1);
	}
	if (!cmd[word][i])
	{
		word++;
		i = 0;
	}
	if (cmd[word][i] && (cmd[word][i] == '\'' || cmd[word][i] == '\"'))
		ft_get_cmd_quotes(cmd[word], res, i);
	else
		ft_get_cmd_split(cmd[word], res, i);
	return (res);
}

void	ft_get_cmd_2(char **cmd, int *word, int *i, int *j)
{
	*i = 0;
	while (cmd[*word][*i])
	{
		while (cmd[*word][*i] && cmd[*word][*i] == ' ')
			*i += 1;
		if (cmd[*word][*i] && cmd[*word][*i] != ' ')
			*j += 1;
		while (cmd[*word][*i] && cmd[*word][*i] != ' ')
			*i += 1;
	}
	if (cmd[*word])
		*word += 1;
}

void	ft_get_cmd_3(char *cmd, int *i, int *tab, char **res)
{
	int	k;
	int	j;

	j = -1;
	k = 0;
	while (cmd[*i] && cmd[*i] == ' ')
		*i += 1;
	if (cmd[*i] && cmd[*i] != ' ')
		j = *i;
	while (cmd[*i] && cmd[*i] != ' ')
		*i += 1;
	if (j >= 0)
	{
		res[*tab] = ft_calloc(1, *i - j + 1);
		while (cmd[j] && cmd[j] != ' ')
			res[*tab][k++] = cmd[j++];
		j = -1;
		k = 0;
		*tab += 1;
	}
}

char	**ft_get_cmd(char **cmd)
{
	int		i;
	int		tab;
	int		word;
	int		j;
	char	**res;

	word = 0;
	j = 0;
	while (cmd[word])
		ft_get_cmd_2(cmd, &word, &i, &j);
	res = (char **) ft_calloc (sizeof(char *), j + 1);
	word = 0;
	j = -1;
	tab = 0;
	while (cmd[word])
	{
		i = 0;
		while (cmd[word][i])
			ft_get_cmd_3(cmd[word], &i, &tab, res);
		word++;
	}
	return (res);
}

void	ft_split_redirect(char ***cmd_line, char **cmd, int j, int word)
{
	int		i;
	char	c;

	while (cmd[word])
	{
		i = 0;
		while (cmd[word][i])
		{
			if (cmd[word][i] == 34 || cmd[word][i] == 39)
			{
				c = cmd[word][i++];
				while (cmd[word][i] != c && cmd[word][i])
					i++;
			}
			if (cmd[word][i] == '>' || cmd[word][i] == '<')
				cmd_line[j++] = ft_get_redirect(cmd, word, i++, cmd_line);
			if (cmd[word][i])
				i++;
		}
		if (cmd[word])
			word++;
	}
	cmd_line[0] = ft_get_cmd(cmd);
}
