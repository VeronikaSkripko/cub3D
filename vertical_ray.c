/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:26:04 by schaya            #+#    #+#             */
/*   Updated: 2021/04/20 14:38:46 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	get_vert_ray(t_vars *vars, int z)
{
	t_ray	ray;
	int		flag_out;

	flag_out = 0;
	vert_ray(vars, &ray, &z, &flag_out);
	while (flag_out < 1)
	{
		if (ray.ry / SIZE < 0 || ray.ry / SIZE >= vars->nbr_str)
			break ;
		else if (vars->map[(int)ray.ry / SIZE][(int)ray.rx / SIZE] != '1')
		{
			ray.ry += ray.yo;
			ray.rx += ray.xo;
		}
		else if (vars->map[(int)ray.ry / SIZE][(int)ray.rx / SIZE] == '1')
		{
			flag_out = 2;
		}
	}
	ray.flag_out = flag_out;
	return (ray);
}

void	vert_ray_look_left(t_vars *vars, t_ray *ray, float *a_tan)
{
	ray->rx = (((int)vars->x_plr / SIZE) * SIZE) - 0.0001;
	ray->ry = (vars->x_plr - ray->rx) * (*a_tan) + vars->y_plr;
	ray->xo = -SIZE;
	ray->yo = (-1) * ray->xo * (*a_tan);
}

void	vert_ray(t_vars *vars, t_ray *ray, int *z, int *flag_out)
{
	float	a_tan;

	ray->angl = vars->angl_plr + *z * RAD * ((float)60 / vars->render_size_x);
	if (ray->angl < 0)
		ray->angl += 2 * PI;
	else if (ray->angl > 2 * PI)
		ray->angl -= 2 * PI;
	*flag_out = 0;
	a_tan = -tanf(ray->angl);
	if (ray->angl == 3 * PI / 2 || ray->angl == PI / 2)
	{
		ray->rx = vars->x_plr;
		ray->ry = vars->y_plr;
		*flag_out = 1;
	}
	else if (ray->angl > PI / 2 && ray->angl < 3 * PI / 2)
		vert_ray_look_left(vars, ray, &a_tan);
	else
	{
		ray->rx = (((int)vars->x_plr / SIZE) * SIZE) + SIZE;
		ray->ry = (vars->x_plr - ray->rx) * a_tan + vars->y_plr;
		ray->xo = SIZE;
		ray->yo = (-1) * ray->xo * a_tan;
	}
}
