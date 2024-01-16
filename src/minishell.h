/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:57:39 by gcot              #+#    #+#             */
/*   Updated: 2023/08/31 11:05:54 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ERR_REDIRECT "syntax error near unexpected token `%c'\n"

extern char	**environ;

typedef struct s_env
{
	char	*line;
	char	**environ;
	char	***cmd;
	int		error;
	int		exit;
}	t_env;

int		ft_is_redirect(char **cmd);
int		ft_keyword(char **cmd, t_env *env, int pid);
int		ft_keyword_2(char **cmd, t_env *env);
int		ft_split_cpy(char *str, char **split, int i, int nb_tabs);

char	*ft_find_value_path_2(char *env, int i);

char	**ft_trie(char **env);
char	***ft_split(t_env *env);
char	*ft_add_var(char *str, char **env, char *var);

void	ft_execute(t_env *env);
void	ft_multiple_pipe(char ***cmd, t_env *env);
void	ft_execute_bin(char **cmd, t_env *env);
void	ft_free_env(t_env *env);
void	ft_clean_env(t_env *env);
void	ft_export_2(t_env *env, char *cmd);
void	ft_replace_var(char ***cmd, char **environ);

t_env	*ft_init_minishell(void);

/*		BIN		*/

void	ft_env(t_env *env);
void	ft_unset(char **path, t_env *env);
void	ft_export(t_env *env, char **cmd);
void	ft_echo(char **cmd, t_env *env);
void	ft_exit(t_env *env);
void	ft_exec(char **cmd);
void	ft_cd(t_env *env, char *cmd);

/*		REDIRECT	*/

int		ft_is_redirect(char **cmd);
int		ft_is_file_name_sep(char c);
int		ft_right_redirect(char *file_name, int out_fd, int is_dbl);
int		ft_put_redirect(char *cmd, char **res, int i);
int		ft_redirect_left(char *file_name, int in_fd, char ***cmd);
int		ft_get_nb_cmd(char **cmd, int word, int res, t_env *env);
int		ft_get_nb_cmd_2(char *cmd, int res, int *i);

char	**ft_get_redirect(char **cmd, int word, int i, char ***cmd_line);
char	**ft_get_cmd(char **cmd);

void	ft_redirect(char **cmd, t_env *env);
void	ft_redirect_left_dbl(char *key_word, char ***cmd);
void	ft_exec_redirect(char ***cmd, t_env *env);
void	ft_split_redirect(char ***cmd_line, char **cmd, int j, int word);
void	ft_get_cmd_split(char *cmd, char **res, int i);
void	ft_get_cmd_quotes(char *cmd, char **res, int i);
void	ft_get_cmd_2(char **cmd, int *word, int *i, int *j);
void	ft_get_cmd_3(char *cmd, int *i, int *tab, char **res);
void	ft_exec_all_redirects(char ***cmd, int *in_fd, int *out_fd);
void	ft_free_redirect(char ***cmd_line);

/*		UTILS		*/

int		ft_strlen(char *str);
int		ft_strchr(char *s1, char *s2);
int		ft_strc(char *s1, char s2);
int		ft_strcmp(char *s1, char *s2);
int		ft_strchr_var(char *env, char *var);

char	*ft_strcat(char *s1, char *s2);
char	*ft_strchr_delete(char *s1, char s2);
char	*ft_strstr_delete(char *s1, char *s2);
char	*ft_strcpy(char *str);
char	*ft_strdup(char *s);
char	**ft_strcpy_double_del(char **src, int i);
char	**ft_strcpy_double(char **src);
char	*delete_quote(char *str);
char	*ft_find_value_path(char *path, char **env, int i);

void	*ft_calloc(size_t nmemb, size_t size);
void	ft_actualisation(t_env *env, int i);

#endif
