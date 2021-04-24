#include "cub3d.h"

t_ray	get_hor_ray(t_vars *vars, int z)
{
	t_ray 	ray;
	int		flag_out;

	flag_out = 0;
	hor_ray(vars, &ray, &z, &flag_out);
	while(flag_out < 1)
	{
		if (ray.rx < 0)
			break;
		if(ray.ry / SIZE < 0 || ray.ry / SIZE >= vars->nbr_str)
			break;
		if(ray.rx < 0 || ray.rx > ft_strlen(vars->map[(int)ray.ry / SIZE]) * SIZE)
			break;
		if(vars->map[(int)ray.ry / SIZE][(int)ray.rx / SIZE] != '1') //check next horizontal line
		{
			ray.rx += ray.xo;
			ray.ry += ray.yo;
		}
		else // hit wall
		{
			flag_out = 2;
		}
		ray.flag_out = flag_out;
	}
	return(ray);
}

void hor_ray(t_vars *vars, t_ray *ray, int *z, int *flag_out)
{
	float	aTan;

	ray->angl = vars->angl_plr + *z * RAD * ((float)60 / vars->render_size_x);
	if (ray->angl < 0)
		ray->angl += 2 * Pi;
	else if (ray->angl > 2 * Pi)
		ray->angl -= 2 * Pi;
	flag_out = 0;
	if (ray->angl == 3 * Pi / 2 || ray->angl == Pi / 2)
		aTan = -0.000001;
	else
		aTan = -1/tanf(ray->angl);
	if(ray->angl > Pi) // looking up
	{
		ray->ry = (((int)vars->y_plr / SIZE) * SIZE) - 0.0001;
		ray->rx = (vars->y_plr - ray->ry) * aTan + vars->x_plr;
		ray->yo = -SIZE;
		ray->xo = (-1) * ray->yo * aTan;
	}
	if(ray->angl < Pi) // looking down
	{
		ray->ry = (((int)vars->y_plr / SIZE) * SIZE) + SIZE;
		ray->rx = (vars->y_plr - ray->ry) * aTan + vars->x_plr;
		ray->yo = SIZE;
		ray->xo = (-1) * ray->yo * aTan;
	}
	if(ray->angl == 0 || ray->angl == Pi) //looking straight left or right
	{
		ray->ry = vars->y_plr;
		ray->rx = vars->x_plr;
		*flag_out = 1;
	}
}

t_ray get_vert_ray(t_vars *vars, int z)
{
	t_ray 	ray;
	int		flag_out;

	flag_out = 0;
	vert_ray(vars, &ray, &z, &flag_out);
	while(flag_out < 1)
	{
		if(ray.ry / SIZE < 0 || ray.ry / SIZE >= vars->nbr_str)
			break;
		else if(vars->map[(int)ray.ry / SIZE][(int)ray.rx / SIZE] != '1')
		{
			ray.ry += ray.yo;
			ray.rx += ray.xo;
		}
		else if(vars->map[(int)ray.ry / SIZE][(int)ray.rx / SIZE] == '1')
		{
			flag_out = 2;
		}
	}
	ray.flag_out = flag_out;
	return(ray);
}

void vert_ray(t_vars *vars, t_ray *ray, int *z, int *flag_out)
{
	float 	aTan;

	ray->angl = vars->angl_plr + *z * RAD * ((float)60 / vars->render_size_x);// 60 градусов / ширина экрана
	if (ray->angl < 0)
		ray->angl += 2 * Pi;
	else if (ray->angl > 2 * Pi)
		ray->angl -= 2 * Pi;
	*flag_out = 0;
	aTan = -tanf(ray->angl);
	if(ray->angl == 3 * Pi / 2 || ray->angl == Pi / 2) //looking straight up or down
	{
		ray->rx = vars->x_plr;
		ray->ry = vars->y_plr;
		*flag_out = 1;
	}
	else if(ray->angl > Pi/2 && ray->angl < 3 * Pi / 2) //looking left
	{
		ray->rx = (((int)vars->x_plr / SIZE) * SIZE) - 0.0001;
		ray->ry = (vars->x_plr - ray->rx) * aTan + vars->y_plr;
		ray->xo = -SIZE;
		ray->yo = (-1) * ray->xo * aTan;
	}
	else /*(ray.angl < Pi / 2 || ray.angl > 3 * Pi / 2)*/ //looking right
	{
		ray->rx = (((int)vars->x_plr / SIZE) * SIZE) + SIZE;
		ray->ry = (vars->x_plr - ray->rx) * aTan + vars->y_plr;
		ray->xo = SIZE;
		ray->yo = (-1) * ray->xo * aTan;
	}
}