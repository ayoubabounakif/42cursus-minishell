/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   420sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:40:22 by aabounak          #+#    #+#             */
/*   Updated: 2021/06/06 12:55:55y khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/minishell.h"
# include <setjmp.h>
# include "parser/syntax_checking.h"


int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	char		*line = NULL;
	int			n = 1;
	t_dlist 	parsed_line; 
	t_dlist		env_list;
	t_syx_check	sx;		

	sx = syntax_check_create();
	env_list = get_envs(envp);
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	while (420)
	{
		line = readline("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m\x1B[32m\x1B[0m\x1B[31m$ \x1B[0m");		
		if (line && *line)
		{
			parsed_line = parse_line(line, env_list);
			add_history(line);
			free(line);
			executeParsedLine(parsed_line, env_list);
			dlist_destroy(parsed_line);
		}
		else if (!line)
			exit(1);
	}
	return (EXIT_SUCCESS);
}
