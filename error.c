/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:41:05 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/22 13:07:54 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int ft_check_redirections(char *line_read, char c)
{
    int i;

    while (line_read[i])
    {
        if (line_read[i])
    }
}
*/
int ft_check_unclosed_quotes(char *line_read, char c)
{
    int i;
    int ret;

    i = 0;
    ret = 0;
    while (line_read[i])
    {
        if (line_read[i] == c)
        {
            if (!ret)
                ret = 1;
            else
                ret = 0;
        }
        i++;
    }
    if (ret)
    {
        ft_putstr_fd("papa$hell:", 2);
		ft_putstr_fd(" Syntax error, unclosed quotes\n", 2);
		return (1);
    }
    return (0);
}

int ft_check_empty_line(char *line_read)
{
    char *line;
    
    line = ft_strtrim(line_read, " ");
    if (line_read[0] == '\0')
    {
        free(line);
        return(1);
    }
    free (line);
    return(0);
}

int	ft_check_empty_pipe(char *line_read)
{
	int	i;

	i = 0;
	while (line_read[i] && line_read[i] == ' ')
		i++;
	if (line_read[i] == '|')
	{
		ft_putstr_fd("papa$hell:", 2);
		ft_putstr_fd(" Syntax error near unexpected token '|'\n", 2);
		return (1);
	}
	i = -1;
	while (line_read[++i])
	{
		if (line_read[i] == '|' && line_read[i + 1] == '\0')
		{
			ft_putstr_fd("papa$hell:", 2);
			ft_putstr_fd(" Syntax error near unexpected token '|'\n", 2);
			return (1);
		}
	}
	return (0);
}

void    ft_check_errors(t_proc *proc)
{
    if (ft_check_empty_line(proc->line_read))
        printf("Empty line\n");
    if (ft_check_empty_pipe(proc->line_read))
        exit (2);
    if (ft_check_unclosed_quotes(proc->line_read, 34))
        exit (2);
    if (ft_check_unclosed_quotes(proc->line_read, 39))
        exit (2);
}