/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:23:21 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:23:23 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_distance(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->sprite_count)
	{
		vars->array_of_sprt[i].sprt_dist = dist(vars->x_plr,
				vars->y_plr, vars->array_of_sprt[i].sprite_x,
				vars->array_of_sprt[i].sprite_y);
		i++;
	}
}

void	sort_sprite(t_vars *vars)
{
	int			i;
	int			j;
	t_sprite	bubble;

	i = 0;
	while (i < vars->sprite_count)
	{
		j = 1;
		while (j < vars->sprite_count)
		{
			if (vars->array_of_sprt[j].sprt_dist
				> vars->array_of_sprt[j - 1].sprt_dist)
			{
				bubble = vars->array_of_sprt[j - 1];
				vars->array_of_sprt[j - 1] = vars->array_of_sprt[j];
				vars->array_of_sprt[j] = bubble;
			}
			j++;
		}
		i++;
	}
}

void	angle_sprite(t_vars *vars)
{
	float	delta_x;
	int		i;

	i = 0;
	while (i < vars->sprite_count)
	{
		delta_x = vars->array_of_sprt[i].sprite_x - vars->x_plr;
		vars->array_of_sprt[i].sprite_angle = acos(delta_x
				/ vars->array_of_sprt[i].sprt_dist);
		if (vars->y_plr > vars->array_of_sprt[i].sprite_y)
		{
			vars->array_of_sprt[i].sprite_angle = 2 * PI
				- vars->array_of_sprt[i].sprite_angle;
		}
		i++;
	}
}

void	check_sprite(t_vars *vars)
{
	sprite_distance(vars);
	sort_sprite(vars);
	angle_sprite(vars);
	draw_sprites(vars);
}
