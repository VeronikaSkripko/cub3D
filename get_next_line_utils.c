/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaya <schaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:24:04 by schaya            #+#    #+#             */
/*   Updated: 2021/04/16 17:24:06 by schaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, char ch)
{
	char	*s;
	int		i;

	s = (char *)str;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == ch)
		return ((char *)s + i);
	return (0);
}

char	*join_parts(char *line, char *buf)
{
	int		i;
	int		g;
	char	*newline;

	i = 0;
	g = 0;
	if (line == NULL || buf == NULL)
		return (NULL);
	newline = ((char *)malloc
			(sizeof(char) * (ft_strlen(line) + ft_strlen(buf)) + 1));
	if (!newline)
		return (NULL);
	while (line[i] != '\0')
		newline[g++] = line[i++];
	free(line);
	i = 0;
	while ((buf[i] != '\0'))
		newline[g++] = buf[i++];
	newline[g] = '\0';
	return (newline);
}

char	*ft_free(char *str)
{
	free(str);
	return (NULL);
}
