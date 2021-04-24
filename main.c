//

#include "cub3d.h"

int	draw(t_vars *vars)
{
	draw_map(vars);
	check_sprite(vars);
	if (vars->bmp_flag == 1)
	{
		if (!(save_bmp_image(vars)))
			perror("Error\nКартинка не сохранилась");
		exit(1);
	}
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->image, 0, 0);
	return (0);
}

int	check_filename(char *file, char *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (file[i] != '\0')
		i++;
	i -= 4;
	while (map[j] != '\0')
	{
		if ((file[i] != map[j]) || (file[i] == '\0'))
		{
			errors("Error\nНеверное название аргумента");
			return (0);
		}
		i++;
		j++;
	}
	if (map[j] == '\0' && file[i] != '\0')
	{
		errors("Error\nНеверное название аргумента");
		return (0);
	}
	return (1);
}

void	init_textures(t_vars *vars)
{
	vars->texture_addr = (char **)(malloc(sizeof(char *) * 4));
	vars->texture_bits_per_pixel = (int *)malloc(sizeof(int) * 4);
	vars->texture_endian = (int *)malloc(sizeof(int) * 4);
	vars->texture_width = (int *)malloc(sizeof(int) * 4);
	vars->texture_height = (int *)malloc(sizeof(int) * 4);
	vars->texture_line_length = (int *)malloc(sizeof(int) * 4);
	vars->texture[0] = mlx_xpm_file_to_image(vars->mlx, vars->texture_path[0],
			&vars->texture_width[0], &vars->texture_height[0]);
	vars->texture[1] = mlx_xpm_file_to_image(vars->mlx, vars->texture_path[1],
			&vars->texture_width[1], &vars->texture_height[1]);
	vars->texture[2] = mlx_xpm_file_to_image(vars->mlx, vars->texture_path[2],
			&vars->texture_width[2], &vars->texture_height[2]);
	vars->texture[3] = mlx_xpm_file_to_image(vars->mlx, vars->texture_path[3],
			&vars->texture_width[3], &vars->texture_height[3]);
	if (vars->texture[0] == NULL || vars->texture[1] == NULL
		|| vars->texture[2] == NULL || vars->texture[3] == NULL)
		errors("Error \nНесуществующий файл для структуры");
	add_texture_addr(vars);
}

void	init(t_vars *vars, char *file)
{
	if (check_filename(file, ".cub"))
	{
		vars->texture = (void *)(malloc(sizeof(void *) * 4));
		vars->texture_path = (char **)malloc(sizeof(char *) * 4);
		process_map(file, vars);
		player_pos(vars);
		vars->mlx = mlx_init();
		vars->win = mlx_new_window(vars->mlx, vars->render_size_x,
				vars->render_size_y, file);
		vars->image = mlx_new_image(vars->mlx, vars->render_size_x,
				vars->render_size_y);
		vars->addr = mlx_get_data_addr(vars->image, &vars->bits_per_pixel,
				&vars->line_length, &vars->endian);
		init_textures(vars);
		init_sprites(vars);
		mlx_hook(vars->win, 17, 0, ft_exit, vars);
		mlx_hook(vars->win, 2, 1L << 0, press_key, vars);
		mlx_loop_hook(vars->mlx, draw, vars);
		mlx_loop(vars->mlx);
	}
	else
		errors("Error\nНазвание файла некорректно");
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc > 3 || argc < 2)
		errors("Error \nКоличество аргументов неверно");
	if (argc == 3 && check_save(argv[2], "--save"))
	{
		vars.bmp_flag = 1;
		init(&vars, argv[1]);
	}
	if (argc == 2)
	{
		vars.bmp_flag = 0;
		init(&vars, argv[1]);
	}
}
