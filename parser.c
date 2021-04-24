/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:25:04 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:25:06 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	skip_spaces(char **buf, int *flag, t_vars *vars)
{
	int	i;

	i = 0;
	while (**buf == ' ')
		(*buf)++;
	if (((*buf)[i] == 'R') || ((*buf)[i] == 'N' && (*buf)[i + 1] == 'O')
		|| ((*buf)[i] == 'S') || ((*buf)[i] == 'W' && (*buf)[i + 1] == 'E')
		|| ((*buf)[i] == 'E' && (*buf)[i + 1] == 'A') || ((*buf)[i] == 'C')
		|| ((*buf)[i] == 'F'))
	{
		(*flag)++;
		return (**buf);
	}
	else
	{
		if (**buf != '\0' && vars->letter_flag != 9)
			errors("Error\nНеверный индификатор");
	}
	return (0);
}

int	check_letter_id(char *buf, t_vars *vars, int flag)
{
	char	index;

	index = skip_spaces(&buf, &flag, vars);
	if (index == 'R')
		parsing_map_size(vars, buf);
	if ((index == 'N') || (index == 'W') || (index == 'E'))
		make_texture(vars, buf);
	if (index == 'S')
		south_or_sprite(vars, buf);
	if (index == 'F')
		make_floor(vars, buf + 1);
	if (index == 'C')
		make_celling(vars, buf + 1);
	return (flag);
}

void	init_parser_files(t_vars *vars)
{
	vars->letter_flag = 0;
	vars->flag_c_found = 0;
	vars->flag_ea_found = 0;
	vars->flag_f_found = 0;
	vars->flag_no_found = 0;
	vars->flag_r_found = 0;
	vars->flag_so_found = 0;
	vars->flag_s_found = 0;
	vars->flag_we_found = 0;
}

void	parser_file(char *file, t_vars *vars)
{
	int		fd;
	char	*buf;
	int		count;

	count = 0;
	init_parser_files(vars);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		errors("Error \nОшибка в чтении файла");
	while (get_next_line(fd, &buf) > 0)
	{
		vars->letter_flag = check_letter_id(buf, vars, vars->letter_flag);
		if (vars->letter_flag == 8 || vars->letter_flag == 9)
			count = process_id_and_str(buf, vars, &count);
		free(buf);
	}
	count = process_id_and_str(buf, vars, &count);
	if (!(vars->flag_no_found == 1 && vars->flag_so_found == 1
			&& vars->flag_ea_found == 1 && vars->flag_we_found == 1
			&& vars->flag_f_found == 1 && vars->flag_c_found == 1
			&& vars->flag_s_found == 1 && vars->flag_r_found == 1))
		errors("Error\nНеверно заданы параметры карты");
	free(buf);
	close(fd);
	vars->nbr_str = count;
}

void	make_sprite(t_vars *vars, char *buf)
{
	vars->flag_s_found = 1;
	while (*buf == ' ')
		buf++;
	vars->sprite_texture_path = ft_strdup(buf);
}
