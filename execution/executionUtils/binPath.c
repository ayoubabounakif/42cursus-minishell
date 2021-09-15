/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binPath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:29:49 by aabounak          #+#    #+#             */
/*   Updated: 2021/09/15 11:48:41 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	freeVars(char **splittedPath)
{
	int		i;

	i = 0;
	while (splittedPath[i])
	{
		free(splittedPath[i]);
		i++;
	}
	free(splittedPath);
}

static char	*getBinPath(char *command, char **splittedPath)
{
	int		i;
	int		binFd;
	char	*binPath;
	char	*tmp_bin;

	i = 0;
	binPath = ft_strdup("");
	while (splittedPath[i])
	{
		free(binPath);
		binPath = ft_strjoin(splittedPath[i], "/");
		tmp_bin = binPath;
		binPath = ft_strjoin(tmp_bin, command);
		free(tmp_bin);
		binFd = open(binPath, O_RDONLY);
		if (binFd > 0)
		{
			close(binFd);
			free(command);
			return (binPath);
		}
		i++;
	}
	free(binPath);
	return (command);
}

char	*binPath(char *cmd, t_dlist envl, t_commands_table cmd_t)
{
	char	*binPath;
	char	**splittedPath;

	(void)cmd_t;
	binPath = NULL;
	splittedPath = ft_split(ft_getenv("PATH", envl), ':');
	if (splittedPath == NULL)
		return (NULL);
	binPath = getBinPath(cmd, splittedPath);
	freeVars(splittedPath);
	return (binPath);
}
