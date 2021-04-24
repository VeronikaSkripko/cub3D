/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:22:31 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:22:34 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_condition1_corners(t_vars *vars, int i, int j)
{
	if ((j == 0 || j == (ft_strlen(vars->whole_map[i]) - 1) || i == 0
			|| i == vars->nbr_str) && (vars->whole_map[i][j] != '1')
			&& (vars->whole_map[i][j] != ' '))
		errors("Error \nНевалидная карта");
}

void	check_map_condition2_zero_and_spaces(t_vars *vars, int i, int j)
{
	if ((j != 0 && vars->whole_map[i][j] == '0')
			&& (vars->whole_map[i][j - 1] == ' '
			|| vars->whole_map[i][j + 1] == ' '))
		errors("Error \nКарта не закрыта2");
}

void	check_map_condition3_zero_and_spaces(t_vars *vars, int i, int j)
{
	if ((i != 0 && vars->whole_map[i][j] == '0')
			&& (vars->whole_map[i + 1][j] == ' '
			|| vars->whole_map[i - 1][j] == ' '))
		errors("Error \nКарта не закрыта3");
}

void	check_map_condition4(t_vars *vars, int i, int j)
{
	if ((j != 0 && i != 0 && vars->whole_map[i][j] == '0')
			&& (vars->whole_map[i + 1][j] != '0'
			&& vars->whole_map[i + 1][j] != '1'
			&& vars->whole_map[i + 1][j] != '2'
			&& vars->whole_map[i + 1][j] != 'N' && vars->whole_map
			[i + 1][j] != 'S' && vars->whole_map[i + 1][j] != 'E'
			&& vars->whole_map [i + 1][j] != 'W'))
		errors("Error \nКарта не закрыта4");
	if ((j != 0 && i != 0 && vars->whole_map[i][j] == '0') && (vars->whole_map
			[i][j + 1] != '0' && vars->whole_map[i][j + 1]
			!= '1' && vars->whole_map[i][j + 1] != '2'
			&& vars->whole_map[i][j + 1] != 'N'
			&& vars->whole_map[i][j + 1] != 'S'
			&& vars->whole_map[i][j + 1] != 'E'
			&& vars->whole_map[i][j + 1] != 'W'))
		errors("Error \nКарта не закрыта4");
	check_map_condition5(vars, i, j);
}

void	check_map(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->nbr_str)
	{
		j = 0;
		while (j < ft_strlen(vars->whole_map[i]))
		{
			check_map_condition1_corners(vars, i, j);
			check_map_condition2_zero_and_spaces(vars, i, j);
			check_map_condition3_zero_and_spaces(vars, i, j);
			check_map_condition4(vars, i, j);
			j++;
		}
		i++;
	}
}
