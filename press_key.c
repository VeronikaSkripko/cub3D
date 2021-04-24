/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:25:16 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:25:18 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	press_key_right_left(int key, t_vars *vars)
{
	if (key == KEY_A)
	{
		if (vars->map[(int)(vars->y_plr + sinf(vars->angl_plr - (PI
						/ 2)) * SPEED) / SIZE][(int)(vars->x_plr)
						/ SIZE] != '1')
			vars->y_plr += sinf(vars->angl_plr - (PI / 2)) * SPEED;
		if (vars->map[(int)(vars->y_plr) / SIZE][(int)(vars->x_plr
			+ cosf(vars->angl_plr - (PI / 2)) * SPEED) / SIZE] != '1')
			vars->x_plr += cosf(vars->angl_plr - (PI / 2)) * SPEED;
	}
	if (key == KEY_D)
	{
		if (vars->map[(int)(vars->y_plr + sinf(vars->angl_plr + (PI
						/ 2)) * SPEED) / SIZE][(int)(vars->x_plr)
						/ SIZE] != '1')
			vars->y_plr += sinf(vars->angl_plr + (PI / 2)) * SPEED;
		if (vars->map[(int)(vars->y_plr) / SIZE][(int)(vars->x_plr
			+ cosf(vars->angl_plr + (PI / 2)) * SPEED) / SIZE] != '1')
			vars->x_plr += cosf(vars->angl_plr + (PI / 2)) * SPEED;
	}
	return (0);
}

int	press_key_up_down(int key, t_vars *vars)
{
	if (key == KEY_W)
	{
		vars->delta_x = cosf(vars->angl_plr) * SPEED;
		vars->delta_y = sinf(vars->angl_plr) * SPEED;
		if (vars->map[(int)vars->y_plr / SIZE][(int)(vars->x_plr
			+ 2 * vars->delta_x) / SIZE] != '1')
			vars->x_plr += vars->delta_x;
		if (vars->map[(int)(vars->y_plr + 2 * vars->delta_y)
			/ SIZE][(int)(vars->x_plr) / SIZE] != '1')
			vars->y_plr += vars->delta_y;
	}
	if (key == KEY_S)
	{
		vars->delta_x = cosf(vars->angl_plr) * SPEED;
		vars->delta_y = sinf(vars->angl_plr) * SPEED;
		if (vars->map[(int)vars->y_plr / SIZE][(int)(vars->x_plr
			- 2 * vars->delta_x) / SIZE] != '1')
			vars->x_plr -= vars->delta_x;
		if (vars->map[(int)(vars->y_plr - 2 * vars->delta_y)
			/ SIZE][(int)(vars->x_plr) / SIZE] != '1')
			vars->y_plr -= vars->delta_y;
	}
	return (0);
}

int	press_key(int key, t_vars *vars)
{
	if (key == KEY_W || key == KEY_S)
		press_key_up_down(key, vars);
	if (key == KEY_A || key == KEY_D)
		press_key_right_left(key, vars);
	if (key == ARROW_LEFT)
	{
		vars->angl_plr = vars->angl_plr - PI * SPEED_ANGLE;
		if (vars->angl_plr < 0)
			vars->angl_plr += 2 * PI;
		vars->delta_x = cosf(vars->angl_plr) * SPEED;
		vars->delta_y = sinf(vars->angl_plr) * SPEED;
	}
	if (key == ARROW_RIGHT)
	{
		vars->angl_plr = vars->angl_plr + PI * SPEED_ANGLE;
		if (vars->angl_plr > 2 * PI)
			vars->angl_plr -= 2 * PI;
		vars->delta_x = cosf(vars->angl_plr) * SPEED;
		vars->delta_y = sinf(vars->angl_plr) * SPEED;
	}
	if (key == KEY_ESC)
		exit(0);
	return (0);
}
