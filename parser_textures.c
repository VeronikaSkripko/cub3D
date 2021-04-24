/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:24:58 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:25:00 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	make_texture(t_vars *vars, char *buf)
{
	if ((buf[0] == 'N') && (buf[1] == 'O') && (buf[2] == ' '))
		work_with_no_texture(vars, buf + 2);
	else if ((buf[0] == 'S') && (buf[1] == 'O') && (buf[2] == ' '))
		work_with_so_texture(vars, buf + 2);
	else if ((buf[0] == 'E') && (buf[1] == 'A') && (buf[2] == ' '))
		work_with_ea_texture(vars, buf + 2);
	else if ((buf[0] == 'W') && (buf[1] == 'E') && (buf[2] == ' '))
		work_with_we_texture(vars, buf + 2);
	else
		errors("Error \nНеправильно задана текстура");
}

void	work_with_no_texture(t_vars *vars, char *buf)
{
	vars->flag_no_found = 1;
	while (*buf == ' ')
		buf++;
	vars->texture_path[0] = ft_strdup(buf);
}

void	work_with_so_texture(t_vars *vars, char *buf)
{
	vars->flag_so_found = 1;
	while (*buf == ' ')
		buf++;
	vars->texture_path[1] = ft_strdup(buf);
}

void	work_with_ea_texture(t_vars *vars, char *buf)
{
	vars->flag_ea_found = 1;
	while (*buf == ' ')
		buf++;
	vars->texture_path[2] = ft_strdup(buf);
}

void	work_with_we_texture(t_vars *vars, char *buf)
{
	vars->flag_we_found = 1;
	while (*buf == ' ')
		buf++;
	vars->texture_path[3] = ft_strdup(buf);
}
