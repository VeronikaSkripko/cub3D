/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:43:24 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 11:26:36 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*copy;

	i = 0;
	copy = malloc(ft_strlen(str) + 1);
	if (!copy)
		return (NULL);
	while (str[i] != '\0')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static char	*check_newstr(char **newstr, char **line)
{
	char	*a;

	a = NULL;
	if (*newstr)
	{
		a = ft_strchr(*newstr, '\n');
		if (a != 0)
		{
			*a++ = '\0';
			*line = ft_strdup(*newstr);
			if (*a)
				ft_strcpy(*newstr, a);
			else
				*newstr = ft_free(*newstr);
		}
		else
		{
			*line = ft_strdup(*newstr);
			*newstr = ft_free(*newstr);
		}
	}
	else
		*line = ft_strdup("");
	return (a);
}

static int	ft_finder(char **after_n, char *buf, char **newstr_, char **line)
{
	*after_n = ft_strchr(buf, '\n');
	if (*after_n != 0)
	{
		*(*after_n)++ = '\0';
		*newstr_ = ft_strdup(*after_n);
		if (**after_n && !(*newstr_))
		{
			free(newstr_);
			free(buf);
			return (-1);
		}
	}
	*line = join_parts(*line, buf);
	if (!(*line))
	{
		free(buf);
		free(newstr_);
		return (-1);
	}
	return (0);
}

int	check_buf(char **buf, int *fd, char **newstr)
{
	if (!(*buf) || (read(*fd, buf, 0) < 0))
	{
		free(*newstr);
		free(*buf);
		return (1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*newstr;
	char		*buf;
	char		*after_n;
	size_t		num;

	if (!line || BUFFER_SIZE <= 0)
		return (-1);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (check_buf(&buf, &fd, &newstr))
		return (-1);
	after_n = check_newstr(&newstr, line);
	num = -1;
	while ((after_n == NULL) && ((num) != 0))
	{
		num = read(fd, buf, BUFFER_SIZE);
		buf[num] = '\0';
		if (ft_finder(&after_n, buf, &newstr, line) == -1)
			return (-1);
	}
	free(buf);
	if (!after_n)
		return (0);
	else
		return (1);
}
