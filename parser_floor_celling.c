/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_floor_celling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:24:45 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:24:47 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	south_or_sprite(t_vars *vars, char *buf)
{
	int	i;

	i = 1;
	if ((buf[i] == 'O') && (buf[i + 1] == ' '))
		make_texture(vars, buf);
	if (buf[i] == ' ')
		make_sprite(vars, buf + 1);
}

unsigned int	turn_rgb(unsigned int red, unsigned int green,
						 unsigned int blue)
{
	return ((red * 256 * 256) + (green * 256) + blue);
}

unsigned int	ft_atoi_color(char *buf, int *i, char c)
{
	unsigned int	res;

	res = 0;
	if (!(buf[*i] >= '0' && buf[*i] <= '9'))
		errors("Error \nОшибка в формате цвета");
	while (buf[*i] != c && buf[*i] != '\0')
	{
		if (!(buf[*i] >= '0' && buf[*i] <= '9'))
			errors("Error \nОшибка в формате цвета");
		res = res * 10 + (buf[*i] - '0');
		if (res > 255)
			errors("Error \nСлишком большое значение для цвета");
		(*i)++;
	}
	return (res);
}

void	make_celling(t_vars *vars, char *buf)
{
	unsigned int	color[3];
	int				i;

	i = 0;
	vars->flag_c_found = 1;
	if (buf[i] != ' ')
		errors("Error\nФормат записи неверен");
	while (buf[i] == ' ')
		(i)++;
	color[0] = ft_atoi_color(buf, &i, ',');
	i++;
	color[1] = ft_atoi_color(buf, &i, ',');
	i++;
	color[2] = ft_atoi_color(buf, &i, ' ');
	while (buf[i] != '\0')
	{
		if (buf[i] != ' ')
			errors("Error\n Wrong color name");
		i++;
	}
	vars->celling_color = turn_rgb(color[0], color[1], color[2]);
}

void	make_floor(t_vars *vars, char *buf)
{
	unsigned int	color[3];
	int				i;

	i = 0;
	vars->flag_f_found = 1;
	if (buf[i] != ' ')
		errors("Error\nФормат записи неверен");
	while (buf[i] == ' ')
		(i)++;
	color[0] = ft_atoi_color(buf, &i, ',');
	i++;
	color[1] = ft_atoi_color(buf, &i, ',');
	i++;
	color[2] = ft_atoi_color(buf, &i, ' ');
	while (buf[i] != '\0')
	{
		if (buf[i] != ' ')
			errors("Error\n Wrong color name");
		i++;
	}
	vars->floor_color = turn_rgb(color[0], color[1], color[2]);
}
