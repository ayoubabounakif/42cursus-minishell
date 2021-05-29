/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   420sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafni <khafni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:40:22 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/29 17:48:29 by khafni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/minishell.h"
# include "dlist/dlists.h"

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	char		*line;
	int			n = 1;
	t_dlist 	parsed_line;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		ft_putstr_fd("\x1B[36m_420sh\x1B[0m\x1B[34m :: \x1B[0m", STDOUT);
		ft_putstr_fd("\x1B[32m", STDOUT);
		ft_putstr_fd("\x1B[0m\x1B[31m$ \x1B[0m", STDOUT);
		n = get_next_line(STDIN, &line);
		parsed_line = cmd_tables_list(line);
		if (n == 0)
		{
			printf("exit\n");
			break ;
		}
		execute_parsed_line(parsed_line, envp);
	}

	//char *s = "ls -l $BIGVAR $donc dddd";
	//printf("%s\n", str_find_and_replace(s, "$donc", "potato"));
	//printf("%s\n", rstr_find_and_replace(cstr_to_rstr(s), "$donc", "potato"));
	//printf("%s\n", find_env_vars_in_a_token(s, get_mask(s)));

	return (EXIT_SUCCESS);
}
