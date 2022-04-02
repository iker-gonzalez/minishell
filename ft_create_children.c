/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_children.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:06:50 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/03 00:21:42 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_child(int *lpipe, int *rpipe, t_node *node, t_proc *proc)
{
	node->pid = fork();
	if (node->pid < 0)
		perror("fork failed");
	if (node->pid == 0)
	{
		if (lpipe)
			ft_set_read(lpipe);
		if (rpipe)
			ft_set_write(rpipe);
		if (node->outfd)
			ft_set_red_write(node->outfd);
		if (node->is_built_in)
		{
			ft_check_builtins(proc, node, 1);
			if (node->route == NULL)
				print_error(": command not found", 127, node->args[0], proc->set);
		}
		else
			execve(node->route, node->args, proc->set->env);
		exit(0);
	}
}

void	ft_create_children(t_proc *proc)
{
	ft_set_route(proc);
	ft_check_red_type(proc);
	if ((*proc->lst)->previous == NULL && (*proc->lst)->next == NULL)
	{
		if ((*proc->lst)->is_built_in)
			ft_check_builtins(proc, (*proc->lst), 0);
		else
			ft_create_child(NULL, NULL, (*proc->lst), proc);
	}
	else if ((*proc->lst)->previous == NULL && (*proc->lst)->next != NULL)
	{
		pipe(proc->rpipe);
		ft_create_child(NULL, proc->rpipe, (*proc->lst), proc);
		ft_swap_pipes(proc);
	}
	else if ((*proc->lst)->previous != NULL && (*proc->lst)->next == NULL)
	{
		ft_create_child(proc->lpipe, NULL, (*proc->lst), proc);
		ft_close_pipe(proc->lpipe);
	}
	else
	{
		pipe(proc->rpipe);
		ft_create_child(proc->lpipe, proc->rpipe, (*proc->lst), proc);
		ft_close_pipe(proc->lpipe);
		ft_swap_pipes(proc);
	}
}

void	ft_check_builtins(t_proc *proc, t_node *node, int child)
{
	if ((ft_strncmp_len((*proc->lst)->args[0], "env", 3)) == 0)
		ft_env(proc, ft_count_argc((*proc->lst)->args), child);
	else if ((ft_strncmp_len((*proc->lst)->args[0], "pwd", 3)) == 0)
		ft_pwd();
	else if ((ft_strncmp_len((*proc->lst)->args[0], "cd", 2)) == 0)
		ft_cd((*proc->lst)->args, proc->set, child);
	else if ((ft_strncmp_len((*proc->lst)->args[0], "export", 6)) == 0)
		export(proc->set, (*proc->lst)->args, child);
	else if ((ft_strncmp_len((*proc->lst)->args[0], "unset", 5)) == 0)
		unset(proc->set, (*proc->lst)->args, child);
	else if ((ft_strncmp_len((*proc->lst)->args[0], "exit", 4)) == 0)
		ft_exit((*proc->lst)->args, proc->set);
	else if ((ft_strncmp((*proc->lst)->args[0], "echo", 4)) == 0)
		ft_echo(node->args, node->outfd);
}
