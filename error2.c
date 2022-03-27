/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:10:13 by jsolinis          #+#    #+#             */
/*   Updated: 2022/03/27 20:32:22 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_3redirections(char *line, char c, int *i)
{
	if (line[*i + 1] && line[*i + 1] == c)
	{
		if (line[*i + 2] && line[*i + 2] == c)
		{
			ft_putstr_fd("papa$hell: ", 2);
			ft_putendl_fd("syntax error near unexpected token `newline'", 2);
			return (1);
		}
		*i += 1;
	}
	*i += 1;
	return (0);
}

int	ft_check_redirections(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == c)
		{
			if (ft_check_3redirections(line, c, &i))
				return (1);
			while (line[i] && line[i] == 32)
				i++;
			if (line[i] == '\0' || line[i] == 60
				|| line[i] == 62 || line[i] == 124)
			{
				ft_putstr_fd("papa$hell: ", 2);
				ft_putendl_fd
					("syntax error near unexpected token `newline'", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}