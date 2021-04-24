/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:23:44 by schaya            #+#    #+#             */
/*   Updated: 2021/04/22 17:22:34 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_wall_x_in_draw2(t_vars *vars, t_ray *vert, int **y)
{
	if (vert->angl > 3 * PI / 2 || vert->angl < PI / 2)
	{
		vars->color_wall = *(unsigned int *)(vars->texture_addr[2]
				+ ((int)((vars->offset_wall + **y) * vars->y_step_wall))
				* (vars->texture_line_length[2]) + ((int)vert->ry % SIZE)
				* (vars->texture_width[2] / SIZE)
				* (vars->texture_bits_per_pixel[2] / 8));
	}
	else
	{
		vars->color_wall = *(unsigned int *)(vars->texture_addr[3]
				+ ((int)((vars->offset_wall + (float)**y) * vars->y_step_wall))
				* (vars->texture_line_length[3]) + ((int)vert->ry % SIZE)
				* (vars->texture_width[3] /** (-1)*/ / SIZE)
				* (vars->texture_bits_per_pixel[3] / 8));
	}
}

void	process_wall_x_in_draw(t_vars *vars, t_ray *hor, t_ray *vert, int *y)
{
	if (vars->flag_ray == 1)
	{
		if (hor->angl > PI)
		{
			vars->color_wall = *(unsigned int *)(vars->texture_addr[0]
					+ ((int)((vars->offset_wall + *y) * vars->y_step_wall))
					* (vars->texture_line_length[0]) + ((int)hor->rx % SIZE)
					* (vars->texture_width[0] / SIZE)
					* (vars->texture_bits_per_pixel[0] / 8));
		}
		else
		{
			vars->color_wall = *(unsigned int *)(vars->texture_addr[1]
					+ ((int)((vars->offset_wall + (float)*y)
							* vars->y_step_wall))
					* (vars->texture_line_length[1]) + ((int)hor->rx % SIZE)
					* (vars->texture_width[1] / SIZE)
					* (vars->texture_bits_per_pixel[1] / 8));
		}
	}
	if (vars->flag_ray == 2)
		process_wall_x_in_draw2(vars, vert, &y);
}

void	process_wall_y_in_draw(t_vars *vars, t_ray *hor, t_ray *vert, int *z)
{
	int	y;
	int	x;

	y = 0;
	while (y < vars->wall_h)
	{
		x = 0;
		while (x < 1)
		{
			process_wall_x_in_draw(vars, hor, vert, &y);
			my_mlx_pixel_put(vars, x + (*z + vars->render_size_x / 2),
				y + ((vars->render_size_y - vars->wall_h) / 2),
				vars->color_wall);
			x++;
		}
		y++;
	}
}
