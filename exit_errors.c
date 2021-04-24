/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:23:57 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:23:59 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_everywhere(t_vars *vars)
{
	int	i;

	i = 0;
	free(vars->array_of_sprt);
	while (i < vars->nbr_str)
		free(vars->map[i++]);
	free(vars->map);
	i = 0;
	while (i < vars->nbr_str)
		free(vars->whole_map[i++]);
	free(vars->whole_map);
	mlx_destroy_image(vars->mlx, vars->image);
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	free(vars->texture_addr[0]);
	free(vars->texture_addr[1]);
	free(vars->texture_addr[2]);
	free(vars->texture_addr[3]);
	exit(0);
}

int	ft_exit(t_vars *vars)
{
	exit_everywhere(vars);
	exit(0);
}

void	errors(char *message)
{
	printf("\033[41m%s\033[0m", message);
	exit(1);
}
