/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 09:17:46 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/29 13:50:37 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* export unset cd exit =>si solo hay un proceso, lo ejecutará
 *  en todo caso el padre. Si no el hijo, si bien los cambios no
 *  se verán reflejados (moriran con el hijo). p.e.=> ls | export a=2 
 *  en este caso el export lo haría el hijo, si bien no podriamos ver 
 *  la variable en env ya que este cambio muere cuando el hijo deja
 *  de ejecutarse.*/

int	ft_export_errors(char *argv)
{
	int	i;

	i = 0;
	if (!ft_isalpha(argv[0]) && argv[0] != '_')
	{
		ft_putendl_fd("papa$hell: export: not a valid identifier", 2);
		return (1);
	}
	if (!ft_findchar(argv, '='))
		return (1);
	while (argv[i] != '=')
	{
		if (!ft_isalnum(argv[i]) && argv[i] != '_')
		{
			ft_putendl_fd("papa$hell: export: not a valid identifier", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_varlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

void	edit_var(t_set *set, char *var)
{
	int	var_len;
	int	i;

	var_len = ft_varlen(var);
	i = -1;
	while (set->env[++i])
	{
		if ((ft_strncmp(set->env[i], var, var_len) == 0))
			set->env[i] = ft_strdup(var);
	}
}

char	**add_var(t_set *set, char *var)
{
	int		i;
	char	**tmp;

	i = 0;
	while (set->env[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (set->env[++i])
			tmp[i] = ft_strdup(set->env[i]);
	tmp[i] = ft_strdup(var);
	tmp[i + 1] = NULL;
	ft_free_double_char(set->env);
	return (tmp);
}

void	export(t_set *set, char **argv)
{
	int	i;
	int	k;
	int	var_len;
	int	edit;

	i = 0;
	edit = 0;
	while (argv[++i])
	{
		k = -1;
		if (!ft_export_errors(argv[i]))
		{
			var_len = ft_varlen(argv[i]);
			while (set->env[++k])
			{
				if (((ft_strncmp(set->env[k], argv[i], var_len)) == 0)
					&& ++edit)
					edit_var(set, argv[i]);
			}
			if (!edit)
				set->env = add_var(set, argv[i]);
		}
	}
}
