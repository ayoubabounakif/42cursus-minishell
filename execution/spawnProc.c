/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawnProc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:22:51 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/15 11:22:54 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	spawnLastProc(int in, int *pipeFds, t_commands_table command, t_dlist envl)
{
	char	**tmp_envl;

	if (isBuiltin(command->tokens_simpl[0]) == TRUE
		&& !command->redir_files->len)
		return (executeBuiltins(command, envl));
	g_vars.pid = fork();
	if (g_vars.pid == CHILD)
	{
		tmp_envl = env_list_to_env_array(envl);
		if (in != STDIN_FILENO)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (pipeFds[WRITE] > 2)
			close(pipeFds[WRITE]);
		if (command->redir_files->len)
			inputOutputRedirection(command);
		if (isBuiltin(command->tokens_simpl[0]) == TRUE)
			exit(executeBuiltins(command, envl));
		else
		{
			if (checkExecutable(command->tokens_simpl[0]) == 0 && command->tokens_simpl[0] != NULL)
			{
				printErrorMessage(command->tokens_simpl[0], "");
				g_vars.exit_code = 127;
				exit(g_vars.exit_code);
			}
			else if (execve(command->tokens_simpl[0], command->tokens_simpl, tmp_envl) == -1)
			{
				free(tmp_envl);
				g_vars.exit_code = 0;
				if (checkDirectory(command->tokens_simpl[0]) == 1)
				{
					printErrorMessage(command->tokens_simpl[0], "is a directory");
					g_vars.exit_code = 126;
					exit(g_vars.exit_code);
				}
				exit(g_vars.exit_code);
			}
			
		}
	}
	return (EXIT_SUCCESS);
}

int	spawnProc(int in, int *pipeFds, t_commands_table command, t_dlist envl)
{
	char	**tmp_envl;

	g_vars.pid = fork();
	if (g_vars.pid == CHILD)
	{
		tmp_envl = env_list_to_env_array(envl);
		dup2InputOutput(in, pipeFds[WRITE]);
		if (pipeFds[READ] > 2)
			close(pipeFds[READ]);
		if (command->redir_files->len)
			inputOutputRedirection(command);
		if (isBuiltin(command->tokens_simpl[0]) == TRUE)
			exit(executeBuiltins(command, envl));
		else
		{
			if (checkExecutable(command->tokens_simpl[0]) == 0 && command->tokens_simpl[0] != NULL)
			{
				printErrorMessage(command->tokens_simpl[0], "");
				g_vars.exit_code = 127;
				exit(g_vars.exit_code);
			}
			else if (execve(command->tokens_simpl[0], command->tokens_simpl, tmp_envl) == -1)
			{
				free(tmp_envl);
				g_vars.exit_code = 0;
				if (checkDirectory(command->tokens_simpl[0]) == 1)
				{
					printErrorMessage(command->tokens_simpl[0], "is a directory");
					g_vars.exit_code = 126;
				}
				exit(g_vars.exit_code);
			}
		}
	}
	return (EXIT_SUCCESS);
}
