/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:27:47 by marvin            #+#    #+#             */
/*   Updated: 2021/12/22 16:27:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_append(char **back_up, char **line)
{
	int		len;
	char	*tmp;

	len = 0;
	while ((*back_up)[len] != '\n' && (*back_up)[len] != '\0')
		len++;
	if ((*back_up)[len] == '\n')
	{
		*line = ft_substr(*back_up, 0, len + 1);
		tmp = ft_strdup(&(*back_up)[len + 1]);
		free(*back_up);
		*back_up = tmp;
		if ((*back_up)[0] == 0)
		{
			free(*back_up);
			*back_up = 0;
		}
	}
	else
	{
		*line = ft_strdup(*back_up);
		free(*back_up);
		*back_up = 0;
	}
	return (*line);
}

static char	*check_line(char **back_up, char **line, int ret, int fd)
{
	if (ret <= 0 && back_up[fd] == NULL)
		return (NULL);
	else
		return (ft_append(&back_up[fd], line));
}

char	*get_next_line(int fd)
{
	int			read_size;
	static char	*back_up[10240];
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_size = read(fd, buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		buf[read_size] = '\0';
		if (back_up[fd] == 0)
			back_up[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(back_up[fd], buf);
			free(back_up[fd]);
			back_up[fd] = tmp;
		}
		if (ft_strchr(back_up[fd], '\n'))
			break ;
		read_size = read(fd, buf, BUFFER_SIZE);
	}
	return (check_line(back_up, &line, read_size, fd));
}
