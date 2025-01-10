/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaurama <ngaurama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:58:15 by ngaurama          #+#    #+#             */
/*   Updated: 2024/11/25 14:55:53 by ngaurama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = ft_calloc(i + 2, sizeof(char));
	else
		line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy(line, buffer, i + (buffer[i] == '\n'));
	return (line);
}

char	*trim_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	new_buffer = ft_calloc(ft_strlen(buffer) - i, sizeof(char));
	if (!new_buffer)
		return (free(buffer), NULL);
	while (buffer[++i])
		new_buffer[j++] = buffer[i];
	free(buffer);
	return (new_buffer);
}

char	*append_and_free(char *buffer, char *buf)
{
	char	*new_buffer;

	new_buffer = ft_strjoin(buffer, buf);
	free(buffer);
	return (new_buffer);
}

char	*read_and_append(int fd, char *buffer, int bytes_read)
{
	char	*temp_buf;

	temp_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_buf)
		return (free(buffer), NULL);
	if (!buffer)
	{
		buffer = ft_calloc(1, 1);
		if (!buffer)
			return (free(temp_buf), free(buffer), NULL);
	}
	while (1)
	{
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		temp_buf[bytes_read] = '\0';
		buffer = append_and_free(buffer, temp_buf);
		if (ft_strchr(temp_buf, '\n'))
			break ;
	}
	free(temp_buf);
	if (bytes_read < 0)
		return (free(buffer), NULL);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffers[MULTI_FD];
	char		*line;
	int			bytes_read;

	bytes_read = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffers[fd]), buffers[fd] = NULL, NULL);
	buffers[fd] = read_and_append(fd, buffers[fd], bytes_read);
	if (!buffers[fd])
		return (NULL);
	line = extract_line(buffers[fd]);
	if (!line)
		return (free(buffers[fd]), buffers[fd] = NULL, NULL);
	buffers[fd] = trim_buffer(buffers[fd]);
	if (!buffers[fd] && *line == '\0')
		return (free(line), NULL);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		i;

// 	int fd[4];
// 	fd[0] = open("test1", O_RDWR);
// 	fd[1] = open("test2", O_RDWR);
// 	i = 0;
// 	while (i < 5)
// 	{
// 		if ((line = get_next_line(fd[0])) != NULL)
// 		{
// 			printf("%s", line);
// 			free(line);
// 		}
// 		if ((line = get_next_line(fd[1])) != NULL)
// 		{
// 			printf("%s", line);
// 			free(line);
// 		}
// 		i++;
// 	}
// 	close(fd[0]);
// }
