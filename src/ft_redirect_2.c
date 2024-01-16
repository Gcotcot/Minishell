/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 09:38:18 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/20 13:21:16 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redirect(char **cmd)
{
	int		i;
	int		word;
	char	c;

	word = 0;
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
				return (1);
			if (cmd[word][i])
				i++;
		}
		if (cmd[word])
			word++;
	}
	return (0);
}

int	ft_put_redirect(char *cmd, char **res, int i)
{
	char	c;

	if (cmd[i] == '<')
		c = '<';
	else
		c = '>';
	cmd[i] = ' ';
	res[0][0] = c;
	i++;
	if (cmd[i] == c)
	{
		cmd[i] = ' ';
		res[0][1] = c;
		i++;
	}
	return (i);
}

void	ft_get_cmd_quotes(char *cmd, char **res, int i)
{
	int		j;
	char	c;

	j = i;
	c = cmd[i];
	while (cmd[i] && cmd[i] != c)
		i++;
	res[1] = (char *) malloc (i - j + 1);
	i = j;
	j = 0;
	while (cmd[i] && j > 0 && cmd[i] != c)
	{
		res[1][j++] = cmd[i++];
		cmd[i - 1] = ' ';
	}
	res[1][j] = '\0';
}

void	ft_get_cmd_split(char *cmd, char **res, int i)
{
	int		j;

	j = i;
	while (cmd[i] && cmd[i] != ' '
		&& cmd[i] != '<'
		&& cmd[i] != '>')
		i++;
	res[1] = (char *) malloc(i - j + 1);
	i = j;
	j = 0;
	while (cmd[i] && cmd[i] != ' '
		&& cmd[i] != '<' && cmd[i] != '>')
	{
		res[1][j++] = cmd[i++];
		cmd[i - 1] = ' ';
	}
	res[1][j] = '\0';
}

int	ft_is_file_name_sep(char c)
{
	if (c == ' ' || c == ';' || c == '\\' || c == '$'
		|| c == '\'' || c == '\"')
		return (1);
	return (0);
}
