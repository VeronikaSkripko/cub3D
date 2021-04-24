/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:25:28 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:25:30 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_save(char *file, char *save)
{
	int	i;

	i = 0;
	while (save[i] != '\0')
	{
		if ((file[i] != save[i]) || (file[i] == '\0'))
		{
			errors("Error\nНеверное название аргумента");
			return (0);
		}
		i++;
	}
	if (save[i] == '\0' && file[i] != '\0')
	{
		errors("Error\nНеверное название аргумента");
		return (0);
	}
	return (1);
}

int	header_file(t_vars *vars, int fd)
{
	unsigned char	header[14];
	int				i;
	int				file_size;

	i = 0;
	file_size = 54 + (vars->line_length * vars->render_size_y);
	while (i < 14)
	{
		header[i] = (unsigned char)(0);
		i++;
	}
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	i = file_size;
	header[2] = (unsigned char)(i % 256);
	header[3] = (unsigned char)(i / 256 % 256);
	header[4] = (unsigned char)(i / 256 / 256 % 256);
	header[5] = (unsigned char)(i / 256 / 256 / 256);
	header[10] = (unsigned char)(54);
	return (!(write(fd, &header, 14) < 0));
}

int	image_header(t_vars *vars, int fd)
{
	unsigned char	image_file[40];
	int				i;
	int				width;
	int				height;

	i = 0;
	width = (int)vars->render_size_x;
	height = (int)vars->render_size_y;
	while (i < 40)
	{
		image_file[i] = (unsigned char)0;
		i++;
	}
	image_file[0] = (unsigned char)40;
	image_file[4] = (unsigned char)(width % 256);
	image_file[5] = (unsigned char)(width / 256 % 256);
	image_file[6] = (unsigned char)(width / 256 / 256 % 256);
	image_file[7] = (unsigned char)(width / 256 / 256 / 256);
	image_file[8] = (unsigned char)(height % 256);
	image_file[9] = (unsigned char)(height / 256 % 256);
	image_file[10] = (unsigned char)(height / 256 / 256 % 256);
	image_file[11] = (unsigned char)(height / 256 / 256 / 256);
	image_file[12] = (unsigned char)(1);
	image_file[14] = (unsigned char)(vars->bits_per_pixel);
	return (!(write(fd, &image_file, 40) < 0));
}

int	write_image(t_vars *vars, int fd)
{
	int	y;

	y = (int)(vars->render_size_y) - 1;
	while (y >= 0)
	{
		if (write(fd, vars->addr + y * vars->line_length,
				  vars->line_length) < 0)
			return (0);
		y--;
	}
	return (1);
}

int	save_bmp_image(t_vars *vars)
{
	int	fd;

	fd = open("bmpscreen.bmp", O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
	if (fd < 0)
	{
		return (0);
	}
	if (!(header_file(vars, fd)))
		return (0);
	if (!(image_header(vars, fd)))
	{
		return (0);
	}
	if (!(write_image(vars, fd)))
	{
		return (0);
	}
	close(fd);
	return (1);
}
