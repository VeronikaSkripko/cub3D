/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:23:30 by schaya            #+#    #+#             */
/*   Updated: 2021/04/22 17:52:58 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define PI 3.1415926535
# define RAD 0.017453298768179
# define KEY_ESC 53
# define ARROW_RIGHT 124
# define ARROW_LEFT 123
# define KEY_A 0
# define KEY_D 2
# define KEY_S 1
# define KEY_W 13
# define SPEED 6
# define SPEED_ANGLE 0.03
# define SIZE 64
# include "get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include "minilibx_opengl_20191021/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

typedef struct s_sprite
{
	int		sprite_x;
	int		sprite_y;
	float	sprite_angle;
	float	sprt_dist;
	int		sprite_w;
	int		sprite_height;
	int		x;
	int		y;

}			t_sprite;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	void			*image;
	char			**map;
	char			**whole_map;
	void			**texture;
	void			*sprite;
	int				nbr_str;
	int				letter_flag;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	char			*addr;
	float			x_plr;
	float			y_plr;
	float			angl_plr;
	float			delta_x;
	float			delta_y;
	float			wall_h;
	int				flag_ray;
	float			y_step_wall;
	float			offset_wall;
	unsigned int	color_wall;
	int				*texture_width;
	int				*texture_height;
	char			**texture_path;
	char			**texture_addr;
	int				*texture_bits_per_pixel;
	int				*texture_line_length;
	int				*texture_endian;
	int				sprite_texture_width;
	int				sprite_texture_height;
	char			*sprite_texture_path;
	char			*sprite_texture_addr;
	int				sprite_bits_per_pixel;
	int				sprite_line_length;
	int				sprite_endian;
	int				sprite_count;
	int				sprite_y_offset;
	float			sprite_angle_range;
	float			sprite_start_angl;
	int				sprite_start_point_x;
	float			sprite_y_step;
	int				sprite_x_in_texture;
	unsigned int	sprite_color;
	float			sprite_current_angle;
	unsigned int	floor_color;
	unsigned int	celling_color;
	int				render_size_x;
	int				render_size_y;
	int				screen_size_w;
	int				screen_size_h;
	t_sprite		*array_of_sprt;
	int				bmp_flag;
	int				flag_r_found;
	int				flag_no_found;
	int				flag_so_found;
	int				flag_ea_found;
	int				flag_we_found;
	int				flag_f_found;
	int				flag_c_found;
	int				flag_s_found;
	int				flag_map_found;
}					t_vars;

typedef struct s_ray
{
	float	ry;
	float	rx;
	float	xo;
	float	yo;
	float	angl;
	int		flag_out;
	int		dist;
}			t_ray;

int				ft_exit(t_vars *vars);
void			exit_everywhere(t_vars *vars);
void			errors(char *message);
int				press_key_right_left(int key, t_vars *vars);
int				press_key_up_down(int key, t_vars *vars);
int				press_key(int key, t_vars *vars);
void			skip_spaces1(char **buf);
void			init_parser_files(t_vars *vars);
void			work_with_no_texture(t_vars *vars, char *buf);
void			work_with_so_texture(t_vars *vars, char *buf);
void			work_with_ea_texture(t_vars *vars, char *buf);
void			work_with_we_texture(t_vars *vars, char *buf);
void			make_texture(t_vars *vars, char *buf);
void			make_sprite(t_vars *vars, char *buf);
unsigned int	ft_atoi_color(char *buf, int *i, char c);
void			make_floor(t_vars *vars, char *buf);
unsigned int	turn_rgb(unsigned int red, unsigned int green, unsigned int
					blue);
void			make_celling(t_vars *vars, char *buf);
void			parsing_map_size(t_vars *vars, char *buf);
void			add_render_x(t_vars *vars, char **buf, int *flag_x,
					int *digit_count);
void			find_map_size(t_vars *vars, char *buf);
void			check_wrong_render_size_sym(char *buf);
int				count_str(char *file, t_vars *vars);
char			*change_spaces(char *buf);
char			**fill_map(char *str, t_vars *vars);
void			check_map_condition1_corners(t_vars *vars, int i, int j);
void			check_map_condition2_zero_and_spaces(t_vars *vars,
					int i, int j);
void			check_map_condition3_zero_and_spaces(t_vars *vars,
					int i, int j);
void			check_map_condition4(t_vars *vars, int i, int j);
void			check_map_condition5(t_vars *vars, int i, int j);
void			check_map_condition6(t_vars *vars, int i, int j);		
void			check_map(t_vars *vars);
void			check_map_elem(t_vars *vars);
void			player_pos(t_vars *vars);
void			find_player_pos(t_vars *vars, int *i, int *j, int *found);
void			player_angle(t_vars *vars, int *i, int *j);
void			my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
float			dist(float px, float py, float hor_ray_x, float hot_ray_y);
int				draw(t_vars *vars);
void			draw_celling_floor(t_vars *vars);
void			find_wall_h_part2(t_vars *vars, t_ray *hor,
					t_ray *vert, int **z);
void			find_wall_h(t_vars *vars, t_ray *hor, t_ray *vert, int *z);
void			process_wall_x_in_draw2(t_vars *vars, t_ray *vert, int **y);
void			process_wall_x_in_draw(t_vars *vars, t_ray *hor,
					t_ray *vert, int *y);
void			process_wall_y_in_draw(t_vars *vars, t_ray *hor,
					t_ray *vert, int *z);
int				draw_map(t_vars *vars);
void			add_texture_addr(t_vars *vars);
void			init_textures(t_vars *vars);
void			init_sprites(t_vars *vars);
void			count_sprites(t_vars *vars);
void			sprites_position_add(t_vars *vars, int *j,
					int *i, int *c);
void			sprites_position(t_vars *vars);
void			check_sprite(t_vars *vars);
void			sprite_distance(t_vars *vars);
void			sort_sprite(t_vars *vars);
void			angle_sprite(t_vars *vars);
void			define_sprite_h_w(t_vars *vars, int *i);
void			define_sprite_start_angle(t_vars *vars, int *i);
void			define_sprite_angle(t_vars *vars, int *i);
void			check_offset(t_vars *vars, int *i);
void			process_sprite_y_in_draw(t_vars *vars, int *i, int *x);
void			process_sprite_x_in_draw(t_vars *vars, int *i);
int				draw_sprites(t_vars *vars);
t_ray			get_hor_ray(t_vars *vars, int z);
void			hor_ray_look_up(t_vars *vars, t_ray *ray, float *aTan);
void			hor_ray_look_down(t_vars *vars, t_ray *ray, float *aTan);
void			hor_ray(t_vars *vars, t_ray *ray, int *z, int *flag_out);
t_ray			get_vert_ray(t_vars *vars, int z);
void			vert_ray_look_left(t_vars *vars, t_ray *ray, float *aTan);
void			vert_ray(t_vars *vars, t_ray *ray, int *z, int *flag_out);
int				get_next_line(int fd, char **line);
char			*ft_free(char *str);
int				ft_strlen(const char *str);
char			*ft_strchr(const char *str, char symbol);
char			*join_parts(char *line, char *buf);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strdup(const char *str);
void			parser_file(char *file, t_vars *vars);
char			skip_spaces(char **buf, int *flag, t_vars *vars);
void			south_or_sprite(t_vars *vars, char *buf);
int				check_letter_id(char *buf, t_vars *vars, int flag);
int				pass_letters_in_map(char *buf, int *all_str);
void			find_whole_map_and_map(char *buf, int *all_str,
					int *map_str, t_vars *vars);
void			process_map(char *file, t_vars *vars);
int				check_save(char *file, char *save);
int				check_filename(char *file, char *map);
void			init(t_vars *vars, char *file);
int				header_file(t_vars *vars, int fd);
int				image_header(t_vars *vars, int fd);
int				write_image(t_vars *vars, int fd);
int				save_bmp_image(t_vars *vars);
int				process_id_and_str(char *buf, t_vars *vars, int *count);
t_ray			get_vert_ray_sprites(t_vars *vars, float angle);
void			vert_ray_sprites(t_vars *vars, t_ray *ray, float angle,
					int *flag_out);
t_ray			get_hor_ray_sprites(t_vars *vars, float angle);
void			hor_ray_sprite_look_up(t_vars *vars, t_ray *ray, float *a_tan);
void			hor_ray_sprite_look_down(t_vars *vars, t_ray *ray,
					float *a_tan);
void			hor_ray_sprites(t_vars *vars, t_ray *ray, float angle,
					int *flag_out);
void			hor_ray_sprite1(t_vars *vars, t_ray *ray, int *flag_out);
void			get_vert_ray_sprites_loop(t_vars *vars, t_ray *ray,
					int *flag_out);

#endif