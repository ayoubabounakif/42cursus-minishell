/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exit__.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:38:02 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/06 12:38:03 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int __exit__(t_command *command, t_dlist env_list)
{
	(void)command;
	(void)env_list;
	return (EXIT_SUCCESS);
}
