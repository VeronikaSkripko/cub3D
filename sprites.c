/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:25:53 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:25:55 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	define_sprite_h_w(t_vars *vars, int *i)
{
	float	pixel_per_rad;

	pixel_per_rad = vars->render_size_x / (60 * RAD);
	vars->array_of_sprt[*i].sprite_height = (float)vars->render_size_x
		* SIZE / vars->array_of_sprt[*i].sprt_dist;
	vars->array_of_sprt[*i].sprite_w = vars->array_of_sprt[*i].sprite_height;
	vars->sprite_angle_range = (float)vars->array_of_sprt[*i].sprite_w
		/ pixel_per_rad;
	vars->sprite_y_step = (float)vars->sprite_texture_height
		/ vars->array_of_sprt[*i].sprite_height;
}

void	define_sprite_angle(t_vars *vars, int *i)
{
	vars->array_of_sprt[*i].sprite_angle -= vars->sprite_angle_range * 0.5;
	if (vars->array_of_sprt[*i].sprite_angle < 0)
		vars->array_of_sprt[*i].sprite_angle += 2 * PI;
	if (vars->array_of_sprt[*i].sprite_angle > 2 * PI)
		vars->array_of_sprt[*i].sprite_angle -= 2 * PI;
}

void	define_sprite_start_angle(t_vars *vars, int *i)
{
	vars->sprite_start_angl = vars->angl_plr
		- vars->array_of_sprt[*i].sprite_angle;
	if (vars->sprite_start_angl < 0)
		vars->sprite_start_angl += 2 * PI;
	if (vars->sprite_start_angl > 2 * PI)
		vars->sprite_start_angl -= 2 * PI;
	if (vars->sprite_start_angl > PI)
		vars->sprite_start_angl -= 2 * PI;
	vars->sprite_start_angl = vars->sprite_start_angl * (-1);
	vars->sprite_start_angl += 30 * RAD;
}

void	check_offset(t_vars *vars, int *i)
{
	float	pixel_per_rad;

	pixel_per_rad = vars->render_size_x / (60 * RAD);
	vars->sprite_start_point_x = vars->sprite_start_angl * pixel_per_rad;
	vars->sprite_y_offset = 0;
	if (vars->array_of_sprt[*i].sprite_height > vars->render_size_y)
	{
		vars->sprite_y_offset = ((float)vars->array_of_sprt[*i].sprite_height
				- (float)vars->render_size_y) / 2;
		vars->array_of_sprt[*i].sprite_height = vars->render_size_y;
	}
}
