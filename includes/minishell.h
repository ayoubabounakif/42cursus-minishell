/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:15:55 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/30 16:38:47 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <math.h>
# include <errno.h>
# include <time.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../dlist/dlists.h"
# include "../parser/command_table_generator.h"

# define TRUE 1
# define FALSE 0

# define YES_VALUE 1
# define NO_VALUE 0

# define CHILD_PROCESS 0

/*
** _420sh STRUCTS
*/

typedef struct	s_vars
{
	pid_t		pid;
	int			exit_code;
}				t_vars;

typedef struct s_env
{
	char		*key;
	char		*value;
	char		sep;
	int			has_value;
}				t_env;

t_vars			g_vars;

/*
** Signals
**/
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		sig_handler(int sign_num);

/*
** Builtins
**/
int			__cd__(t_command *command, t_dlist env_list);
int			__pwd__(t_command *command, t_dlist env_list);
int			__echo__( t_command *command, t_dlist env_list);
int			__export__(t_command *command, t_dlist env_list);
int			__unset__(t_command *command, t_dlist env_list);
int			__env__(t_command *command, t_dlist env_list);
int			__exit__(t_command *command, t_dlist env_list);

/*
** Env
**/
t_env		*env_create(char *key, char *value);
void		env_destroy(void *env_);
int			env_unset(t_dlist env_list, char *key);
t_dlist		get_envs(char **env);
char		*get_value(char *line);
char		*bin_path(char *cmd, t_dlist envl);
char		**env_list_to_env_array(t_dlist env_list);
void	env_array_destroy(char **env_array);
char	*find_envv_akey_value(char *key, t_dlist env_list);
/*
** Execution
*/
void		execute_parsed_line(t_dlist parsed_line, t_dlist envl);
void		fork_pipes(t_dlist pipeline, t_dlist envl);
int			spawn_proc(int in, int out, t_command *command, t_dlist envl);

/*
** Utils
*/
void		redir_in_out(int in, int out);
#endif