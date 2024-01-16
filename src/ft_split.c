/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:14:02 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/17 11:22:02 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nb_words_2(char *str, int i, int nb, char c)
{
	while (str[i] && str[i] != 124)
	{
		while (str[i] == ' ' && str[i])
			i++;
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == 124)
				break ;
			if (str[i] && (str[i] == 34 || str[i] == 39))
			{
				c = str[i++];
				while (str[i] && str[i] != c)
					i++;
			}
			if (str[i])
				i++;
		}
		if (str[i] == 124)
			break ;
		nb++;
		while (str[i] == ' ' && str[i])
			i++;
	}
	return (nb);
}

int	ft_nb_words(char *str, int nb_cmd)
{
	int		i;
	char	c;

	if (!str)
		return (0);
	i = 0;
	while (nb_cmd > 0)
	{
		if (str[i] == 34 || str[i] == 39)
		{
			c = str[i++];
			while (str[i] != c && str[i])
				i++;
		}
		if (str[i] == 124 && str[i - 1] != 124 && str[i + 1] != 124)
			nb_cmd--;
		i++;
	}
	return (ft_nb_words_2(str, i, 0, '"'));
}

int	nb_cmd(char *str)
{
	int		i;
	int		nb;
	char	c;

	i = 0;
	nb = 1;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			c = str[i++];
			while (str[i] != c && str[i])
				i++;
		}
		if (str[i] == 124 && str[i - 1] != 124
			&& str[i + 1] != 124)
			nb++;
		if (str[i])
			i++;
	}
	return (nb);
}

char	***ft_split(t_env *env)
{
	char	***split;
	int		i;
	int		pos;
	int		nb_words;

	split = ft_calloc(sizeof(*split), nb_cmd(env->line) + 1);
	i = 0;
	pos = 0;
	while (i < nb_cmd(env->line))
	{
		nb_words = ft_nb_words(env->line, i);
		if (!nb_words)
		{
			free(split);
			return (NULL);
		}
		split[i] = ft_calloc(sizeof(**split), nb_words + 1);
		pos = ft_split_cpy(env->line, split[i], pos, nb_words) + 1;
		i++;
	}
	split[i] = NULL;
	return (split);
}
