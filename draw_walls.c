/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:23:50 by schaya            #+#    #+#             */
/*   Updated: 2021/04/20 14:33:17 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_celling_floor(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->render_size_y)
	{
		j = 0;
		while (j < vars->render_size_x)
		{
			my_mlx_pixel_put(vars, j, i, 0x00000000);
			if (i < vars->render_size_y / 2)
				my_mlx_pixel_put(vars, j, i, vars->celling_color);
			else
				my_mlx_pixel_put(vars, j, i, vars->floor_color);
			j++;
		}
		i++;
	}
}

void	find_wall_h_part2(t_vars *vars, t_ray *hor, t_ray *vert, int **z)
{
	if (hor->flag_out != 2)
	{
		vars->wall_h = vars->render_size_x * SIZE / (dist(vars->x_plr,
					vars->y_plr, vert->rx, vert->ry) * cos(fabs((float)**z
						/ (float)(vars->render_size_x / 60)) * RAD));
		vars->flag_ray = 2;
	}
	else if (dist(vars->x_plr, vars->y_plr, hor->rx, hor->ry)
		< dist(vars->x_plr, vars->y_plr, vert->rx, vert->ry))
	{
		vars->wall_h = vars->render_size_x * SIZE / (dist(vars->x_plr,
					vars->y_plr, hor->rx, hor->ry) * cos(fabs((float)**z
						/ (float)(vars->render_size_x / 60)) * RAD));
		vars->flag_ray = 1;
	}
	else
	{
		vars->wall_h = vars->render_size_x * SIZE / (dist(vars->x_plr,
					vars->y_plr, vert->rx, vert->ry) * cos(fabs((float)**z
						/ (float)(vars->render_size_x / 60)) * RAD));
		vars->flag_ray = 2;
	}
}

void	find_wall_h(t_vars *vars, t_ray *hor, t_ray *vert, int *z)
{
	if (vert->flag_out != 2)
	{
		vars->wall_h = vars->render_size_x * SIZE / (dist(vars->x_plr,
					vars->y_plr, hor->rx, hor->ry) * cos(fabs((float)*z
						/ (float)(vars->render_size_x / 60)) * RAD));
		vars->flag_ray = 1;
	}
	else
	{
		find_wall_h_part2(vars, hor, vert, &z);
	}
	vars->y_step_wall = (float)vars->texture_height[0] / (float)vars->wall_h;
	vars->offset_wall = 0;
	if (vars->wall_h > vars->render_size_y)
	{
		vars->offset_wall = (vars->wall_h - vars->render_size_y) / 2;
		vars->wall_h = vars->render_size_y;
	}
}

int	draw_map(t_vars *vars)
{
	t_ray	hor;
	t_ray	vert;
	int		z;

	z = vars->render_size_x * (-0.5);
	draw_celling_floor(vars);
	while (z < vars->render_size_x / 2)
	{
		hor = get_hor_ray(vars, z);
		vert = get_vert_ray(vars, z);
		find_wall_h(vars, &hor, &vert, &z);
		process_wall_y_in_draw(vars, &hor, &vert, &z);
		z++;
	}
	return (0);
}
