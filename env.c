/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 07:39:23 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 20:17:31 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write(int fd, char *arg)
{
	size_t	cnt;

	cnt = ft_strlen(arg);
	write(fd, arg, cnt);
	write(fd, "\n", 1);
}

int	ft_env(t_proc *proc, int cmd_count, int child, int fd)
{
	int		i;
	int		err;

	err = 0;
	fd = 1;
	if (cmd_count > 1 && child && ++err)
		err = print_error(": No such file or directory",
				127, (*proc->lst)->args[1], 1);
	else if (cmd_count > 1 && !child && ++err)
		err = print_error(": No such file or directory",
				127, (*proc->lst)->args[1], 0);
	if (!err)
	{
		i = -1;
		while (proc->set->env[++i])
			ft_write(fd, proc->set->env[i]);
	}
	if (child)
		exit (err);
	return (err);
}
