/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_vert_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:25:46 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:25:48 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_vert_ray_sprites_loop(t_vars *vars, t_ray *ray, int *flag_out)
{
	while (*flag_out < 1)
	{
		if (ray->ry / SIZE < 0 || ray->ry / SIZE >= vars->nbr_str)
			break ;
		else if (vars->map[(int)ray->ry / SIZE][(int)ray->rx / SIZE] != '1'
			&& vars->map[(int)ray->ry / SIZE][(int)ray->rx / SIZE] != '2')
		{
			ray->ry += ray->yo;
			ray->rx += ray->xo;
		}
		else if (vars->map[(int)ray->ry / SIZE][(int)ray->rx / SIZE] == '2')
		{
			ray->dist = dist(vars->x_plr, vars->y_plr, ray->rx, ray->ry);
			*flag_out = 3;
		}
		else
		{
			ray->dist = dist(vars->x_plr, vars->y_plr, ray->rx, ray->ry);
			*flag_out = 2;
		}
	}
}

t_ray	get_vert_ray_sprites(t_vars *vars, float angle)
{
	t_ray	ray;
	int		flag_out;

	flag_out = 0;
	vert_ray_sprites(vars, &ray, angle, &flag_out);
	ray.dist = 2000000000;
	get_vert_ray_sprites_loop(vars, &ray, &flag_out);
	ray.flag_out = flag_out;
	return (ray);
}

void	vert_ray_sprites_conditions(t_vars *vars, t_ray *ray, int **flag_out)
{
	float	aTan;

	aTan = -tanf(ray->angl);
	if (ray->angl == 3 * PI / 2 || ray->angl == PI / 2)
	{
		ray->rx = vars->x_plr;
		ray->ry = vars->y_plr;
		**flag_out = 1;
	}
	else if (ray->angl > PI / 2 && ray->angl < 3 * PI / 2)
	{
		ray->rx = (((int)vars->x_plr / SIZE) * SIZE) - 0.0001;
		ray->ry = (vars->x_plr - ray->rx) * aTan + vars->y_plr;
		ray->xo = -SIZE;
		ray->yo = (-1) * ray->xo * aTan;
	}
	else
	{
		ray->rx = (((int)vars->x_plr / SIZE) * SIZE) + SIZE;
		ray->ry = (vars->x_plr - ray->rx) * aTan + vars->y_plr;
		ray->xo = SIZE;
		ray->yo = (-1) * ray->xo * aTan;
	}
}

void	vert_ray_sprites(t_vars *vars, t_ray *ray, float angle, int *flag_out)
{
	ray->angl = angle;
	if (ray->angl < 0)
		ray->angl += 2 * PI;
	else if (ray->angl > 2 * PI)
		ray->angl -= 2 * PI;
	*flag_out = 0;
	vert_ray_sprites_conditions(vars, ray, &flag_out);
}
