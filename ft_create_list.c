/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:48 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/02 20:46:51 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

t_node	*ft_new_node(char **args)
{
	t_node	*ret;

	ret = malloc(sizeof (t_node));
	memset(ret, 0, sizeof(t_node));
	if (!ret)
		return (NULL);
	ret->args = args;
	return (ret);
}

void	ft_add_node_back(t_proc *proc, t_node **node, t_node *new)
{
	if (*node)
	{
		proc->head = *node;
		while ((*node)->next)
			(*node) = (*node)->next;
		new->previous = *node;
		(*node)->next = new;
		(*node) = proc->head;
	}
	else
		(*node) = new;
}

void	ft_lstiter(t_proc *proc, void (*f)(t_proc *))
{
	if (!f || proc->lst == NULL)
		return ;
	while ((*proc->lst))
	{
		f((proc));
		(*proc->lst) = (*proc->lst)->next;
	}
	(*proc->lst) = proc->head;
}
