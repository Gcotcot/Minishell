/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:09:26 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/30 14:10:02 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_var_3(char *str, char *var, char *new)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '$')
	{
		new[i] = str[i];
		i++;
	}
	j = i;
	i += ft_strlen(var) + 1;
	while (str[i])
		new[j++] = str[i++];
	free(str);
	return (new);
}

char	*ft_add_var_2(char *str, char *env, char *var, char *new)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (str[i] != '$')
	{
		new[i] = str[i];
		i++;
	}
	j = i;
	k = ft_strlen(var) + 1;
	while (env[k])
	{
		new[j] = env[k];
		j++;
		k++;
	}
	i += ft_strlen(var) + 1;
	while (str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	free(str);
	return (new);
}

char	*ft_add_var(char *str, char **env, char *var)
{
	int		i;
	char	*new;

	i = 0;
	while (env[i] && ft_strchr_var(env[i], var))
		i++;
	if (env[i])
	{
		new = malloc(sizeof(*new) * (ft_strlen(env[i]) \
			- ft_strlen(var) + ft_strlen(str)) - 1);
		str = ft_add_var_2(str, env[i], var, new);
	}
	else
	{
		new = ft_calloc(sizeof(*new), ft_strlen(str) - ft_strlen(var));
		str = ft_add_var_3(str, var, new);
	}
	free(var);
	return (str);
}
