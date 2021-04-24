/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:24:24 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:24:26 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_sprites(t_vars *vars)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < vars->nbr_str)
	{
		j = 0;
		while (j < ft_strlen(vars->map[i]))
		{
			if (vars->map[i][j] == '2')
				count++;
			j++;
		}
		i++;
	}
	vars->sprite_count = count;
}

void	sprites_position_add(t_vars *vars, int *j, int *i, int *c)
{
	vars->array_of_sprt[*c].sprite_x = ((*j) * SIZE) + SIZE / 2;
	vars->array_of_sprt[*c].sprite_y = ((*i) * SIZE) + SIZE / 2;
	vars->array_of_sprt[*c].x = (*j);
	vars->array_of_sprt[*c].y = (*i);
	(*c)++;
	vars->map[*i][*j] = '0';
}

void	sprites_position(t_vars *vars)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	vars->array_of_sprt = malloc(sizeof(t_sprite) * vars->sprite_count);
	while (i < vars->nbr_str)
	{
		j = 0;
		while (j < ft_strlen(vars->map[i]))
		{
			if (vars->map[i][j] == '2')
				sprites_position_add(vars, &j, &i, &count);
			j++;
		}
		i++;
	}
}

void	init_sprites(t_vars *vars)
{
	count_sprites(vars);
	sprites_position(vars);
	vars->sprite = mlx_xpm_file_to_image(vars->mlx, vars->sprite_texture_path,
			 &vars->sprite_texture_width, &vars->sprite_texture_height);
	if (vars->sprite == NULL)
		errors("Error\nНеверный путь спрайта");
	vars->sprite_texture_addr = mlx_get_data_addr(vars->sprite,
			&vars->sprite_bits_per_pixel, &vars->sprite_line_length,
			&vars->sprite_endian);
}
