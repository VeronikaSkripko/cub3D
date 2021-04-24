/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:23:36 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:23:38 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_sprite_x_in_draw(t_vars *vars, int *i)
{
	t_ray	hor;
	t_ray	vert;
	int		x;
	float	rad_per_pixel;

	x = 0;
	rad_per_pixel = 1 / (vars->render_size_x / (60 * RAD));
	while (x < vars->array_of_sprt[*i].sprite_w)
	{
		if (x + vars->sprite_start_point_x < 0 || x + vars->sprite_start_point_x
			>= vars->render_size_x)
		{
			x++;
			continue ;
		}
		vars->sprite_current_angle = vars->array_of_sprt[*i].sprite_angle
			+ (x * rad_per_pixel);
		hor = get_hor_ray_sprites(vars, vars->sprite_current_angle);
		vert = get_vert_ray_sprites(vars, vars->sprite_current_angle);
		if ((hor.flag_out == 3 && hor.dist < vert.dist) || (vert.flag_out == 3
				&& hor.dist > vert.dist))
			process_sprite_y_in_draw(vars, i, &x);
		x++;
	}
}

void	process_sprite_y_in_draw(t_vars *vars, int *i, int *x)
{
	int	y;

	y = 0;
	while (y < vars->array_of_sprt[*i].sprite_height)
	{
		vars->sprite_x_in_texture = ((float)(*x)
				/ vars->array_of_sprt[*i].sprite_w)
			* vars->sprite_texture_width;
		vars->sprite_color = *(unsigned int *)((vars->sprite_texture_addr
					+ (int)(vars->sprite_y_step * (y
							+ vars->sprite_y_offset))
					*(vars->sprite_line_length))
				+ (int)(vars->sprite_x_in_texture * (vars->sprite_bits_per_pixel
						/ 8)));
		if (vars->sprite_color == *(unsigned int *) vars->sprite_texture_addr)
		{
			y++;
			continue ;
		}
		my_mlx_pixel_put(vars, (*x) + vars->sprite_start_point_x,
			y + ((vars->render_size_y - vars->array_of_sprt[*i].sprite_height)
				/ 2), vars->sprite_color);
		y++;
	}
}

int	draw_sprites(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->sprite_count)
	{
		vars->map[vars->array_of_sprt[i].y][vars->array_of_sprt[i].x] = '2';
		define_sprite_h_w(vars, &i);
		define_sprite_angle(vars, &i);
		define_sprite_start_angle(vars, &i);
		check_offset(vars, &i);
		process_sprite_x_in_draw(vars, &i);
		vars->map[vars->array_of_sprt[i].y][vars->array_of_sprt[i].x] = '0';
		i++;
	}
	return (0);
}
