/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 07:39:23 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/06 12:47:10 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_proc *proc, int cmd_count, int child)
{
	int	i;
	int err;

	err = 0;
	if (cmd_count > 1 && child && ++err)
		err = print_error(": No such file or directory", 127, (*proc->lst)->args[1], 1);
	else if (cmd_count > 1 && !child && ++err)
		err = print_error(": No such file or directory", 127, (*proc->lst)->args[1], 0);
	if (!err)
	{
		i = -1;
		while (proc->set->env[++i])
			printf("%s\n", proc->set->env[i]);
	}
	if (child)
		exit (err);
	return (err);
}
