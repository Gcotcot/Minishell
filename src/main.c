/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:56:12 by gbricot           #+#    #+#             */
/*   Updated: 2023/08/17 11:19:24 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		printf ("\b\b\033[K");
	return ;
}

int	main(void)
{
	t_env	*env;

	env = ft_init_minishell();
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
	while (env->exit == 0)
	{
		env->line = readline("Minishell> ");
		if (!env->line)
		{
			env->exit = 1;
			printf("exit\n");
		}
		else
			ft_execute(env);
		add_history(env->line);
		ft_free_env(env);
	}
	rl_clear_history();
	ft_clean_env(env);
	return (0);
}
