/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:21:57 by jsolinis          #+#    #+#             */
/*   Updated: 2022/03/27 00:24:48 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>


void	ft_set_route(t_proc *proc)
{
	int		i;
	char	**routes;

	i = 0;
	while (proc->paths[i])
		i++;
	routes = malloc (i * sizeof(char *)); 
	i = 0;
	while (proc->paths[i])
	{
		routes[i] = ft_strjoin(proc->paths[i], (*proc->lst)->args[0]);
		if (access(routes[i], F_OK) == 0)
			(*proc->lst)->route = routes[i];
		else
			free(routes[i]);
		i++;
	}
}

	void	ft_parental_wait(t_proc *proc)
	{
		int	stt;
	pid_t	process;

	process = waitpid((*proc->lst)->pid, &stt, 0);
	printf("ANTES: %d, DESPUES: %d\n", (*proc->lst)->pid, process);
	//if (WIFEXITED(stt))
	//	(*proc->lst)->status = WEXITSTATUS(stt);
}

void	ft_initialize_pipes(t_proc *proc)
{
	int	i;

	i = 0;
	proc->launched_processes = 0;
	while (i < 2)
		pipe(proc->p[i++]);
}

void	ft_print_fd(t_proc *proc)
{
	printf("LAUNCHED Ps: %d\n", proc->launched_processes);
}

void	ft_launch_process(t_proc *proc)
{
//	ft_initialize_pipes(proc);
	pipe(proc->p[0]);
	ft_lstiter(proc, ft_create_children);
	ft_lstiter(proc, ft_parental_wait);
	ft_lstiter(proc, ft_print_fd);
//	ft_lstiter(proc, ft_fd_red);
}




