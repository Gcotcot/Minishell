/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:18:26 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/30 14:18:35 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_split_cpy_2(char *str, int i)
{
	int		j;
	char	c;

	j = i;
	while (str[j] != ' ' && str[j])
	{
		if (str[j] == 34 || str[j] == 39)
		{
			c = str[j++];
			while (str[j] != c && str[j])
				j++;
		}
		if (str[j] == 124)
			break ;
		if (str[j])
			j++;
	}
	return (j);
}

int	ft_split_cpy(char *str, char **split, int i, int nb_tabs)
{
	int		j;
	int		tab;
	int		x;

	tab = 0;
	while (tab < nb_tabs)
	{
		while (str[i] == ' ' && str[i])
			i++;
		j = ft_split_cpy_2(str, i);
		split[tab] = (char *) malloc(j - i + 1);
		x = 0;
		while (i < j)
			split[tab][x++] = str[i++];
		split[tab][x] = '\0';
		i++;
		tab++;
	}
	split[tab] = NULL;
	i--;
	while (str[i] && str[i] != 124)
		i++;
	return (i);
}
