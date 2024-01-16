/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:38:42 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/17 11:18:44 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_init_minishell(void)
{
	t_env	*env;

	env = ft_calloc (sizeof(t_env), 1);
	if (!env)
		exit(1);
	env->environ = ft_strcpy_double(environ);
	ft_actualisation(env, 0);
	return (env);
}

void	ft_free_env(t_env *env)
{
	int	i;
	int	j;

	if (env->line)
		free(env->line);
	env->line = NULL;
	i = 0;
	if (env->cmd)
	{
		while (env->cmd[i])
		{
			j = 0;
			while (env->cmd[i][j])
				free(env->cmd[i][j++]);
			free(env->cmd[i++]);
		}
		free(env->cmd);
		env->cmd = NULL;
	}
}

void	ft_clean_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->environ[i])
	{
		free(env->environ[i]);
		i++;
	}
	free(env->environ);
	free(env);
}
