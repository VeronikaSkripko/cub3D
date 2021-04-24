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
	int	i;

	i = 0;
	vars->flag_no_found = 1;
	while (*buf == ' ')
		buf++;
	printf("buf north = %s\n", buf);
	if (buf[i] == '.' && buf[i + 1] == '/')
		vars->texture_path[0] = ft_strdup(buf);
	else
		errors("Error \nWrong texture path");
}

void	work_with_so_texture(t_vars *vars, char *buf)
{
	int	i;

	i = 0;
	vars->flag_so_found = 1;
	while (*buf == ' ')
		buf++;
	printf("buf south = %s\n", buf);
	if (buf[i] == '.' && buf[i + 1] == '/')
		vars->texture_path[1] = ft_strdup(buf);
	else
		errors("Error \nWrong texture path");
}

void	work_with_ea_texture(t_vars *vars, char *buf)
{
	int	i;

	i = 0;
	vars->flag_ea_found = 1;
	while (*buf == ' ')
		buf++;
	printf("buf east = %s\n", buf);
	if (buf[i] == '.' && buf[i + 1] == '/')
		vars->texture_path[2] = ft_strdup(buf);
	else
		errors("Error \nWrong texture path");
}

void	work_with_we_texture(t_vars *vars, char *buf)
{
	int	i;

	i = 0;
	vars->flag_we_found = 1;
	while (*buf == ' ')
		buf++;
	printf("buf west = %s\n", buf);
	if (buf[i] == '.' && buf[i + 1] == '/')
		vars->texture_path[3] = ft_strdup(buf);
	else
		errors("Error \nWrong texture path");
}
