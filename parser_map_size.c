/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:24:51 by schaya            #+#    #+#             */
/*   Updated: 2021/04/22 17:24:23 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing_map_size(t_vars *vars, char *buf)
{
	if (buf[0] == 'R' && buf[1] == ' ')
	{
		vars->render_size_y = 0;
		vars->render_size_x = 0;
		vars->screen_size_w = 0;
		vars->screen_size_h = 0;
		mlx_get_screen_size(vars->mlx, &vars->screen_size_w,
			&vars->screen_size_h);
		find_map_size(vars, buf + 1);
		if (vars->render_size_y < 300)
			vars->render_size_y = 300;
		if (vars->render_size_x < 300)
			vars->render_size_x = 300;
		if (vars->render_size_y > vars->screen_size_h)
			vars->render_size_y = vars->screen_size_h;
		if (vars->render_size_x > vars->screen_size_w)
			vars->render_size_x = vars->screen_size_w;
		vars->flag_r_found = 1;
	}
	else
		errors("Error\nОшибка в размере экрана");
}

void	find_map_size(t_vars *vars, char *buf)
{
	int	flag_x;
	int	flag_y;
	int	digit_count;

	flag_x = 0;
	flag_y = 0;
	digit_count = 0;
	add_render_x(vars, &buf, &flag_x, &digit_count);
	skip_spaces1(&buf);
	check_wrong_render_size_sym(buf);
	digit_count = 0;
	while (*buf >= '0' && *buf <= '9')
	{
		if (digit_count > 7)
			errors("Error\nСлишком большое число для размера экрана");
		vars->render_size_y = vars->render_size_y * 10 + ((*buf) - '0');
		buf++;
		flag_y = 1;
		digit_count++;
	}
	check_wrong_render_size_sym(buf);
	skip_spaces1(&buf);
	if ((flag_x == 1 && flag_y == 0) || flag_x == 0)
		errors("Error\nМало аргументов для размера экрана");
}

void	add_render_x(t_vars *vars, char **buf, int *flag_x, int *digit_count)
{
	skip_spaces1(buf);
	check_wrong_render_size_sym(*buf);
	while ((**buf) >= '0' && (**buf) <= '9')
	{
		if (*digit_count > 7)
			errors("Error\nСлишком большое число для размера экрана");
		else
		{
			vars->render_size_x = vars->render_size_x * 10 + ((**buf) - '0');
			(*buf)++;
			*flag_x = 1;
			(*digit_count)++;
		}
	}
}

void	check_wrong_render_size_sym(char *buf)
{
	while (((*buf) < '0' || (*buf) > '9') && ((*buf) != '\0'))
	{
		if ((*buf) == '-')
			errors("Error \nОтрицательное значение размера карты");
		errors("Error \nФормат разрешения экрана неверен");
	}
}

void	skip_spaces1(char **buf)
{
	while (**buf == ' ')
		(*buf)++;
}
