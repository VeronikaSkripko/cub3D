/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:22:43 by schaya            #+#    #+#             */
/*   Updated: 2021/04/20 14:29:33 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_elem(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->nbr_str)
	{
		j = 0;
		while (j < ft_strlen(vars->whole_map[i]))
		{
			if (vars->whole_map[i][j] != '0' && vars->whole_map[i][j] != '1' &&
			   vars->whole_map[i][j] != '2' && vars->whole_map[i][j] != ' ' &&
			   vars->whole_map[i][j] != 'N' && vars->whole_map[i][j] != 'S' &&
			   vars->whole_map[i][j] != 'E' && vars->whole_map[i][j] != 'W' &&
			   vars->whole_map[i][j] != '\0')
				errors("Error \nНеправильный символ на карте");
			j++;
		}
		i++;
	}
}

void	check_map_condition6(t_vars *vars, int i, int j)
{
	if ((j != 0 && i != 0 && vars->whole_map[i][j] == '2')
			&& (vars->whole_map[i + 1][j] != '0'
			&& vars->whole_map[i + 1][j] != '1'
			&& vars->whole_map[i + 1][j] != '2'
			&& vars->whole_map[i + 1][j] != 'N' && vars->whole_map
			[i + 1][j] != 'S' && vars->whole_map[i + 1][j] != 'E'
			&& vars->whole_map [i + 1][j] != 'W'))
		errors("Error \nКарта не закрыта");
	if ((j != 0 && i != 0 && vars->whole_map[i][j] == '2') && (vars->whole_map
			[i][j + 1] != '0' && vars->whole_map[i][j + 1]
			!= '1' && vars->whole_map[i][j + 1] != '2'
			&& vars->whole_map[i][j + 1] != 'N'
			&& vars->whole_map[i][j + 1] != 'S'
			&& vars->whole_map[i][j + 1] != 'E'
			&& vars->whole_map[i][j + 1] != 'W'))
		errors("Error \nКарта не закрыта");
}

void	check_map_condition5(t_vars *vars, int i, int j)
{
	if (((j != 0 && i != 0 && vars->whole_map[i][j] == 'N') || (j != 0 && i != 0
			&& vars->whole_map[i][j] == 'S')
			|| (j != 0 && i != 0 && vars->whole_map [i][j] == 'W')
			|| (j != 0 && i != 0 && vars->whole_map[i][j] == 'E'))
			&& (vars->whole_map[i][j + 1] != '0'
			&& vars->whole_map[i][j + 1] != '1'
			&& vars->whole_map[i][j + 1] != '2'))
		errors("Error \nКарта не закрыта");
	if (((j != 0 && i != 0 && vars->whole_map[i][j] == 'N') || (j != 0 && i != 0
			&& vars->whole_map[i][j] == 'S')
			|| (j != 0 && i != 0 && vars->whole_map[i][j] == 'W')
			|| (j != 0 && i != 0 && vars->whole_map[i][j] == 'E'))
			&& (vars->whole_map[i + 1][j] != '0'
			&& vars->whole_map[i + 1][j] != '1'
			&& vars->whole_map[i + 1][j] != '2'))
		errors("Error \nКарта не закрыта");
	check_map_condition6(vars, i, j);
}
