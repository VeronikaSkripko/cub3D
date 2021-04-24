/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:25:10 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:52:23 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_plr_spaces(t_vars *vars, int **i, int **j)
{
	if ((vars->whole_map[(**i) + 1][**j] == ' ')
		|| (vars->whole_map[(**i) - 1][**j] == ' ')
		|| (vars->whole_map[**i][(**j) + 1] == ' ')
		|| (vars->whole_map[**i][(**j) - 1] == ' '))
	{
		errors("Error\nПробел перед игроком");
	}
}

void	player_pos(t_vars *vars)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	found = 0;
	vars->x_plr = 0;
	vars->y_plr = 0;
	while (i < vars->nbr_str)
	{
		j = 0;
		while (j < ft_strlen(vars->map[i]))
		{
			find_player_pos(vars, &i, &j, &found);
			j++;
		}
		i++;
	}
	if (vars->x_plr == 0 && vars->y_plr == 0)
		errors("Error\nНет игрока на карте");
}

void	find_player_pos(t_vars *vars, int *i, int *j, int *found)
{
	if ((vars->whole_map[*i][*j] == 'N' || vars->whole_map[*i][*j] == 'S'
		 || vars->whole_map[*i][*j] == 'W' || vars->whole_map[*i][*j] == 'E')
		&& (*found == 0))
	{
		vars->x_plr = (*j * SIZE) + SIZE / 2;
		vars->y_plr = (*i * SIZE) + SIZE / 2;
		check_plr_spaces(vars, &i, &j);
		player_angle(vars, i, j);
		*found = 1;
	}
	else if (((vars->whole_map[*i][*j] == 'N' || vars->whole_map[*i][*j] == 'S'
		|| vars->whole_map[*i][*j] == 'W' || vars->whole_map[*i][*j] == 'E')
			&& (*found == 1)))
	{
		errors("Error \nНеверное количество игроков на карте");
	}
}

void	player_angle(t_vars *vars, int *i, int *j)
{
	if (vars->map[*i][*j] == 'N')
		vars->angl_plr = 3 * PI / 2;
	if (vars->map[*i][*j] == 'S')
		vars->angl_plr = PI / 2;
	if (vars->map[*i][*j] == 'W')
		vars->angl_plr = PI;
	if (vars->map[*i][*j] == 'E')
		vars->angl_plr = 0.00001;
}
