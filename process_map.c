/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:25:22 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:25:24 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_map(char *file, t_vars *vars)
{
	parser_file(file, vars);
	vars->flag_map_found = 0;
	vars->map = (char **)malloc(sizeof(char *) * (vars->nbr_str + 1));
	vars->whole_map = (char **)malloc(sizeof(char *) * (vars->nbr_str + 1));
	vars->map = fill_map(file, vars);
	check_map(vars);
	check_map_elem(vars);
}

int	process_id_and_str(char *buf, t_vars *vars, int *count)
{
	while (*buf == ' ')
		buf++;
	if ((buf[0] == 'N' && buf[1] == 'O') || (buf[0] == 'S' && buf[1] == '0')
		|| (buf[0] == 'W' && buf[1] == 'E') || (buf[0] == 'E' && buf[1] == 'A')
		|| (buf[0] == 'S' || buf[0] == 'F') || (buf[0] == 'C' || buf[0] == 'R'))
		(vars->letter_flag)++;
	else
	{
		if ((vars->letter_flag == 9) && ((ft_strchr(buf, '2'))
				|| (ft_strchr(buf, '1')) || (ft_strchr(buf, '0'))
				|| (ft_strchr(buf, ' '))
				|| (ft_strchr(buf, 'W')) || (ft_strchr(buf, 'S'))
				|| (ft_strchr(buf, 'N')) || (ft_strchr(buf, 'E'))))
		{
			(*count)++;
		}
		else if (*buf != '\0')
			errors("Error\nОшибка в карте");
	}
	return (*count);
}

void	find_whole_map_and_map(char *buf, int *all_str, int *map_str,
t_vars *vars)
{
	if ((*all_str == 8 || *all_str == -1) && ((ft_strchr(buf, '2'))
			|| (ft_strchr (buf, '1')) || (ft_strchr(buf, '0'))
			|| (ft_strchr (buf, ' '))
			|| (ft_strchr(buf, 'W')) || (ft_strchr(buf, 'S'))
			|| (ft_strchr(buf, 'N')) || (ft_strchr(buf, 'E'))))
	{
		vars->whole_map[*map_str] = ft_strdup(buf);
		if (ft_strchr (buf, ' '))
			buf = change_spaces(buf);
		vars->map[*map_str] = ft_strdup(buf);
		(*map_str)++;
		vars->flag_map_found = 1;
	}
	if (ft_strlen(buf) == 0 && vars->flag_map_found == 1 && *all_str != -1)
		errors("Error\nInvalid map");
}

int	pass_letters_in_map(char *buf, int *all_str)
{
	while (*buf == ' ' && *all_str != 8)
		buf++;
	if ((buf[0] == 'N' && buf[1] == 'O') || (buf[0] == 'S' && buf[1] == '0')
		|| (buf[0] == 'W' && buf[1] == 'E') || (buf[0] == 'E' && buf[1] == 'A')
		|| (buf[0] == 'S' || buf[0] == 'F') || (buf[0] == 'C' || buf[0] == 'R'))
	{
		(*all_str)++;
		return (1);
	}
	return (0);
}

char	**fill_map(char *str, t_vars *vars)
{
	int		fd;
	int		all_str;
	int		map_str;
	char	*buf;

	all_str = 0;
	map_str = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		errors("Error \nОшибка в чтении файла");
	while (1)
	{
		if (get_next_line(fd, &buf) == 0)
			all_str = -1;
		if (!(pass_letters_in_map(buf, &all_str)))
			find_whole_map_and_map(buf, &all_str, &map_str, vars);
		if (all_str == -1)
			break ;
		free(buf);
	}
	close(fd);
	free(buf);
	return (vars->map);
}
