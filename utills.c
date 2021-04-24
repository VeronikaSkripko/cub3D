/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:25:59 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:26:01 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*change_spaces(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == ' ')
			buf[i] = '1';
		i++;
	}
	return (buf);
}

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

float	dist(float px, float py, float hor_ray_x, float hot_ray_y)
{
	return (sqrt((hor_ray_x - px) * (hor_ray_x - px)
			+ (hot_ray_y - py) * (hot_ray_y - py)));
}

void	add_texture_addr(t_vars *vars)
{
	vars->texture_addr[0] = mlx_get_data_addr(vars->texture[0],
			&vars->texture_bits_per_pixel[0],
			&vars->texture_line_length[0], &vars->texture_endian[0]);
	vars->texture_addr[1] = mlx_get_data_addr(vars->texture[1],
			&vars->texture_bits_per_pixel[1],
			&vars->texture_line_length[1], &vars->texture_endian[1]);
	vars->texture_addr[2] = mlx_get_data_addr(vars->texture[2],
			&vars->texture_bits_per_pixel[2],
			&vars->texture_line_length[2], &vars->texture_endian[2]);
	vars->texture_addr[3] = mlx_get_data_addr(vars->texture[3],
			&vars->texture_bits_per_pixel[3],
			&vars->texture_line_length[3], &vars->texture_endian[3]);
}
