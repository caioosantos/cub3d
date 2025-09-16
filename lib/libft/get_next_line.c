/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:50:36 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/09/15 21:38:46 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_buffer(char **buffer)
{
	if (buffer && *buffer)
	{
		untrack_pointer(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

static char	*get_line_tail(char *buf)
{
	int		b_read;
	char	*tail;

	b_read = 0;
	while (buf[b_read] != '\n' && buf[b_read] != '\0')
		b_read++;
	if (buf[b_read] == '\n')
		b_read++;
	if (buf[b_read] == '\0')
		return (NULL);
	tail = ft_strdup(buf + b_read);
	buf[b_read] = '\0';
	return (tail);
}

static char	*get_line(int fd, char *buf, char *tail)
{
	ssize_t	buf_size;
	char	*temp;

	while (1)
	{
		buf_size = read(fd, buf, BUFFER_SIZE);
		if (buf_size == -1)
			return (NULL);
		if (buf_size == 0)
			break ;
		buf[buf_size] = '\0';
		if (!tail)
			tail = ft_collect_mem(1, sizeof(char));
		temp = tail;
		tail = ft_strjoin(temp, buf);
		free_buffer(&temp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (tail);
}

char	*get_next_line(int fd)
{
	static char	*tail = NULL;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_collect_mem(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	line = get_line(fd, buffer, tail);
	free_buffer(&buffer);
	if (!line)
		return (free_buffer(&tail));
	tail = get_line_tail(line);
	return (line);
}
