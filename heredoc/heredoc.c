/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 15:45:21 by khafni            #+#    #+#             */
/*   Updated: 2021/09/07 17:17:34 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

char *generate_random_value(void)
{
	int			fd;	
	unsigned	randval;
	char		*rand_string;
	char		*r_string;

	fd = open("/dev/random", O_RDONLY);
	read(fd, &randval, sizeof(randval));
	close(fd);
	rand_string = ft_itoa(randval);
	r_string = ft_strjoin("/tmp/heredoc-", rand_string);
	free(rand_string);
	return (r_string);
}

t_arrptr	get_array_of_heredoc_files(t_commands_table cmd)
{
	t_arrptr her_arr;
	t_redir_file rf;
	int i;

	i = 0;
	her_arr = empty_arrptr_create(free);
	while (i < cmd->redir_files->len)
	{
		rf = arrptr_get(cmd->redir_files, i);
		if (rf->file_type == REDI_HEREDOC_FILE)
			arrptr_add(her_arr, ft_strdup(rf->file_name));	
		i++;
	}
	return (her_arr);
}

char	*heredoc_repl_save(char *file)
{
	int 	fd;
	char	*line;
	char	*random_string;
	
	
	random_string = generate_random_value();		
	fd = open(random_string, O_CREAT | O_RDWR, S_IRWXU);
	while (1)
	{	
		line = readline("heredoc> ");
		if (!ft_strncmp(line, file, ft_strlen(file)))
		{
			free(line);
			// free(tmp_str);
			close(fd);
			return (random_string);
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);		
	}	
}

void	heredoc_repl_non_save(char *file)
{	
	char	*line;
	
	while (1)
	{	
		line = readline("heredoc> ");		
		if (!ft_strncmp(line, file, ft_strlen(file)))
		{
			free(line);
			return ;
		}
		free(line);	
	}
}

void	turn_last_heredoc_delName_into_filename(t_commands_table cmd, char *file_name)
{
	int i;
	t_redir_file rf;

	i = 0;
	while (i < cmd->redir_files->len - 1)	
		i++;	
	rf = arrptr_get(cmd->redir_files, i);
	free(rf->file_name);
	rf->file_name = ft_strdup(file_name);
}

char	*heredoc_for_one_cmd_table(t_commands_table cmd)
{
	t_arrptr 	hdoc_file_names;
	int			i;
	char		*str;
	char		*ret_file_name;

	hdoc_file_names = get_array_of_heredoc_files(cmd);	
	i = 0;
	str = arrptr_get(hdoc_file_names, i);
	while (i < hdoc_file_names->len - 1)
	{
		str = arrptr_get(hdoc_file_names, i);
		heredoc_repl_non_save(str);
		i++;
	}
	if (hdoc_file_names->len >= 1)
	{
		str = arrptr_get(hdoc_file_names, i);
		ret_file_name = heredoc_repl_save(str);
		turn_last_heredoc_delName_into_filename(cmd, ret_file_name);
	}
	arrptr_destroy(hdoc_file_names);
	return (ret_file_name);
}
