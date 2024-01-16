/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trie.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:36:59 by gcot              #+#    #+#             */
/*   Updated: 2023/08/10 12:59:10 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_trie_2(char **res, int i)
{
	int		j;
	char	*temp;

	temp = ft_strcpy(res[i]);
	j = i + 1;
	while (res[j])
	{
		if (ft_strcmp(temp, res[j]) > 0)
		{
			free(res[i]);
			res[i] = ft_strcpy(res[j]);
			free(res[j]);
			res[j] = ft_strcpy(temp);
			free(temp);
			temp = ft_strcpy(res[i]);
		}
		j++;
	}
	free(res[i]);
	res[i] = ft_strcpy(temp);
	free(temp);
}

char	**ft_trie(char **env)
{
	int		i;
	char	**res;

	i = 0;
	while (env[i])
		i++;
	res = ft_calloc(sizeof(*res), i + 1);
	i = 0;
	while (env[i])
	{
		res[i] = ft_strcpy(env[i]);
		i++;
	}
	i = 0;
	while (res[i + 1])
	{
		ft_trie_2(res, i);
		i++;
	}
	return (res);
}
