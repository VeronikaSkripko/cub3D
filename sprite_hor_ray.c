/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_hor_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:25:40 by schaya            #+#    #+#             */
/*   Updated: 2021/04/21 15:11:02 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	get_hor_ray_sprites(t_vars *vars, float angle)
{
	t_ray	ray;
	int		flag_out;

	flag_out = 0;
	ray.dist = 2000000000;
	hor_ray_sprites(vars, &ray, angle, &flag_out);
	while (flag_out < 1)
	{
		if (ray.rx < 0)
			break ;
		if (ray.ry / SIZE < 0 || ray.ry / SIZE >= vars->nbr_str)
			break ;
		if (ray.rx < 0 || ray.rx > ft_strlen
			(vars->map[(int)ray.ry / SIZE]) * SIZE)
			break ;
		hor_ray_sprite1(vars, &ray, &flag_out);
	}
	return (ray);
}

void	hor_ray_sprite_look_up(t_vars *vars, t_ray *ray, float *a_tan)
{
	ray->ry = (((int)vars->y_plr / SIZE) * SIZE) - 0.0001;
	ray->rx = (vars->y_plr - ray->ry) * (*a_tan) + vars->x_plr;
	ray->yo = -SIZE;
	ray->xo = (-1) * ray->yo * (*a_tan);
}

void	hor_ray_sprite_look_down(t_vars *vars, t_ray *ray, float *a_tan)
{
	ray->ry = (((int)vars->y_plr / SIZE) * SIZE) + SIZE;
	ray->rx = (vars->y_plr - ray->ry) * (*a_tan) + vars->x_plr;
	ray->yo = SIZE;
	ray->xo = (-1) * ray->yo * (*a_tan);
}

void	hor_ray_sprites(t_vars *vars, t_ray *ray, float angle, int *flag_out)
{
	float	a_tan;

	ray->angl = angle;
	if (ray->angl < 0)
		ray->angl += 2 * PI;
	else if (ray->angl > 2 * PI)
		ray->angl -= 2 * PI;
	flag_out = 0;
	if (ray->angl == 3 * PI / 2 || ray->angl == PI / 2)
		a_tan = -0.000001;
	else
		a_tan = -1 / tanf(ray->angl);
	if (ray->angl > PI)
		hor_ray_sprite_look_up(vars, ray, &a_tan);
	if (ray->angl < PI)
		hor_ray_sprite_look_down(vars, ray, &a_tan);
	if (ray->angl == 0 || ray->angl == PI)
	{
		ray->ry = vars->y_plr;
		ray->rx = vars->x_plr;
		*flag_out = 1;
	}
}

void	hor_ray_sprite1(t_vars *vars, t_ray *ray, int *flag_out)
{
	if (vars->map[(int)ray->ry / SIZE][(int)ray->rx / SIZE] != '2'
		&& vars->map[(int)ray->ry / SIZE][(int)ray->rx / SIZE] != '1')
	{
		ray->rx += ray->xo;
		ray->ry += ray->yo;
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
	ray->flag_out = *flag_out;
}
