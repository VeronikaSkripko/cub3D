NAME	= cub3D

SRCS	=  cub3d.c get_next_line.c get_next_line_utils.c parser.c sprites.c\
			player.c process_map.c exit_errors.c check_map.c check_map2.c save_bmp.c press_key.c\
			utills.c draw_walls.c draw_walls_extra.c parser_floor_celling.c\
			parser_textures.c parser_map_size.c horizont_ray.c vertical_ray.c\
			sprite_hor_ray.c sprite_vert_ray.c check_sprites.c init_sprites.c draw_sprites.c
			
HEADERS  = cub3d.h

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

.c.o:	%.c ${HEADERS}
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME) : ${OBJS} libmlx.a
			${CC} ${OBJS} libmlx.a -framework OpenGL -framework Appkit -O2 -o ${NAME}

all: ${NAME}

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re