#include "minishell.h"
#include <string.h>

void print_list (t_node **lst)
{
	while (*lst)
	{
		printf("content: %s\n", (*lst)->content);
		printf("single_quoted: %d\n", (*lst)->single_quoted);
		printf("double_quoted: %d\n", (*lst)->double_quoted);
		printf("pipe: %d\n", (*lst)->pipe);
		printf("dollar: %d\n", (*lst)->dollar);
		printf("redirection: %d\n", (*lst)->redirection);
		printf("previous: %p\n", (*lst)->previous);
		printf("next: %p\n", (*lst)->next);
		printf("==============================\n");
		*lst = (*lst)->next;
	}
}

void ft_gen_lst(t_proc *proc)
{
    int i;

    proc->tokens = ft_split(proc->line_read, ' ');
    i = 0;
    while (proc->tokens[i])
        i++;
	proc->cmd_count = i;
    proc->lst = malloc(sizeof(t_node) * proc->cmd_count);
    ft_memset((proc->lst), 0, sizeof(t_node *));
    i = 0;
    while (proc->tokens[i])
    {
        ft_add_node_back(proc->lst, ft_new_node(proc->tokens[i]));
        i++;
    }
}

t_node	*ft_new_node(char *content)
{
	t_node *ret;

	ret = malloc(sizeof (t_node));
	memset(ret, 0, sizeof(t_node));
	if (!ret)
		return NULL;
	ret->content = content;
	return (ret);
}

void	ft_add_node_back(t_node **node, t_node *new)
{
	t_node *head;

	head = NULL;
	if (*node)
	{
		head = *node;
		while((*node)->next)
			(*node) = (*node)->next;
		new->previous = *node;
		(*node)->next = new;
		(*node) = head;
	}
	else
		(*node) = new;
}