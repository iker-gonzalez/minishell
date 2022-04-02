/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:00:37 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/02 10:42:36 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **argv, t_set *set)
{
	int	i;
	int	cmd_count;

	cmd_count = ft_count_argc(argv);
	if (cmd_count == 1)
		exit (0);
	if (cmd_count > 2)
		print_error(": too many arguments.", 1, argv[1], set);
	if (cmd_count == 2)
	{
		i = -1;
		while (argv[1][++i])
		{
			if (!ft_isdigit(argv[1][i]))
				print_error(": numeric argument required", 255, argv[1], set);
		}
		exit (ft_atoi(argv[1]));
	}
}