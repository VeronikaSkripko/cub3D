/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:44:18 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 11:25:07 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 200
# include <unistd.h>
# include <stdlib.h>

int			get_next_line(int fd, char **line);
int			ft_strlen(const char *str);
char		*ft_strchr(const char *str, char symbol);
char		*join_parts(char *line, char *buf);
char		*ft_strcpy(char *dest, char *src);
char		*ft_free(char *str);

#endif
